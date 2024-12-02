#include "track.h"
#include "motor.h"
void GO(void);
void Right_Try(void);
void Left_Try(void);

#define A_SPEED 66					// 66
#define B_SPEED 50					// 50
#define DELAY_NO 10
#define DELAY_SP 5


void Tracking(void){
	   // 右转
		if (((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1))&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
			GO();
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		while(1)
		{
			RIGHT();
			Left_Try();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
			}
		}
		// 左转
		else  if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1))){
			GO();
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
		while(1)
		{
			LEFT();
			Left_Try();
		 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
		 	}
		}
			}
		}
		// T字与十字路口
	/*	else if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		HAL_Delay(20);
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		while(1)
		{
			RIGHT_IMM();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
				}
			}
		}
	}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)){
		HAL_Delay(20);
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
		while(1){
		LEFT_IMM();
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break;
				}
			}
		}
	}
*/
		// 直行
		else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
			A_Forward(A_SPEED);
			B_Forward(B_SPEED);
		}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
			  	GO_Dir();
		  }else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0)){
			  HAL_Delay(50);
			  GO_Back();
		  }else{
			A_Forward(A_SPEED);
			B_Forward(B_SPEED);
		}

 }

void GO_Back(void){
	while(1){
	if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0)){
		A_Backward(A_SPEED - 30);
		B_Backward(B_SPEED - 25);
		}else{
			break;
		}
	}
}

void GO_Dir(void){
	while(1){
		A_Forward(A_SPEED);
		B_Forward(B_SPEED);
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 && HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0){
			break;
		}
	}
}

void Right_Try(void){
	if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
		A_Forward(A_SPEED);
		B_Forward(B_SPEED);
		HAL_Delay(500);
	}
if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
while(1)
{
RIGHT();
if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
break ;
}
}
}
}
void Left_Try(void){
	if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)){
		A_Forward(A_SPEED);
		B_Forward(B_SPEED);
		HAL_Delay(500);
	}
if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)){
while(1)
{
LEFT();
if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
break ;
}
}
}

}

void GO(void){
	HAL_Delay(10);
	if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
	while(1){
		A_Backward(A_SPEED);
		B_Backward(B_SPEED);
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
			break;
			}
    	}
	}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
		while(1){
		RIGHT();
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
		break ;
		}
		}
	}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
		while(1){
		LEFT();
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
		break ;
		}
		}
	}
}
