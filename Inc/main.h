/**
  ******************************************************************************
  * @file    FatFs/FatFs_USBDisk/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "usbh_core.h"
#include "stm32l475e_iot01.h"
#include "usbh_msc.h" 
#include "ff.h"
#include "ff_gen_drv.h"
#include "usbh_diskio_dma.h"
#include <stdint.h> 
/* Exported types ------------------------------------------------------------*/
extern FATFS USBH_fatfs;
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */

/*-------------------------------------------------------------USARTx*/
#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_6
#define USARTx_TX_GPIO_PORT              GPIOB
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_7
#define USARTx_RX_GPIO_PORT              GPIOB
#define USARTx_RX_AF                     GPIO_AF7_USART1


/*--------------------------------------------------------------UARTX*/
/* Definition for UARTx clock resources */
#define UARTx                           UART4
#define UARTx_CLK_ENABLE()              __HAL_RCC_UART4_CLK_ENABLE();
#define UARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define UARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define UARTx_FORCE_RESET()             __HAL_RCC_UART4_FORCE_RESET()
#define UARTx_RELEASE_RESET()           __HAL_RCC_UART4_RELEASE_RESET()

/* Definition for UARTx Pins */
#define UARTx_TX_PIN                    GPIO_PIN_0
#define UARTx_TX_GPIO_PORT              GPIOA
#define UARTx_TX_AF                     GPIO_AF8_UART4
#define UARTx_RX_PIN                    GPIO_PIN_1
#define UARTx_RX_GPIO_PORT              GPIOA
#define UARTx_RX_AF                     GPIO_AF8_UART4



#endif /* __MAIN_H */

