/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define A_SPEED 61					// 71
#define B_SPEED 42						// 50
#define DELAY_NO 75
#define DELAY_SP 25
#define DELAY_DF 800
#define LEFT_SPD 50
#define RIGHT_SPD 40				// 若在右场，则将此处值 - 10
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int loop = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
		HAL_Delay(1000);
		  for(int b = 40;b <= 240;b ++){
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, b);
			  HAL_Delay(500);
		  }
		  HAL_Delay(1000);
		  for(int a = 240;a >= 50;a --){
		  		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, a);
		  		  HAL_Delay(500);
		  	  }
		  HAL_Delay(1000);
		  for(int b = 240;b >= 150;b --){
		  		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, b);
		  		  HAL_Delay(500);
		  	  }
		  HAL_Delay(3500);
		  for(int b = 150;b <= 240;b ++){
		  	  		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, b);
		  	  		  HAL_Delay(500);
		  	  	  }
		  HAL_Delay(1000);
		  for(int a = 50;a <= 240;a ++){
		  		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, a);
		  		  HAL_Delay(200);
		  	  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  // HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_4);

 // HAL_TIM_Base_Start_IT(&htim4);

  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 240);		// 舵机A驱动代码，舵机占空比代数取值为40~250
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 150);		// 舵机B驱动代码
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);		// 舵机C驱动代码!!!

  HAL_Delay(1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)){
	  			HAL_Delay(DELAY_SP);
	  			// 左、右侧入环
	  			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(loop == 0)){
	  				// loop = 1;
	  				HAL_Delay(DELAY_NO);
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 75);
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(loop == 0)){
	  				// loop = 1;
	  				HAL_Delay(DELAY_NO);
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 225);
	  			}
	  		// 二阶段
	  			else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(loop == 1)){
	  				loop = 2;
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(loop == 1)){
	  				loop = 2;
	  			// 差不多可以结束了
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(loop == 2)){
	  				loop = 3;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(loop == 2)){
	  				loop = 3;
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  			}
	  			else{
	  				A_Forward(A_SPEED);
	  				B_Forward(B_SPEED);
	  				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
	  			}
	  		}
	  // 右转
  else if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
	  HAL_Delay(DELAY_NO);
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
							for(int i = 100 ; i > 0 ; i --){
								A_Backward(i);
								B_Backward(i);
							}
							RIGHT(RIGHT_SPD);
							HAL_Delay(DELAY_DF);
							while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) != 1){
								RIGHT(RIGHT_SPD);
							}
						}
		else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&& loop != 9){
			RIGHT_SPD - 15;
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 180);
			loop =9;
						}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)){
							goto left;
						}
			HAL_Delay(DELAY_NO);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)){
				right:
		while(1)
		{
			RIGHT(RIGHT_SPD);
			switch(loop){
			case 0:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 165);break;
			case 1:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 140);break;
			case 2:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 160);break;
			default:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 165);break;
		}
			if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
				break ;
			}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
				goto left;
			}
		}
			}else if(((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1))){
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
		else  if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
			HAL_Delay(DELAY_NO);
				if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)){
								goto right;
							}
			else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(loop == 0)){
				  				// loop = 1;
				  				A_Forward(A_SPEED);
				  				B_Forward(B_SPEED);
				  				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 75);
				  			}
			else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&loop != 9){
				RIGHT_SPD - 15;
							__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 180);
							loop = 9;
										}
			HAL_Delay(DELAY_NO);
			if ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
				left:
		while(1)
		{
			LEFT(LEFT_SPD);
			switch(loop){
			case 0:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 135);break;
			case 1:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 160);break;
			case 2:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 140);break;
			default:__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 135);break;
			HAL_Delay(500);
		}
		 if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
			 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
			 break ;
		 	}else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)){
				// goto right;
			}
		}
			}else if(((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)||(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1))){
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
	  	  // T左转
	/*	if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1)){
					for(int i = 100 ; i > 0 ; i --){
						A_Backward(i);
						B_Backward(i);
					}
					LEFT(LEFT_SPD);
					loop = 9;
					HAL_Delay(DELAY_DF);
				}*/
		// T右转
		else if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0)){
					for(int i = 100 ; i > 0 ; i --){
						A_Backward(i);
						B_Backward(i);
					}
					RIGHT(RIGHT_SPD);
					loop = 9;
					HAL_Delay(DELAY_DF);
				}
		// 直行
		else{
			A_Forward(A_SPEED);
			B_Forward(B_SPEED);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 150);
		}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
