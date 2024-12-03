#include "track.h"
#include "motor.h"

#define A_SPEED 66					// 66
#define B_SPEED 50					// 50
#define DELAY_NO 20
#define DELAY_SP 10

int RIGHT_IN = 0;
int LEFT_IN = 0;
int RIGHT_OUT = 0;
int LEFT_OUT = 0;
int PHASE = 0;

void Tracking(void){
	// 入环判断、十字路口、T字路口
	if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
		HAL_Delay(DELAY_SP);
			// A-左侧赛道，右入环
		if(((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0))&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(LEFT_IN == 0)&&(RIGHT_IN == 0)){
			RIGHT_IN = 1;
			LEFT_IN = 0;
			PHASE = 1;
			return;
		}
			// B-右侧赛道，左入环
		else if(((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0))&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(LEFT_IN == 0)&&(RIGHT_IN == 0)){
			LEFT_IN = 1;
			RIGHT_IN = 0;
			PHASE = 1;
			return;
		}
		HAL_Delay(DELAY_SP);
			// 十字路口
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
				return;
		}
			// A-T字左转
			else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
				goto left;
			}
			// B-T字右转
			else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
				goto right;
			}
}
	   // A-右转同时进行出环判断
	else if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
			HAL_Delay(5);
			// 立刻判断一次是否在环内,若不是则直接清空所有标志
			if (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0){
				RIGHT_IN = 0;
				LEFT_IN = 0;
				RIGHT_OUT = 0;
				LEFT_OUT = 0;
				PHASE = 0;
			}
			HAL_Delay(DELAY_NO);
			// B-右侧出环,清零左侧入环
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(LEFT_IN == 1)&&(PHASE == 2)){
				HAL_Delay(DELAY_NO);
				if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(LEFT_IN == 1)&&(PHASE == 2)){
				RIGHT_OUT = 1;
				LEFT_OUT = 0;
				LEFT_IN = 0;
				return;
			}
	}
			// A-通常情况
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(RIGHT_OUT == 0)&&(RIGHT_IN == 0)){
				right:
		while(1){
			RIGHT();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
	}
			// A-右侧已入环——第一阶段
			if((RIGHT_IN == 1)&&(PHASE == 1)){
				while(1){
					RIGHT();
					if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
						break ;
					}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)){
						PHASE = 2;
						break ;
					}
				}
			}
			// B-左侧已入环——第二阶段
			if((LEFT_IN == 1)&&(PHASE == 2)){
				while(1){
					LEFT();
				 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
					break ;
				 	}
				}
			}
}



	   // B-左转同时进行出环判断
	else if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)){
			HAL_Delay(5);
			// 立刻判断一次是否在环内,若不是则直接清空所有标志
			if (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0){
				RIGHT_IN = 0;
				LEFT_IN = 0;
				RIGHT_OUT = 0;
				LEFT_OUT = 0;
				PHASE = 0;
			}
			HAL_Delay(DELAY_NO);
			// A-左侧出环,清零右侧入环
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(RIGHT_IN == 1)&&(PHASE == 2)){
				HAL_Delay(DELAY_NO);
				if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(RIGHT_IN == 1)&&(PHASE == 2)){
				LEFT_OUT = 1;
				RIGHT_OUT = 0;
				RIGHT_IN = 0;
				return;
			}
	}
			// B-通常情况
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(LEFT_OUT == 0)&&(LEFT_IN == 0)){
				left:
		while(1){
			LEFT();
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
			break ;
			}
		}
	}
			// B-左侧已入环——第一阶段
			if((LEFT_IN == 1)&&(PHASE == 1)){
				while(1){
					LEFT();
					if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
						break ;
					}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
						PHASE = 2;
						break ;
					}
				}
			}
			// A-右侧已入环——第二阶段
			if((RIGHT_IN == 1)&&(PHASE == 2)){
				while(1){
					RIGHT();
				 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)){
					break ;
				 	}
				}
			}
}
		// 备忘：在上面的while循环break条件里考虑加入判断4、8号光电的可能性

		// 如果条件全部不匹配，就直行
		else{
			A_Forward(A_SPEED);
			B_Forward(B_SPEED);
		}
 }
