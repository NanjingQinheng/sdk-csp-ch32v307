/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH       first version
 */

#include <board.h>
#include <rtthread.h>
#include <ch32v30x.h>
#include "drv_common.h"

#define DBG_TAG "board"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void system_clock_config(int target_freq_Mhz)
{
    /* system_clock have been configured in start.S */
}

int clock_information(void)
{
    RCC_ClocksTypeDef RCC_ClocksStatus={0};
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    LOG_D("System Clock information");
    LOG_D("SYSCLK_Frequency = %d", RCC_ClocksStatus.SYSCLK_Frequency);
    LOG_D("HCLK_Frequency   = %d", RCC_ClocksStatus.HCLK_Frequency);
    LOG_D("PCLK1_Frequency  = %d", RCC_ClocksStatus.PCLK1_Frequency);
    LOG_D("PCLK2_Frequency  = %d", RCC_ClocksStatus.PCLK2_Frequency);
    LOG_D("ADCCLK_Frequency = %d", RCC_ClocksStatus.ADCCLK_Frequency);
    return RT_EOK;
}
INIT_BOARD_EXPORT(clock_information);

void clk_init(char *clk_source, int source_freq, int target_freq)
{
    /* system clock initiate at start.S */
    system_clock_config(target_freq);
}
