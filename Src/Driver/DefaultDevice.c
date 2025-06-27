/*
 * DefaultDriver.c
 *
 *  Created on: 2020年2月14日
 *      Author: Administrator
 */
#include "DefaultDevice.h"

// 加热丝1
#define HEATER1_PIN                        GPIO_Pin_8
#define HEATER1_PORT                       GPIOC
#define HEATER1_RCC                        RCC_AHB1Periph_GPIOC
#define HEATER1_ON()                       GPIO_SetBits(HEATER1_PORT, HEATER1_PIN)
#define HEATER1_OFF()                      GPIO_ResetBits(HEATER1_PORT, HEATER1_PIN)


// 风扇1
#define FAN1_PIN                           GPIO_Pin_9
#define FAN1_PORT                          GPIOC
#define FAN1_RCC                           RCC_AHB1Periph_GPIOC
#define FAN1_ON()                          GPIO_SetBits(FAN1_PORT, FAN1_PIN)
#define FAN1_OFF()                         GPIO_ResetBits(FAN1_PORT, FAN1_PIN)


// 机箱风扇
#define BOXFAN_PIN                         GPIO_Pin_8
#define BOXFAN_PORT                        GPIOA
#define BOXFAN_RCC                         RCC_AHB1Periph_GPIOA
#define BOXFAN_ON()                        GPIO_SetBits(BOXFAN_PORT, BOXFAN_PIN)
#define BOXFAN_OFF()                       GPIO_ResetBits(BOXFAN_PORT, BOXFAN_PIN)

// 定量LED
#define METERLED1_PIN                      GPIO_Pin_6
#define METER1_PORT                        GPIOA
#define METER1_RCC                         RCC_AHB1Periph_GPIOA
#define METER1_ON()                        GPIO_SetBits(METER1_PORT, METERLED1_PIN)
#define METER1_OFF()                       GPIO_ResetBits(METER1_PORT, METERLED1_PIN)

#define METERLED2_PIN                      GPIO_Pin_7
#define METER2_PORT                        GPIOA
#define METER2_RCC                         RCC_AHB1Periph_GPIOA
#define METER2_ON()                        GPIO_SetBits(METER2_PORT, METERLED2_PIN)
#define METER2_OFF()                       GPIO_ResetBits(METER2_PORT, METERLED2_PIN)

void DefaultDevice_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(HEATER1_RCC | FAN1_RCC | BOXFAN_RCC | METER1_RCC | METER2_RCC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = HEATER1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(HEATER1_PORT, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = FAN1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(FAN1_PORT, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = BOXFAN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(BOXFAN_PORT, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = METERLED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(METER1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = METERLED2_PIN;
	GPIO_Init(METER2_PORT, &GPIO_InitStructure);

    //器件默认关闭
    HEATER1_OFF();
    FAN1_OFF();
    BOXFAN_OFF();
    METER1_OFF();
    METER1_OFF();
}
