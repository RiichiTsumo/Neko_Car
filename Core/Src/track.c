#include "track.h"
#include "motor.h"
#include "main.h"
#include "stm32f1xx_it.h"
#include "gpio.h"

#define A_SPEED 67						// 67
#define B_SPEED 50					// 50
#define DELAY_NO 20
#define DELAY_SP 10



void Tracking(void)
{
	/*  if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
	  			HAL_Delay(DELAY_SP);
				if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
					HAL_Delay(DELAY_SP);
					if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
				  				while(1)
				  				{
				  					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 100);
				  					LEFT_IMM();
				  					HAL_Delay(DELAY_DF);
				  					if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
				  						__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
				  						break ;
				  					}
				  				}
					}
				  					}else if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
				  						HAL_Delay(DELAY_SP);
				  						if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
				  						while(1)
						  				{
						  					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 100);
						  					RIGHT_IMM();
						  					HAL_Delay(DELAY_DF);
						  					if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
						  						__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
						  						break ;
						  					}
						  				}
						  				}
						  					}
	  			// 左、右侧入环
	  			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(loop == 0)){
	  				loop = 1;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(loop == 0)){
	  				loop = 1;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}
	  			// 二阶段
	  			else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(loop == 1)){
	  				loop = 2;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(loop == 1)){
	  				loop = 2;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			// 差不多可以结束了
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(loop == 2)){
	  				loop = 0;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(loop == 2)){
	  				loop = 0;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}
	  			else{
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}
	  		}
	  // 右转
else if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		HAL_Delay(DELAY_SP);
		if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
			HAL_Delay(DELAY_SP);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
			while(1)
		  				{
		  					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 100);
		  					RIGHT_IMM();
		  					HAL_Delay(DELAY_DF);
		  					if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
		  						__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
		  						break ;
		  					}
		  				}
			}
		  					}
			HAL_Delay(DELAY_NO);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
				right:
		while(1)
		{
			RIGHT();
			switch(loop){
			case 0:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 165);break;
			case 1:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 140);break;
			case 2:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 160);break;
			default:break;
		}
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
				break ;
			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
				goto left;
			}
		}
			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1))){
				while(1){
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);
				if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)){
					break;
				}
			}
			}else{
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);
			}
		}
		// 左转
		else  if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
			HAL_Delay(DELAY_SP);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
				HAL_Delay(DELAY_SP);
				if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
				while(1)
			  				{
			  					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 100);
			  					LEFT_IMM();
			  					HAL_Delay(DELAY_DF);
			  					if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			  						__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
			  						break ;
			  					}
			  				}
				}
			  					}
			HAL_Delay(DELAY_NO);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
				left:
		while(1)
		{
			LEFT();
			switch(loop){
			case 0:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 135);break;
			case 1:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 160);break;
			case 2:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 140);break;
			default:break;
		}
		 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
			 break ;
		 	}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)){
				goto right;
			}
		}
			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1))){
				while(1){
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);
				if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
					break;
				}
			}
			}else{
				A_Forward(A_SPEED);
				B_Forward(B_SPEED);

			}
		}
		// T字与十字路口、出入环检查

		// 直行
		else{
			A_Forward(A_SPEED);
			B_Forward(B_SPEED);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
		}*/
 }
