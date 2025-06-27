/**
 * @file main.c
 * @brief 
 * @details
 *
 * @version 1.0.0
 * @author xingfan
 * @date 2016-4-28
 */



#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx.h"
#include "System.h"
#include "console/Console.h"
#include "CmdLine.h"
#include "DncpStack.h"
#include "UpdateDriver.h"
#include "DeviceInfo.h"
#include "DeviceIndicatorLED.h"
#include "Watchdog.h"
#include "DeviceUpdate/UpdateHandle.h"
#include "Driver/DefaultDevice.h"
#include "Driver/HardwareType.h"

int main(void)
{
    System_Init();
    // 功能模块初始化
    Console_Init();
    CmdLine_Init();

    UpdateDriver_Boot();
    DeviceIndicatorLED_Init();
    HardwareType_Init();

    DefaultDevice_Init();

    Watchdog_Init();
    DncpStack_Init();
    DeviceInfo_Init();
    UpdateHandle_Init();

    vTaskStartScheduler();

    /* Infinite loop */
    while (1)
    {
    }
}


#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
 * @}
 */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
