/**
 * @addtogroup module_CmdLine
 * @{
 */

/**
 * @file
 * @brief 应用接口：命令行实现。
 * @details 定义各应用命令及其处理函数。
 * @version 1.0.0
 * @author kim.xiejinqiang
 * @date 2012-5-21
 */


#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdlib.h>
#include "Tracer/Trace.h"
#include "Console/Console.h"
#include "Driver/System.h"
#include "CmdLine.h"
#include "SystemConfig.h"
#include "DeviceIndicatorLED.h"
#include "UpdateDriver.h"
#include "DeviceUpdate/UpdateHandle.h"
#include "McuFlash.h"
#include "Driver/HardwareType.h"
// 命令行版本定义，命令有变更时，需要相应更新本版本号
const CmdLineVersion g_kCmdLineVersion =
{
        1,      // 主版本号
        0,      // 次版本号
        0,      // 修订版本号
        0       // 编译版本号
};

// 命令处理函数声明列表
static int Cmd_help(int argc, char *argv[]);
static int Cmd_welcome(int argc, char *argv[]);
static int Cmd_version(int argc, char *argv[]);
static int Cmd_showparam(int argc, char *argv[]);
static int Cmd_reset(int argc, char *argv[]);
static int Cmd_trace(int argc, char *argv[]);
static int Cmd_demo(int argc, char *argv[]);

//系统命令
static int Cmd_flash(int argc, char *argv[]);
static int Cmd_IAP(int argc, char *argv[]);
static int Cmd_SetBlink(int argc, char *argv[]);
static int Cmd_Hardware(int argc, char *argv[]);
/**
 * @brief 命令行命令表，保存命令关键字与其处理函数之间的对应关系。
 * @details 每条命令对应一个结点，结点包括：命令关键字、处理函数、简短描述文本。
 */
const CmdLineEntry g_kConsoleCmdTable[] =
{
    { "demo",       Cmd_demo,       "\t\t: Demo for cmd implementation and param parse" },
    { "trace",      Cmd_trace,      "\t\t: Trace level" },
    { "welcome",    Cmd_welcome,    "\t\t: Display welcome message" },
    { "version",    Cmd_version,    "\t\t: Display version infomation about this application" },
    { "reset",      Cmd_reset,      "\t\t: Reset system" },
    { "help",       Cmd_help,       "\t\t: Display list of commands. Short format: h or ?" },

    { "flash",      Cmd_flash,      "\t\t: Flash read write erase operation." },
    { "iap",        Cmd_IAP,         "\t\t:Provides erase and jump operations." },
    { "blink",      Cmd_SetBlink,    "\t\t:Set the duration of equipment indicator, on time and off time.Uint milliseconds." },
    { "hardware",  Cmd_Hardware,  "\t\t: Read Hardware Info." },
    { "?",          Cmd_help,       0 },
    { "h",          Cmd_help,       0 },
    { "showparam",  Cmd_showparam,  0 },
    { 0, 0, 0 }
};


/**
 * @brief 判断第一个字串等于第二个字串。
 * @details 本函数与strcmp相比，预先做了有效性检查。
 * @param str1 要比较的字串1。
 * @param str2 要比较的字串2，不能为NULL。
 * @return 是否相等。
 */
Bool IsEqual(const char* str1, const char* str2)
{
    return (0 == strcmp(str1, str2)) ? TRUE : FALSE;
}

void CmdLine_Init(void)
{

}
int Cmd_Hardware(int argc, char *argv[])
{
    Uint8 type = 0;
    if (IsEqual(argv[1], "type"))
    {
        type = HardwareType_GetValue();
        Printf("Hardware Type: %d\n", type);
    }
    else if (0 == argv[1] || IsEqual(argv[1], "help") ||
             IsEqual(argv[1], "?"))
    {
        Printf("====== hardware commands ======\n");
        Printf(" type : get hardware type value\n");
    }
}

int Cmd_SetBlink(int argc, char *argv[])
{
    if (argv[1])
    {
        if (argv[2] && argv[3])
        {
            DeviceIndicatorLED_SetBlink(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        }
        else
        {
            Printf("Invalid param\n");
        }
    }
    else if (0 == argv[1] || IsEqual(argv[1], "help") ||
             IsEqual(argv[1], "?"))
    {
        Printf("====== blink commands ======\n");
        Printf(" blink [DURATION] [ONTIME] [OFFTIME]:\n");
    }

    return (0);
}

int Cmd_IAP(int argc, char *argv[])
{
    if (IsEqual(argv[1], "erase"))
    {
        UpdateHandle_StartErase();
    }
    else if (IsEqual(argv[1], "write"))
    {
        if (argv[2] && argv[3] && argv[4])
        {
            UpdateHandle_WriteProgram((u8 *)argv[2], atoi(argv[3]), atoi(argv[4]));
        }
        else
        {
            Printf("Invalid param\n");
        }
    }
    else if (IsEqual(argv[1], "check"))
    {
        if (argv[2])
        {
            UpdateHandle_CheckIntegrity(atoi(argv[2]));
        }
        else
        {
            Printf("Invalid param\n");
        }
    }
    else if (IsEqual(argv[1], "read"))
    {
        if (argv[2] && argv[3])
        {
            uint8_t str[30]={""};
            UpdateDriver_Read(atoi(argv[2]),atoi(argv[3]),str);
            Printf("\n");
            for(int i = 0; i< atoi(argv[3]); i++)
            {
                Printf("0x%02x ",str[i]);
            }
            Printf("\n%s",str);
        }
        else
        {
            Printf("Invalid param\n");
        }
    }
    else if (IsEqual(argv[1], "getmax"))
    {
        Printf("%d\n", UpdateHandle_GetMaxFragmentSize());
    }
    else if (IsEqual(argv[1], "getmode"))
    {
        DeviceRunMode mode = UpdateHandle_GetRunMode();
        Printf("%d\n", mode);
    }
#ifdef _CS_APP
    else if (IsEqual(argv[1], "updater"))
    {
        UpdateHandle_EnterUpdater();
    }
#else
    else if (IsEqual(argv[1], "app"))
    {
        UpdateHandle_EnterApplication();
    }
#endif
    else if (0 == argv[1] || IsEqual(argv[1], "help") ||
             IsEqual(argv[1], "?"))
    {
        Printf("====== iap commands ======\n");
        Printf(" iap erase: \n");
        Printf(" iap write [TEXT]   [NUM]  [SEQ]: \n");
        Printf(" iap check [CRC16]              : \n");
        Printf(" iap read  [OFFSET] [NUM]       : \n");
#ifdef _CS_APP
        Printf(" iap updater                    : \n");
#else
        Printf(" iap app                        : \n");
#endif
        Printf(" iap getmax                     : \n");
        Printf(" iap getmode                    : \n");
    }
    else
    {
        Printf("Invalid param: %s\n", argv[1]);
    }
    return (0);
}

int Cmd_flash(int argc, char *argv[])
{
    if (IsEqual(argv[1], "deletewrite"))//不保留原始数据的写
    {
        if (argv[2] && argv[3] && argv[4])
        {
            McuFlash_DeleteWrite(atoi(argv[2]), atoi(argv[3]),(u8 *)argv[4]);
            Printf("\nWriteAddr 0x%x ",atoi(argv[2]));
        }
        else
        {
            Printf("Invalid param\n");
        }
    }
    else if (IsEqual(argv[1], "write"))//保留原始数据的写
    {
        if (argv[2] && argv[3] && argv[4])
        {
            McuFlash_Write(atoi(argv[2]), atoi(argv[3]),(u8 *)argv[4]);
            Printf("\nWriteAddr 0x%x ",atoi(argv[2]));
        }
        else
        {
            Printf("Invalid param\n");
        }
    }
    else if (IsEqual(argv[1], "read"))//读FLASH数据
    {
        if (argv[2] && argv[3])
        {
            uint8_t str[30]={""};
            McuFlash_Read(atoi(argv[2]),atoi(argv[3]),str);
            Printf("\nReadAddr 0x%x\n",atoi(argv[2]));
            for(int i = 0; i< atoi(argv[3]); i++)
            {
                Printf("0x%02x ",str[i]);
            }
            Printf("\n%s",str);
        }
        else
        {
            Printf("Invalid param\n");
        }
    }
    else if (IsEqual(argv[1], "erase"))//擦除
    {
        if (argv[2])
        {
           McuFlash_EraseSector(atoi(argv[2]));
           Printf("\nEraseAddr 0x%x", atoi(argv[2]));
        }
        else
        {
            Printf("Invalid param\n");
        }

    }
    else if (0 == argv[1] || IsEqual(argv[1], "help") ||
             IsEqual(argv[1], "?"))
    {
        Printf("====== flash commands ======\n");
        Printf(" flash deletewrite [ADDR] [NUM] [TEXT]: \n");
        Printf(" flash write       [ADDR] [NUM] [TEXT]: \n");
        Printf(" flash read        [ADDR] [NUM]       : \n");
        Printf(" flash erase       [ADDR]             : \n");
    }
    else
    {
        Printf("Invalid param: %s\n", argv[1]);
    }
    return (0);
}

//*****************************************************************************
//
// 命令处理函数
//
//*****************************************************************************
// 显示帮助，简单显示命令列表
int Cmd_help(int argc, char *argv[])
{
    CmdLineEntry *cmdEntry;

    ConsoleOut("\nAvailable commands\n");
    ConsoleOut("------------------\n");

    cmdEntry = (CmdLineEntry *) &g_kConsoleCmdTable[0];

    // 遍历整个命令表，打印出有提示信息的命令
    while (cmdEntry->cmdKeyword)
    {
        // 延时一下，等待控制台缓冲区空出足够的空间
        System_Delay(10);

        if (cmdEntry->cmdHelp)
            ConsoleOut("%s%s\n", cmdEntry->cmdKeyword, cmdEntry->cmdHelp);

        cmdEntry++;
    }

    return (0);
}

int Cmd_version(int argc, char *argv[])
{
    ConsoleOut("Version: %d.%d.%d.%d\n",
            g_kCmdLineVersion.major,
            g_kCmdLineVersion.minor,
            g_kCmdLineVersion.revision,
            g_kCmdLineVersion.build
            );
    return(0);
}

int Cmd_welcome(int argc, char *argv[])
{
    Console_Welcome();
    return(0);
}


// 显示参数
int Cmd_showparam(int argc, char *argv[])
{
    int i = 0;

    ConsoleOut("The params is:\n");
    for (i = 1; i < argc; i++)
    {
        ConsoleOut("    Param %d: %s\n", i, argv[i]);
    }

    return(0);
}


int Cmd_reset(int argc, char *argv[])
{
    Printf("\n\n\n");
    System_Delay(10);
    System_Reset();
    return (0);
}

int Cmd_trace(int argc, char *argv[])
{
    if (argv[1])
    {
        Trace_SetLevel(atoi(argv[1]));
    }
    else
    {
        Printf("L: %d\n", Trace_GetLevel());
    }

    return (0);
}

// 命令处理函数示例
int Cmd_demo(int argc, char *argv[])
{
    if (IsEqual(argv[1], "subcmd1"))
    {
        if (IsEqual(argv[2], "param"))
        {
            // 调用相关功能函数
            Printf("Exc: subcmd1 param");
        }
    }
    else if (IsEqual(argv[1], "subcmd2"))
    {
        Printf("Exc: subcmd2");
    }
    else if (0 == argv[1] || IsEqual(argv[1], "help") ||
             IsEqual(argv[1], "?"))
    {
        Printf("====== Sub commands ======\n");
        Printf(" mycmd subcmd1 param : Sub command description\n");
        Printf(" mycmd subcmd2       : Sub command description\n");
    }
    else
    {
        Printf("Invalid param: %s\n", argv[1]);
    }

    return (0);
}


/** @} */
