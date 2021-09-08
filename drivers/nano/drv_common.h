/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-7      SummerGift   first version
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include <ch32v30x.h>

#ifdef __cplusplus
extern "C" {
#endif

void _Error_Handler(char *s, int num);

#ifndef Error_Handler
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif

#define DMA_NOT_AVAILABLE ((DMA_INSTANCE_TYPE *)0xFFFFFFFFU)

#define __CH32_PORT(port)  GPIO##port##_BASE
#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__CH32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

#define CH32_FLASH_START_ADRESS       ROM_START
#define CH32_FLASH_SIZE               ROM_SIZE
#define CH32_FLASH_END_ADDRESS        ROM_END

#define CH32_SRAM1_SIZE               RAM_SIZE
#define CH32_SRAM1_START              RAM_START
#define CH32_SRAM1_END                RAM_END

extern int _ebss;
#define HEAP_BEGIN      ((void *)&_ebss)


#define HEAP_END                      CH32_SRAM1_END

#ifdef __cplusplus
}
#endif

#endif
