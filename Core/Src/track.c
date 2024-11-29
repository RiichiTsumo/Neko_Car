#include "track.h"
#include "motor.h"

#define A_SPEED 67						// 67
#define B_SPEED 50					// 50
#define DELAY_NO 20
#define DELAY_SP 10


void Tracking(void)
{
	   // 右转
		if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
			// HAL_Delay(DELAY_NO);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		while(1)
		{
			RIGHT();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
			}else{
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);
			}
		}
		// 左转
		else  if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
			// HAL_Delay(DELAY_NO);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
		while(1)
		{
			LEFT();
		 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
		 	}
		}
			}else{
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);
			}
		}
		// T字与十字路口
		if (((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1))){
			// HAL_Delay(DELAY_SP);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		while(1)
		{
			RIGHT_IMM();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);
			}else{
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);
			}
		}

		// 直行
		else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
			A_Forward(A_SPEED);
			B_Forward(B_SPEED);
		}else{
			A_Forward(A_SPEED);
			B_Forward(B_SPEED);
		}

 }
