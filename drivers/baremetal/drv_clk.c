/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH       first version
 */
#include <ch32v30x.h>
#include <stdio.h>


void system_clock_config(int target_freq_Mhz)
{
    /* system_clock have been configured in start.S */
}

int clock_information(void)
{
    RCC_ClocksTypeDef RCC_ClocksStatus={0};
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    printf("System Clock information\r\n");
    printf("SYSCLK_Frequency = %d\r\n", RCC_ClocksStatus.SYSCLK_Frequency);
    printf("HCLK_Frequency   = %d\r\n", RCC_ClocksStatus.HCLK_Frequency);
    printf("PCLK1_Frequency  = %d\r\n", RCC_ClocksStatus.PCLK1_Frequency);
    printf("PCLK2_Frequency  = %d\r\n", RCC_ClocksStatus.PCLK2_Frequency);
    printf("ADCCLK_Frequency = %d\r\n", RCC_ClocksStatus.ADCCLK_Frequency);
    return 0;
}

void wait_ms(unsigned long ms_time)
{
	Delay_Ms(ms_time);
}
