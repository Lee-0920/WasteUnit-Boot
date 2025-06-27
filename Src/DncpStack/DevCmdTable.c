/**
 * @addtogroup module_DncpStack
 * @{
 */

/**
 * @file
 * @brief 设备命令表。
 * @version 1.0.0
 * @author kim.xiejinqiang
 * @date 2013-3-19
 */

#include <string.h>
#include "Common/Utils.h"
#include "Driver/System.h"
#include "Common/Types.h"
#include "DevCmdTable.h"
#include "DeviceInfo.h"
#include "DeviceStatus.h"
#include "DeviceUpdate.h"

//*******************************************************************
// 应用命令实现

/**
 * 命令接口的版本号。
 * 每一次接口命令的调整，都应该变更这个版本号。
 */
static const DscpVersion s_kDscpInterfaceVersion =
{
        1,      // 主版本号
        2,      // 次版本号
        0,      // 修订版本号
        0       // 编译版本号
};

/*
 * 各应用相关的命令的入口函数都需要添加到这里。
 * 每一条命令对应一个命令码和处理函数。
 */
static const DscpCmdEntry s_kDscpCmdTable[] =
{
    CMD_TABLE_DEVICE_INFO,
    CMD_TABLE_DEVICE_STATUS,
    CMD_TABLE_DEVICE_UPDATE,
};

DscpCmdTable DevCmdTable_GetTable(void)
{
    return (DscpCmdTable) s_kDscpCmdTable;
}

DscpVersion DevCmdTable_GetVersion(void)
{
    return s_kDscpInterfaceVersion;
}

/** @} */
