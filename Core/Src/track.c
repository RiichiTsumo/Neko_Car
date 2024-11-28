#include "track.h"
#include "motor.h"

int meow = 0;

void Tracking(void)
{
	   // 右转
		if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
			HAL_Delay(50);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		while(1)
		{
			RIGHT();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
			}else{
				A_Forward(58);
				B_Forward(48);
			}
		}
		// 左转
		else  if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
			HAL_Delay(50);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&roll==0){
		while(1)
		{
			LEFT();
		 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
		 	}
		}
			}else{
				A_Forward(58);
				B_Forward(48);
			}
		}
		// 右急转
		if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
			HAL_Delay(20);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		while(1)
		{
			RIGHT_IMM();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
			}else{
				A_Forward(58);
				B_Forward(48);
			}
		}

		//环岛
		if(((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1) || (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)) && ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0) || (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0))){
			  HAL_TIM_Base_Start_IT(&htim3);
			  while(meow == 0){
					A_Forward(58);
					B_Forward(48);
			  }
		}
		// 直行
		else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
			A_Forward(58);
			B_Forward(48);
		}else{
			A_Forward(58);
			B_Forward(48);
		}

 }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim3){
		mewo = 1;
	}
}
