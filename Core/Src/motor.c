/**
 * @file motor.c
 * @brief 双H桥电机驱动器控制实现
 */

#include <motor.h>
#include "tim.h"

/** @brief IN1引脚的定时器 */
#define IN1_TIM &htim1
/** @brief IN2引脚的定时器 */
#define IN2_TIM &htim1
/** @brief IN3引脚的定时器 */
#define IN3_TIM &htim1
/** @brief IN4引脚的定时器 */
#define IN4_TIM &htim1

/** @brief IN1引脚的定时器通道 */
#define IN1_CH TIM_CHANNEL_1
/** @brief IN2引脚的定时器通道 */
#define IN2_CH TIM_CHANNEL_2
/** @brief IN3引脚的定时器通道 */
#define IN3_CH TIM_CHANNEL_3
/** @brief IN4引脚的定时器通道 */
#define IN4_CH TIM_CHANNEL_4

/** @brief 最大速度值 */
#define MAX_SPEED 100


/** @brief 当前衰减模式 */
static DecayMode currentDecayMode = SLOW_DECAY;

/**
 * @brief 设置IN1引脚的PWM占空比
 * @param duty 占空比值
 */
static inline void __SetIn1PWM(uint8_t duty)
{
    __HAL_TIM_SET_COMPARE(IN1_TIM, IN1_CH, duty);
}

/**
 * @brief 设置IN2引脚的PWM占空比
 * @param duty 占空比值
 */
static inline void __SetIn2PWM(uint8_t duty)
{
    __HAL_TIM_SET_COMPARE(IN2_TIM, IN2_CH, duty);
}

/**
 * @brief 设置IN3引脚的PWM占空比
 * @param duty 占空比值
 */
static inline void __SetIn3PWM(uint8_t duty)
{
    __HAL_TIM_SET_COMPARE(IN3_TIM, IN3_CH, duty);
}

/**
 * @brief 设置IN4引脚的PWM占空比
 * @param duty 占空比值
 */
static inline void __SetIn4PWM(uint8_t duty)
{
    __HAL_TIM_SET_COMPARE(IN4_TIM, IN4_CH, duty);
}

/**
 * @brief 初始化
 */
void MOTOR_Init(void)
{
    HAL_TIM_PWM_Start(IN1_TIM, IN1_CH);
    HAL_TIM_PWM_Start(IN2_TIM, IN2_CH);
    HAL_TIM_PWM_Start(IN3_TIM, IN3_CH);
    HAL_TIM_PWM_Start(IN4_TIM, IN4_CH);
}

/**
 * @brief 设置衰减模式
 * @param mode 衰减模式
 */
void MOTOR_SetDecayMode(DecayMode mode)
{
    currentDecayMode = mode;
}

/**
 * @brief 控制电机A前进
 * @param speed 速度值（0-100）
 */
void A_Backward(uint8_t speed)
{
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;
    
    if (currentDecayMode == FAST_DECAY) {
        __SetIn1PWM(speed);
        __SetIn2PWM(0);
    } else {
        __SetIn1PWM(MAX_SPEED);
        __SetIn2PWM(MAX_SPEED - speed);
    }
}

/**
 * @brief 控制电机B前进
 * @param speed 速度值（0-100）
 */
void B_Forward(uint8_t speed)
{
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;

    if (currentDecayMode == FAST_DECAY) {
        __SetIn3PWM(speed);
        __SetIn4PWM(0);
    } else {
        __SetIn3PWM(MAX_SPEED);
        __SetIn4PWM(MAX_SPEED - speed);
    }
}

/**
 * @brief 控制电机A后退
 * @param speed 速度值（0-100）
 */
void A_Forward(uint8_t speed)
{
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;
    
    if (currentDecayMode == FAST_DECAY) {
        __SetIn1PWM(0);
        __SetIn2PWM(speed);
    } else {
        __SetIn1PWM(MAX_SPEED - speed);
        __SetIn2PWM(MAX_SPEED);
    }
}

/**
 * @brief 控制电机B后退
 * @param speed 速度值（0-100）
 */
void B_Backward(uint8_t speed)
{
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;

    if (currentDecayMode == FAST_DECAY) {
        __SetIn3PWM(0);
        __SetIn4PWM(speed);
    } else {
        __SetIn3PWM(MAX_SPEED - speed);
        __SetIn4PWM(MAX_SPEED);
    }
}

/**
 * @brief 电机A刹车
 */
void A_Brake(void)
{
    __SetIn1PWM(MAX_SPEED);
    __SetIn2PWM(MAX_SPEED);
}

/**
 * @brief 电机A滑行
 */
void A_Coast(void)
{
    __SetIn1PWM(0);
    __SetIn2PWM(0);
}

/**
 * @brief 电机B刹车
 */
void B_Brake(void)
{
    __SetIn3PWM(MAX_SPEED);
    __SetIn4PWM(MAX_SPEED);
}

/**
 * @brief 电机B滑行
 */
void B_Coast(void)
{
    __SetIn3PWM(0);
    __SetIn4PWM(0);
}

/**
 * @brief 右转
 */
void RIGHT(void)
{
	A_Forward(70);
	B_Backward(25);
	//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 157);
}

/**
 * @brief 右急转
 */
void LEFT_IMM(void)
{
	B_Forward(75);
	A_Backward(25);
	//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 157);
}

/**
 * @brief 左转
 */
void LEFT(void)
{
	A_Backward(20);
	B_Forward(75);
	//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 52);
}

/**
 * @brief 左急转
 */
void RIGHT_IMM(void)
{
	A_Forward(70);
	B_Backward(30);
	//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 157);
}
