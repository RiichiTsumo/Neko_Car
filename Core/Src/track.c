#include "track.h"
#include "motor.h"

int checkpoint = 0;
int roll = 0;

void Tracking(void)
{
	   //右转
		if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
			if(checkpoint != 0){
				roll = 1;
				goto j;
			}
			HAL_Delay(50);
			j:
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&roll == 0){
		while(1)
		{
			RIGHT();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
			}else if(roll==1){
				HAL_Delay(100);
				roll=0;
				goto j;
			}else{
				A_Forward(58);
				B_Forward(48);
			}
		}
		//左转
		else  if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
			if(checkpoint != 0){
				roll = 1;
				goto p;
			}
			HAL_Delay(50);
			p:
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&roll==0){
		while(1)
		{
			LEFT();
		 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
		 	}
		}
			}else if(roll==1){
				HAL_Delay(100);
				roll = 0;
				goto p;
			}else{
				A_Forward(58);
				B_Forward(48);
			}
		}
		//直行
		else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
			A_Forward(58);
			B_Forward(48);
			checkpoint = 1;
		}else{
			A_Forward(58);
			B_Forward(48);
		}

 }
