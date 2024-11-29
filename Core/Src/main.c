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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int meow = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
typedef struct
{
   	float kp, ki, kd;
    float error, lastError;
    float integral, maxIntegral;
    float output, maxOutput;
}PID;

void PID_Init(PID *pid, float p, float i, float d, float maxI, float maxOut)
{
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    pid->maxIntegral = maxI;
    pid->maxOutput = maxOut;
}

void PID_Calc(PID *pid, float reference, float feedback)
{
    pid->lastError = pid->error;
    pid->error = reference - feedback;
    float dout = (pid->error - pid->lastError) * pid->kd;
    float pout = pid->error * pid->kp;
    pid->integral += pid->error * pid->ki;
    if(pid->integral > pid->maxIntegral) pid->integral = pid->maxIntegral;
    else if(pid->integral < -pid->maxIntegral) pid->integral = -pid->maxIntegral;
    pid->output = pout+dout + pid->integral;
    if(pid->output > pid->maxOutput) pid->output =   pid->maxOutput;
    else if(pid->output < -pid->maxOutput) pid->output = -pid->maxOutput;
}

PID mypid = {0};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim3){
		//meow = 1;
		A_Backward(65);
		B_Backward(55);
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
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2,  TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1,  TIM_CHANNEL_4);

  // PID_Init(&mypid, 0, 0, 0, 800, 1000);

  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start(&htim4);
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 145);		// 舵机A驱动代码，舵机占空比代数取值为40~250
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 40);		// 舵机B驱动代码
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 40);		// 舵机C驱动代码

  //HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
  TIM3->CCR1=TIM3->CCR4=80;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // HAL_TIM_Base_Start_IT(&htim3);
		//环岛
	/*	if(((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1) || (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1)) && ((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0) || (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0))){
			  HAL_TIM_Base_Start_IT(&htim3);
			  while(meow == 0){
					A_Forward(68);
					B_Forward(50);
			  }
			meow = 0;
		}*/
	  Tracking();
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
