/*
 * SystemConfig.h
 *
 *  Created on: 2016年6月7日
 *      Author: Administrator
 */

#ifndef SRC_SYSTEMCONFIG_H_
#define SRC_SYSTEMCONFIG_H_


//外设中断抢占式优先级配置=============================================================================
#define    WATCHDOG_IRQ_PRIORITY                    3
#define    LAIRS485ADAPTER_IRQ_PRIORITY             7
#define    CONSOLEUART_IRQ_PRIORITY                 7

//freeRTOS 任务优先级和堆栈大小配置===================================================================
#define CONSOLESCHEDULER_TASK_PRIO                  5
#define CONSOLESCHEDULER_STK_SIZE                   256

#define LAIRS485COMMITTOUPPER_TASK_PRIO             6
#define LAIRS485COMMITTOUPPER_STK_SIZE              256

#define LAIRS485SENDREQUEST_TASK_PRIO               6
#define LAIRS485SENDREQUEST_STK_SIZE                256

#define LAIRS485MONITORHOST_TASK_PRIO               6
#define LAIRS485MONITORHOST_STK_SIZE                128

#define DNCPSTACKDSCPCMD_TASK_PRIO                  6
#define DNCPSTACKDSCPCMD_STK_SIZE                   256

#define DEVICEINDICATOR_LED_TASK_PRIO               4
#define DEVICEINDICATOR_LED_STK_SIZE                128

#define UPDATER_ERASE_TASK_PRIO                     4
#define UPDATER_ERASE_STK_SIZE                      128
//用户FLASH地址和大小配置==============================================================================
#define UPDATE_FLASH_START                          0x08000000//UPDATE程序空间48K
#define UPDATE_FLASH_END                            0x0800BFFF
#define UPDATE_DATA_FLASH_START                     0x0800C000//UPDATE数据空间16K
#define UPDATE_DATA_FLASH_END                       0x0800FFFF
#define APP_DATA_FLASH_START                        0x08010000//APP数据空间64K
#define APP_DATA_FLASH_END                          0x0801FFFF
#define APP_FLASH_START                             0x08020000 
#define APP_FLASH_END                               0x081FFFFF

#define FLASH_FACTORY_SIGN                          0xAA55AA55
#define FLASH_USE_BASE                              UPDATE_DATA_FLASH_START

//共96byte
#define DEVICE_INFO_SIGN_FLASH_BASE_ADDR           FLASH_USE_BASE
#define DEVICE_INFO_SIGN_FLASH_LEN                  4
#define DEVICE_INFO_TYPE_ADDRESS                    (DEVICE_INFO_SIGN_FLASH_BASE_ADDR + DEVICE_INFO_SIGN_FLASH_LEN)
#define DEVICE_INFO_TYPE_LEN                        16
#define DEVICE_INFO_MODEL_ADDRESS                   (DEVICE_INFO_TYPE_ADDRESS + DEVICE_INFO_TYPE_LEN)
#define DEVICE_INFO_MODEL_LEN                       24
#define DEVICE_INFO_SN_ADDRESS                      (DEVICE_INFO_MODEL_ADDRESS + DEVICE_INFO_MODEL_LEN)
#define DEVICE_INFO_SN_LEN                          32
#define DEVICE_INFO_MANUF_ADDRESS                   (DEVICE_INFO_SN_ADDRESS +  DEVICE_INFO_SN_LEN)
#define DEVICE_INFO_MANUF_LEN                       20
#define DEVICE_INFO_DATE_ADDRESS                    (DEVICE_INFO_MANUF_ADDRESS + DEVICE_INFO_MANUF_LEN)
#define DEVICE_INFO_DATE_LEN                        4

//所有使用的内存 100  = 100
#define FLASH_USE_SIZE                              ((u16)200)

#endif /* SRC_SYSTEMCONFIG_H_ */
