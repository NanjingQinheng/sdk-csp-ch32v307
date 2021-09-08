/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-09     xiangxistu   first version
 * 2020-05-18     chenyaxing   modify stm32_uart_config struct
 */

#include "stdlib.h"
#include "drv_common.h"
#include "uart_config.h"


#define DBG_TAG              "drv.usart"

#ifdef DRV_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif

#include <rtdbg.h>

#ifdef RT_USING_CONSOLE


/*  uart driver */
struct ch32_uart
{
    USART_TypeDef *Instance;
    USART_InitTypeDef Init;
};
struct ch32_uart_config
{
    const char *name;
    USART_TypeDef *Instance;
    IRQn_Type irq_type;

    const char *tx_pin_name;
    const char *rx_pin_name;
};

static struct ch32_uart handle;
static struct ch32_uart_config *_uart_config = RT_NULL;

struct ch32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif
#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif
#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif
#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif
#ifdef BSP_USING_UART8
    UART8_CONFIG,
#endif
};


static rt_err_t ch32_uart_clk_enable(struct ch32_uart_config *config)
{
    /* uart clock enable */
    switch ((uint32_t)config->Instance)
    {
#ifdef BSP_USING_UART1
    case (uint32_t)USART1:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        break;
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    case (uint32_t)USART2:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        break;
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    case (uint32_t)USART3:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        break;
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
    case (uint32_t)UART4:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        break;
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
    case (uint32_t)UART5:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        break;
#endif /* BSP_USING_UART5 */

#ifdef BSP_USING_UART6
    case (uint32_t)UART6:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6, ENABLE);
        break;
#endif /* BSP_USING_UART6 */

#ifdef BSP_USING_UART7
    case (uint32_t)UART7:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
        break;
#endif /* BSP_USING_UART7 */

#ifdef BSP_USING_UART8
    case (uint32_t)UART8:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);
        break;
#endif /* BSP_USING_UART8 */
    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}
static rt_err_t ch32_gpio_clk_enable(GPIO_TypeDef *gpiox)
{
    /* gpio ports clock enable */
    switch ((uint32_t)gpiox)
    {
    #if defined(GPIOA)
        case (uint32_t)GPIOA:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            break;
    #endif
    #if defined(GPIOB)
        case (uint32_t)GPIOB:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            break;
    #endif
    #if defined(GPIOC)
        case (uint32_t)GPIOC:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
            break;
    #endif
    #if defined(GPIOD)
        case (uint32_t)GPIOD:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
            break;
    #endif
    #if defined(GPIOE)
        case (uint32_t)GPIOE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
            break;
    #endif
    #if defined(GPIOF)
        case (uint32_t)GPIOF:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
            break;
    #endif
    #if defined(GPIOG)
        case (uint32_t)GPIOG:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
            break;
    #endif

        default:
            return -RT_ERROR;
    }

    return RT_EOK;
}



static int up_char(char * c)
{
    if ((*c >= 'a') && (*c <= 'z'))
    {
        *c = *c - 32;
    }
    return 0;
}

static void get_pin_by_name(const char* pin_name, GPIO_TypeDef **port, uint16_t *pin)
{
    int pin_num = atoi((char*) &pin_name[2]);
    char port_name = pin_name[1];
    up_char(&port_name);
    up_char(&port_name);
    *port = ((GPIO_TypeDef *) ((uint32_t) GPIOA
            + (uint32_t) (port_name - 'A') * ((uint32_t) GPIOB - (uint32_t) GPIOA)));
    *pin = (GPIO_Pin_0 << pin_num);
}

static rt_err_t ch32_gpio_configure(struct ch32_uart_config *config)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef *tx_port;
    GPIO_TypeDef *rx_port;
    uint16_t tx_pin;
    uint16_t rx_pin;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    get_pin_by_name(config->rx_pin_name, &rx_port, &rx_pin);
    get_pin_by_name(config->tx_pin_name, &tx_port, &tx_pin);
    /* gpio ports clock enable */
    ch32_gpio_clk_enable(tx_port);
    if (tx_port != rx_port)
    {
        ch32_gpio_clk_enable(rx_port);
    }

    /* tx pin initialize */
    GPIO_InitStruct.GPIO_Pin = tx_pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(tx_port, &GPIO_InitStruct);

    /* rx pin initialize */
    GPIO_InitStruct.GPIO_Pin = rx_pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(rx_port, &GPIO_InitStruct);
    return RT_EOK;
}



static rt_err_t ch32_configure(struct ch32_uart_config *config)
{
    ch32_uart_clk_enable(config);

    handle.Instance                        = config->Instance;
    handle.Init.USART_BaudRate             = 115200;
    handle.Init.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    handle.Init.USART_Mode                 = USART_Mode_Rx|USART_Mode_Tx;
    handle.Init.USART_WordLength           = USART_WordLength_8b;
    handle.Init.USART_StopBits             = USART_StopBits_1;
    handle.Init.USART_Parity               = USART_Parity_No;

    USART_Init( handle.Instance,&handle.Init);
    USART_Cmd(handle.Instance, ENABLE);
    return RT_EOK;
}

int rt_hw_usart_init(void)
{
    _uart_config = &uart_config[0];
    ch32_gpio_configure(_uart_config);
    ch32_configure(_uart_config);
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);



void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            while (USART_GetFlagStatus(handle.Instance, USART_FLAG_TC) == RESET);
            handle.Instance->DATAR = a;
        }
        while (USART_GetFlagStatus(handle.Instance, USART_FLAG_TC) == RESET);
        handle.Instance->DATAR =  *(str + i);
    }
}


#ifdef RT_USING_FINSH
char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (USART_GetFlagStatus(handle.Instance, USART_FLAG_RXNE) != RESET)
    {
        ch = handle.Instance->DATAR & 0xff;
    }

    return ch;
}
#endif /* RT_USING_FINSH */
#endif/* RT_USING_CONSOLE */



