#include "bsp_pid.h"
#include "math.h"
//#include "./key/bsp_key.h"
#include "protocol.h"
#include "tim.h"

//����ȫ�ֱ���

_pid pid;
double pwm_value = 0.0;//����˿��PWM�����ֵ
extern float tep;
/**
  * @brief  PID������ʼ��
	*	@note 	��
  * @retval ��
  */
void PID_param_init()
{
    /* ��ʼ������ */
//    printf("PID_init begin \n");
    pid.target_val=0.0;
    pid.actual_val=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.integral=0.0;
//		pid.Kp = 0.31;
//		pid.Ki = 0.070;
//		pid.Kd = 0.3;
//		pid.Kp = 0.21;
//		pid.Ki = 0.070;
//		pid.Kd = 0.3;
    pid.Kp = 0.01;//24
    pid.Ki = 0.80;
    pid.Kd = 0.04;

#if defined(PID_ASSISTANT_EN)
    float pid_temp[3] = {pid.Kp, pid.Ki, pid.Kd};
    set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3);     // ��ͨ�� 1 ���� P I D ֵ
#endif

}

/**
  * @brief  ����Ŀ��ֵ
  * @param  val		Ŀ��ֵ
	*	@note 	��
  * @retval ��
  */
void set_pid_target(float temp_val)
{
    pid.target_val = temp_val;    // ���õ�ǰ��Ŀ��ֵ
}

/**
  * @brief  ��ȡĿ��ֵ
  * @param  ��
	*	@note 	��
  * @retval Ŀ��ֵ
  */
float get_pid_target(void)
{
    return pid.target_val;    // �õ���ǰ��Ŀ��ֵ
}

/**
  * @brief  ���ñ��������֡�΢��ϵ��
  * @param  p������ϵ�� P
  * @param  i������ϵ�� i
  * @param  d��΢��ϵ�� d
	*	@note 	��
  * @retval ��
  */
void set_p_i_d(float p, float i, float d)
{
    pid.Kp = p;    // ���ñ���ϵ�� P
    pid.Ki = i;    // ���û���ϵ�� I
    pid.Kd = d;    // ����΢��ϵ�� D
}

/**
  * @brief  PID�㷨ʵ��
  * @param  val		ʵ��ֵ
  * @note 	��
  * @retval ͨ��PID���������
  */
float PID_realize(float temp_val)
{
			/*����Ŀ��ֵ*/
//    pid.target_val=temp_val;
    /*����Ŀ��ֵ��ʵ��ֵ�����*/
    pid.err=pid.target_val-temp_val;
    /*����ۻ�*/
    pid.integral+=pid.err;
    /*PID�㷨ʵ��*/
//    pid.actual_val=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
	pwm_value=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
    /*����*/
    pid.err_last=pid.err;
    /*���ص�ǰʵ��ֵ*/
//	pwm_value = pid.actual_val;//���۲�ֵ������PWM,�������Ĵﵽ�¶ȵĶ�̬ƽ�⡣
	/*** Լ��ռ�ձȵ�ֵ ***/
	if(pwm_value > 3500)
	{
		pwm_value = 3500;
	
	}
	else if(pwm_value < 0)
	{
		pwm_value = 0;
	
	
	}	
	TIM_SetTIM4Compare4(pwm_value);
//	printf("�˿�pwm_value��ֵ�ǣ�%2.f\r\n",pwm_value);
//    return pid.actual_val;
}

/**
  * @brief  ��ʱ�����ڵ��ú���
  * @param  ��
	*@note 	��
  * @retval ��
  */
float set_point = 0;
int pid_status=0;
void time_period_fun()
{

	
    if(!pid_status)
    {
		
//        float val=PID_realize(tep);
//		printf("act��ʵ��ֵ��%f\n",pid.actual_val);
        int temps = tep;    // ��λ����Ҫ����������ת��һ��
        set_computer_value(SEND_FACT_CMD, CURVES_CH1, &temps, 1);  
		// ��ͨ�� 1 ����ʵ��ֵ
//		set_computer_value(SEND_TARGET_CMD, CURVES_CH1, &set_point, 1);     // ��ͨ�� 1 ����Ŀ��ֵ
//		printf("act��ʵ��ֵ��%f\n",val);
		
		
//		while(pid.target_val >30 && pid.target_val <120)
//		{
////			PID_realize(tep);
////			float val = PID_realize(tep);
////			int temps = val;    // ��λ����Ҫ����������ת��һ��
//			set_computer_value(SEND_FACT_CMD, CURVES_CH1, &tep, 1); 
//		}

    }
	

}







