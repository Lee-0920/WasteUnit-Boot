/*
 * Watchdog.c
 *
 *  Created on: 2016年10月14日
 *      Author: LIANG
 */

#include "stm32F4xx.h"
#include "Common/Types.h"
#include "SystemConfig.h"
#include <string.h>

#define WATCHDOG_PRER    6//分频数:低3位有效
//分频因子 = 4 * 2 ^ PRER 最大值为256
#define WATCHDOG_RLR     1250//重装载值:低11位有效
//时间计算:tout = ((4 * 2 ^ PRER) * RLR) / 32 (ms)

#define TIM_PERIOD         2499
#define TIM_PRESCALER      8999
#define WATCHDOG_TIM       TIM5
#define TIM_RCC            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE)
#define TIM_IRQN           TIM5_IRQn
#define TIM_HANDLER        TIM5_IRQHandler
//中断时间计算
//Tout= ((TIM_PERIOD + 1) * (TIM_PRESCALER + 1)) / Tclk
//Tclk 定时器的输入时钟频率（单位为 Mhz）,APB1为90M, APB2为180M
//TIM_PERIOD 重装载寄存器周期值
//TIM_PRESCALER 时钟频率的预分频值
static void Watchdog_Config(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//使能对寄存器 I 写操作
    IWDG_SetPrescaler(WATCHDOG_PRER);//设置 IWDG 预分频值
    IWDG_SetReload(WATCHDOG_RLR);//设置 IWDG 重装载值
    IWDG_ReloadCounter();//按照 IWDG 重装载寄存器的值重装载 IWDG 计数器
    IWDG_Enable();
}

static void Watchdog_Feed(void)
{
    IWDG_ReloadCounter();
}

static void Watchdog_TIMInit(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    memset(&TIM_TimeBaseStructure, 0, sizeof(TIM_TimeBaseStructure));
    TIM_RCC;

    TIM_TimeBaseStructure.TIM_Period = TIM_PERIOD;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_Prescaler = TIM_PRESCALER;
    TIM_TimeBaseInit(WATCHDOG_TIM, &TIM_TimeBaseStructure);
    TIM_ClearFlag(WATCHDOG_TIM, TIM_IT_Update); //避免定时器启动时进入中断服务程序
    TIM_ITConfig(WATCHDOG_TIM, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = WATCHDOG_IRQ_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(WATCHDOG_TIM,ENABLE);
}

void Watchdog_Init(void)
{
    Watchdog_Config();
    Watchdog_TIMInit();
}

void TIM_HANDLER(void)
{
    if(TIM_GetITStatus(WATCHDOG_TIM, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(WATCHDOG_TIM, TIM_IT_Update);
        Watchdog_Feed();
    }
}



