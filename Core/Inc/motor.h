
#ifndef __MOTOR_H_
#define __MOTOR_H_

#include <stdint.h>

/**
 * @brief 衰减模式枚举
 */
typedef enum {
    SLOW_DECAY,  /**< 慢衰减模式 */
    FAST_DECAY   /**< 快衰减模式 */
} DecayMode;

/**
 * @brief 初始化
 */
void MOTOR_Init(void);

/**
 * @brief 设置衰减模式
 * @param mode 衰减模式
 */
void MOTOR_SetDecayMode(DecayMode mode);

/**
 * @brief 控制电机A前进
 * @param speed 速度值（0-100）
 */
void A_Forward(uint8_t speed);

/**
 * @brief 控制电机A后退
 * @param speed 速度值（0-100）
 */
void A_Backward(uint8_t speed);

/**
 * @brief 电机A刹车
 */
void A_Brake(void);

/**
 * @brief 电机A滑行
 */
void A_Coast(void);

/**
 * @brief 控制电机B前进
 * @param speed 速度值（0-100）
 */
void B_Forward(uint8_t speed);

/**
 * @brief 控制电机B后退
 * @param speed 速度值（0-100）
 */
void B_Backward(uint8_t speed);

/**
 * @brief 电机B刹车
 */
void B_Brake(void);

/**
 * @brief 电机B滑行
 */
void B_Coast(void);

/**
 * @brief 右转
 */
void RIGHT(uint8_t speed);

/**
 * @brief 右急转
 */
void RIGHT_IMM(void);
void LEFT_IMM(void);

/**
* @brief 左转
*/
void LEFT(uint8_t speed);

#endif /* __MOTOR_H_ */
