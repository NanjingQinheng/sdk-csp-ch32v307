/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     SummerGift   first version
 * 2019-01-03     zylx         modify dma support
 * 2020-05-18     chenyaxing   modify uart_config struct
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .Instance = USART1,                                         \
        .irq_type = USART1_IRQn,                                    \
        .tx_pin_name = BSP_UART1_TX_PIN,                            \
        .rx_pin_name = BSP_UART1_RX_PIN,                            \
    }
#endif /* UART1_CONFIG */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                                \
    {                                                               \
        .name = "uart2",                                            \
        .Instance = USART2,                                         \
        .irq_type = USART2_IRQn,                                    \
        .tx_pin_name = BSP_UART2_TX_PIN,                            \
        .rx_pin_name = BSP_UART2_RX_PIN,                            \
    }
#endif /* UART2_CONFIG */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = USART3,                                         \
        .irq_type = USART3_IRQn,                                    \
        .tx_pin_name = BSP_UART3_TX_PIN,                            \
        .rx_pin_name = BSP_UART3_RX_PIN,                            \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                                \
    {                                                               \
        .name = "uart4",                                            \
        .Instance = UART4,                                          \
        .irq_type = UART4_IRQn,                                     \
        .tx_pin_name = BSP_UART4_TX_PIN,                            \
        .rx_pin_name = BSP_UART4_RX_PIN,                            \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                                \
    {                                                               \
        .name = "uart5",                                            \
        .Instance = UART5,                                          \
        .irq_type = UART5_IRQn,                                     \
        .tx_pin_name = BSP_UART5_TX_PIN,                            \
        .rx_pin_name = BSP_UART5_RX_PIN,                            \
    }
#endif /* UART5_CONFIG */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                                \
    {                                                               \
        .name = "uart6",                                            \
        .Instance = UART6,                                         \
        .irq_type = UART6_IRQn,                                    \
        .tx_pin_name = BSP_UART6_TX_PIN,                            \
        .rx_pin_name = BSP_UART6_RX_PIN,                            \
    }
#endif /* UART6_CONFIG */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG                                                \
    {                                                               \
        .name = "uart7",                                            \
        .Instance = UART7,                                          \
        .irq_type = UART7_IRQn,                                     \
        .tx_pin_name = BSP_UART7_TX_PIN,                            \
        .rx_pin_name = BSP_UART7_RX_PIN,                            \
    }
#endif /* UART7_CONFIG */
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_UART8)
#ifndef UART8_CONFIG
#define UART8_CONFIG                                                \
    {                                                               \
        .name = "uart8",                                            \
        .Instance = UART8,                                          \
        .irq_type = UART8_IRQn,                                     \
        .tx_pin_name = BSP_UART8_TX_PIN,                            \
        .rx_pin_name = BSP_UART8_RX_PIN,                            \
    }
#endif /* UART8_CONFIG */
#endif /* BSP_USING_UART8 */

#ifdef __cplusplus
}
#endif

#endif
