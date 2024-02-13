/**
  ******************************************************************************
  * @file    USB_Host/MSC/Src/stm32l4xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitTypeDef  GPIO_Init4Struct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();

  UARTx_TX_GPIO_CLK_ENABLE();
  UARTx_RX_GPIO_CLK_ENABLE();

  /* Enable USARTx clock */
  USARTx_CLK_ENABLE();

  UARTx_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

    GPIO_Init4Struct.Pin       = UARTx_TX_PIN;
    GPIO_Init4Struct.Mode      = GPIO_MODE_AF_PP;
    GPIO_Init4Struct.Pull      = GPIO_PULLUP;
    GPIO_Init4Struct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_Init4Struct.Alternate = UARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  HAL_GPIO_Init(UARTx_TX_GPIO_PORT, &GPIO_Init4Struct);


  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  GPIO_Init4Struct.Pin = UARTx_RX_PIN;
  GPIO_Init4Struct.Alternate = UARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

  HAL_GPIO_Init(UARTx_RX_GPIO_PORT, &GPIO_Init4Struct);

  /* USART1 interrupt Init */
     HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
     HAL_NVIC_EnableIRQ(USART1_IRQn);
   /* USER CODE BEGIN USART1_MspInit 1 */

     /* UART4 interrupt Init */
        HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
      /* USER CODE BEGIN UART4_MspInit 1 */

}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  UARTx_FORCE_RESET();
  UARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);

  HAL_GPIO_DeInit(UARTx_TX_GPIO_PORT, UARTx_TX_PIN);

  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

  HAL_GPIO_DeInit(UARTx_RX_GPIO_PORT, UARTx_RX_PIN);

  /* USART1 interrupt DeInit */
   HAL_NVIC_DisableIRQ(USART1_IRQn);
   HAL_NVIC_DisableIRQ(UART4_IRQn);
 /* USER CODE BEGIN USART1_MspDeInit 1 */

}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

