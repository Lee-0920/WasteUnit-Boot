/**
#include <System.h>
 * @addtogroup module_Driver
 * @{
 */

/**
 * @file
 * @brief MCU 核心系统驱动。
 * @details 配置 MCU 的时钟、功耗模式、中断等系统核心参数，提供复位、延时、电源管理等功能接口。
 * @version 1.1.0
 * @author kim.xiejinqiang
 * @date 2012-10-30
 */

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Tracer/Trace.h"
/**
 * @brief 初始化优先级分组和节拍定时器
 */
void System_Init(void)
{
    RCC_ClocksTypeDef RCC_Clocks;
    //设置向量表的位置和偏移量
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
    //设置为优先级组4，4位都用于保存抢占式优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    //配置节拍频率
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / configTICK_RATE_HZ);
    //配置节拍定时器的时钟为最低优先级
    NVIC_SetPriority(SysTick_IRQn, 0xf);
}


/**
 * @brief 打开系统的总中断。
 */
void System_EnableMasterInterrupt(void)
{
//    __ASM volatile("cpsie i");
}

/**
 * @brief 关闭系统的总中断。
 */
void System_DisableMasterInterrupt(void)
{
//    __ASM volatile("cpsid i");
}

/**
 * @brief 软件延时（毫秒）。
 * @param mSec 要延时的毫秒数。
 */
void System_Delay(unsigned int mSec)
{
    vTaskDelay(mSec/portTICK_RATE_MS);
}

/**
 * @brief 软件延时（微秒）。
 * @param uSec 要延时的微秒数。
 */
void System_DelayUs(unsigned int uSec)
{

}

/**
 * @brief 软件延时（秒）。
 * @param sec 要延时的秒数。
 */
void System_DelaySec(unsigned int sec)
{

}


/**
 * @brief 打开电源开关。
 */
void System_PowerOn(void)
{
}

/**
 * @brief 关机。
 */
void System_PowerOff(void)
{
}

/**
 * @brief 系统复位。
 * @details 复位后，系统重新启动。
 */
void System_Reset(void)
{
    NVIC_SystemReset();
}

void System_PrintfFloat(unsigned char level, float value, unsigned char len)
{
    if(level <= g_traceLevel)
    {
        unsigned int IntegerPart;
        float DecimalPart;
        if(value < 0)
        {
            Printf("-");
            value *= -1;
        }

        IntegerPart = (unsigned int)value;
        Printf("%d.", IntegerPart);

        DecimalPart = value - IntegerPart;
        for(int i = 0; i < len; i++)
        {
            DecimalPart *= 10;
            Printf("%d", (unsigned int)DecimalPart % 10);
        }
    }
}

/** @} */
