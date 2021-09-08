/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09      WCH      first version
 */

#include <ch32v30x.h>

extern int rt_hw_usart_init();
extern void system_clock_config(int);
extern int clock_information(void);


void clk_init(char *clk_source, int source_freq, int target_freq)
{
    /* disbale interrupt */
    __disable_irq();
    /* system clock config */
    system_clock_config(target_freq);
	Delay_Init();
    /* enable interrupt */
	__enable_irq();
}


int uart_init()
{
    rt_hw_usart_init();
    clock_information();
    return 0;
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char *s, int num)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    while(1)
    {
    }
    /* USER CODE END Error_Handler */
}

