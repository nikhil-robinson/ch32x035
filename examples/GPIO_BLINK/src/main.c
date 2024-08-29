/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/26
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *GPIO routine:
 *PA0 push-pull output.
 *
 ***Only PA0--PA15 and PC16--PC17 support input pull-down.
 */

#include "debug.h"

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u8 i = 0;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    // USART_Printf_Init(115200);
    // printf("SystemClk:%d\r\n", SystemCoreClock);
    // printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    // printf("GPIO Toggle TEST\r\n");
    GPIO_Toggle_INIT();

    while (1)
    {
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (Bit_SET) : (Bit_RESET));
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, (i == 0) ? (Bit_SET) : (Bit_RESET));
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, (i == 0) ? (Bit_SET) : (Bit_RESET));
        GPIO_WriteBit(GPIOA, GPIO_Pin_3, (i == 0) ? (Bit_SET) : (Bit_RESET));
        GPIO_WriteBit(GPIOA, GPIO_Pin_6, (i == 0) ? (Bit_SET) : (Bit_RESET));

        GPIO_WriteBit(GPIOB, GPIO_Pin_12, (i == 0) ? (Bit_SET) : (Bit_RESET));
        GPIO_WriteBit(GPIOB, GPIO_Pin_1, (i == 0) ? (Bit_SET) : (Bit_RESET));

        GPIO_WriteBit(GPIOC, GPIO_Pin_14, (i == 0) ? (Bit_SET) : (Bit_RESET));
        GPIO_WriteBit(GPIOC, GPIO_Pin_15, (i == 0) ? (Bit_SET) : (Bit_RESET));

        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
        {
            i = !i;
            Delay_Ms(100);
        }
    }
}
