/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @brief   Main program body
  *          This sample code shows how to use FatFs with USB disk drive.
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
#include "string.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_rtc.h" // Includi il file di intestazione per il RTC
#include "stm32l4xx_hal_rtc.c"

#define HAL_RTC_MODULE_ENABLED


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
FIL MyFile;                   /* File object */
char USBDISKPath[4];          /* USB Host logical drive path */
USBH_HandleTypeDef hUSBHost; /* USB Host handle */

RTC_HandleTypeDef hrtc;


typedef enum {
  APPLICATION_IDLE = 0,
  APPLICATION_START,
  APPLICATION_RUNNING,
}MSC_ApplicationTypeDef;

MSC_ApplicationTypeDef Appli_state = APPLICATION_IDLE;
UART_HandleTypeDef UartHandle;
UART_HandleTypeDef Uart4Handle;


/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#define RX_BUFFER_SIZE 4096
#define TX_BUFFER_SIZE 1024

static void SystemClock_Config(void);
static void MX_RTC_Init(void);
static void Error_Handler(const char*);
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);
void MSC_Application(const uint8_t*,const TCHAR*);
void processReceivedData(uint8_t);
void initRxBuffer();
void deinitRxBuffer();

uint8_t lf = 0x0A;
uint8_t *rxBuffer;
uint8_t tx_buff[TX_BUFFER_SIZE];
uint8_t sdata;
uint8_t *data;
char SN[10];
int buf_index;
int buf_size;
int txflag;
const char* header = "Rec,DInizio,DEND,Ciclo,NFiltro,Linea,DPwrDown,LeakTest,SpanTest,VolIngr,VolStd,PercTEff,TExtMin,TExtMed,TExtMax,TFiltMin,TFiltMed,TFiltMax,PAtmMin,PAtmMed,PAtmMax,FlowRSD,InPDrop,CadPFin,CadPMax,DTMax,DataDTMax,OraDTMax,Time_dt>5,DTMed,Warning\r";

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32L4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();

  MX_RTC_Init();

  // Imposta la data e l'ora
  //    RTC_DateTypeDef sDate;
  //    RTC_TimeTypeDef sTime;

    tx_buff[0] = 0x34;
    tx_buff[1] = 0x34;
    tx_buff[2] = 0x0D;
    buf_index = 0;
    buf_size = RX_BUFFER_SIZE;

    SN[0] = '\0';
    data = NULL;
    txflag=0;

  /* Configure the system clock to 80 MHz */
  SystemClock_Config();
  //MX_RTC_Init();

  /* Enable Power Clock*/
  __HAL_RCC_PWR_CLK_ENABLE();

  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits (8 data bit + 0 parity bit) :
        BE CAREFUL :
             Program 7 data bits + 1 parity bit in PC HyperTerminal
      - Stop Bit    = One Stop bit
      - Parity      = None parity
      - BaudRate    = 115200 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance        = USARTx;
  UartHandle.Init.BaudRate   = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;

  Uart4Handle.Instance        = UARTx;
  Uart4Handle.Init.BaudRate   = 19200;
  Uart4Handle.Init.WordLength = UART_WORDLENGTH_8B;
  Uart4Handle.Init.StopBits   = UART_STOPBITS_1;
  Uart4Handle.Init.Parity     = UART_PARITY_NONE;
  Uart4Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  Uart4Handle.Init.Mode       = UART_MODE_TX_RX;

  if (HAL_UART_Init(&UartHandle) != HAL_OK || HAL_UART_Init(&Uart4Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler("uart or usart init error");
  }

  // HAL_UART_Receive_IT(&UartHandle, rxBuffer, 1); //interrupt serial

  initRxBuffer();

  //HAL_UART_Transmit(&Uart4Handle, "prova", 5, 0xFFFF);
  //USBH_UsrLog("VAFFA");


  /* Enable USB power on Pwrctrl CR2 register */
  HAL_PWREx_EnableVddUSB();

  /*##-1- Link the USB Host disk I/O driver ##################################*/
  if(FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == 0)
  {
    /*##-2- Init Host Library ################################################*/
    USBH_Init(&hUSBHost, USBH_UserProcess, 0);

    /*##-3- Add Supported Class ##############################################*/
    USBH_RegisterClass(&hUSBHost, USBH_MSC_CLASS);

    /*##-4- Start Host Process ###############################################*/
    USBH_Start(&hUSBHost);

    /*##-5- Run Application (Blocking mode) ##################################*/
    while (1)
    {
      /* USB Host Background task */
      USBH_Process(&hUSBHost);

      /* Mass Storage Application State Machine */
     switch(Appli_state)
    {
    case APPLICATION_START:
    	//const uint8_t myText[] = "demo write";
    	//const TCHAR* filename = _T("H0346");
    	//MSC_Application(myText,filename);
    	//USBH_UsrLog("started!\n");

    	HAL_UART_Transmit(&Uart4Handle, tx_buff, 3, 0xFFFF);
    	txflag=1;
    	//USBH_UsrLog("started with flag %d\n",txflag);
       Appli_state = APPLICATION_IDLE;
       break;
      case APPLICATION_IDLE:

    	  break;

     default:

    	 break;
      }


     if (UARTx->ISR & USART_ISR_RXNE) {  // se c'è un carattere in arrivo dalla seriale


    	 // Controlla e ridimensiona il buffer se necessario
    	                          if (buf_index >= buf_size - 1) { // Lascia spazio per '\0'
    	                              buf_size += RX_BUFFER_SIZE;
    	                              uint8_t *newBuffer = realloc(rxBuffer, buf_size * sizeof(char));
    	                              if (newBuffer == NULL) {
    	                                  // Gestione dell'errore di reallocazione della memoria
    	                                  free(rxBuffer);
    	                                  return 1;
    	                              }
    	                              rxBuffer = newBuffer;
    	                          }

         sdata = (uint8_t)(UARTx->RDR); // Leggi un byte dal buffer di ricezione di USARTx
         rxBuffer[buf_index++] = sdata;
         rxBuffer[buf_index] = '\0';

                    if ((strstr(rxBuffer, "\r\r\r") != NULL)) {

        	   //USBH_UsrLog("terminatore trovato, stringa: %s",rxBuffer);
        	   txflag=0;

        	   // Estrai SN
        	       char *startSN = strchr(rxBuffer, '=') + 1;
        	       if (startSN != NULL) {
        	           char *endSN = strchr(startSN, '\r');
        	           if (endSN != NULL && (endSN - startSN < sizeof(SN))) {
        	               strncpy(SN, startSN, endSN - startSN);
        	               SN[endSN - startSN] = '\0';  // Termina correttamente la stringa SN

        	           }
        	       }

        	       // Estrai data
        	       //char *startData = strchr(rxBuffer, '\r') + 1;  // Inizio dei dati dopo il primo '\r'
        	       char *startData = startSN + 8; // Inizio dei dati dopo il numero seriale (8 caratteri)
        	       if (startData != NULL) {
        	           char *endData = strstr(startData, "\r\r\r");  // Fine dei dati prima dei tre '\r'
        	           if (endData != NULL) {
        	               size_t dataSize = endData - startData;
        	               data = (char *)malloc(dataSize + 1);  // Alloca memoria per i dati
        	               if (data != NULL) {
        	                   strncpy(data, startData, dataSize);
        	                   data[dataSize] = '\0';  // Termina correttamente la stringa data
        	                   USBH_UsrLog("data: %s",data);
        	               }
        	           }
        	       }

        	       int bufferSize = strlen(header) + strlen((char *)data) + 1; // +1 per '\0'

        	             // Alloca il buffer per la stringa finale
        	             char *finalString = (char *)malloc(bufferSize);
        	             if (finalString == NULL) {
        	                 USBH_UsrLog("null final");
        	                 return; // Termina la funzione in caso di errore
        	             }

        	             // Costruisci la stringa finale
        	             strcpy(finalString, header);
        	             strcat(finalString, (char *)data);
        	             USBH_UsrLog("final: %s",finalString);
        	             USBH_UsrLog("SN: %s",SN);

        	       // Reset del buffer dopo l'elaborazione
        	       memset(rxBuffer, 0, RX_BUFFER_SIZE);
        	       buf_index = 0;

        	       strcat(SN,".csv");
        	       //USBH_UsrLog("serial:%s\nDATA:%s\nFinal:%s",SN,data,finalString);
        	       MSC_Application(finalString,SN);

        	       free(finalString); // libera la memoria allocata
   	               free(data);  // libera la memoria allocata
   	               SN[0] = '\0';


        	   } // end data reached

       } // end char received



    } // end infinite loop

   }  // end link usb stick init

  deinitRxBuffer(); // Pulisci alla fine
  return 0;
  /* Infinite loop */
  //for(;;);

} // end main


/**
  * @brief  Main routine for Mass Storage Class
  * @param  None
  * @retval None
  */
void MSC_Application(const uint8_t* wtext,const TCHAR* path){

	FRESULT res;                                          /* FatFs function common result code */
	  uint32_t byteswritten, bytesread;                     /* File write/read counts */
	  //uint8_t wtext[] = "This is hydra working with FatFs"; /* File write buffer */
	  uint8_t rtext[100];                                   /* File read buffer */

	  /* Register the file system object to the FatFs module */
	    if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
	    {
	      /* FatFs Initialization Error */
	      Error_Handler("mount error");
	    }
	    else
	    {
	      /* Create and Open a new text file object with write access */
	      if(f_open(&MyFile, path, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
	      {
	        /* path file Open for write Error */
	        Error_Handler("write open error");
	      }
	      else
	      {
	        /* Write data to the text file */
	        res = f_write(&MyFile, wtext, strlen((char*)wtext), (void *)&byteswritten);

	        if((byteswritten == 0) || (res != FR_OK))
	        {
	          /* wtext file Write or EOF Error */
	          Error_Handler("write error");
	        }
	        else
	        {
	          /* Close the open text file */
	          f_close(&MyFile);

	          /* Open the text file object with read access */
	          if(f_open(&MyFile, path, FA_READ) != FR_OK)
	          {
	            /* 'data.txt' file Open for read Error */
	            Error_Handler("read open error");
	          }
	          else
	          {
	            /* Read data from the text file */
	            res = f_read(&MyFile, rtext, sizeof(rtext), (void *)&bytesread);

	            if((bytesread == 0) || (res != FR_OK))
	            {
	              /* 'data.txt' file Read or EOF Error */
	              Error_Handler("final read error");
	            }
	            else
	            {
	              /* Close the open text file */
	              f_close(&MyFile);

	              /* Compare read data with the expected data */
//	              if((bytesread != byteswritten))
//	              {
//	                /* Read data is different from the expected data */
//	                //Error_Handler("compare read error");
//	              }
//	              else
	              {
	                /* Success of the demo: no error occurrence */
	                USBH_UsrLog ("Success data writing");
	                USBH_UsrLog ("\nflag: %d",txflag);
	              }
	            }
	          }
	        }
	      }
	    }


  /* Unlink the USB disk I/O driver */
  FATFS_UnLinkDriver(USBDISKPath);

  USBH_UsrLog ("fat driver disconnesso");
}

/**
  * @brief  User Process
  * @param  phost: Host handle
  * @param  id: Host Library user message ID
  * @retval None
  */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{
  switch(id)
  {
  case HOST_USER_SELECT_CONFIGURATION:
    break;

  case HOST_USER_DISCONNECTION:
    Appli_state = APPLICATION_IDLE;
    f_mount(NULL, (TCHAR const*)"", 0);
    FATFS_UnLinkDriver(USBDISKPath);
    break;

  case HOST_USER_CLASS_ACTIVE:
    Appli_state = APPLICATION_START;
    FATFS_LinkDriver(&USBH_Driver, USBDISKPath);
    f_mount(&USBH_fatfs, "", 0);

    break;

  default:
    break;
  }
}

void initRxBuffer() {
    rxBuffer = (uint8_t*)malloc(buf_size * sizeof(uint8_t));
    memset(rxBuffer, 0, buf_size);
    if (rxBuffer == NULL) {
        // Gestione dell'errore di allocazione della memoria
        // Potresti voler stampare un messaggio di errore o terminare il programma
    	USBH_UsrLog("buffer error");
    }
}

void deinitRxBuffer() {
    free(rxBuffer);
    rxBuffer = NULL;
    buf_index = 0;
    buf_size = RX_BUFFER_SIZE;
}

void processReceivedData(uint8_t sdata) {

	// Controlla e ridimensiona il buffer se necessario
	    if (buf_index >= buf_size - 1) { // Lascia spazio per '\0'
	        size_t new_size = buf_size + RX_BUFFER_SIZE;
	        uint8_t *newBuffer = (uint8_t *)realloc(rxBuffer, new_size);
	        if (newBuffer == NULL) {
	            // Gestione dell'errore di reallocazione della memoria
	        	free(rxBuffer);
	            rxBuffer = NULL;
	        	//deinitRxBuffer();
	            buf_size=0;
	            buf_index=0;
	            USBH_UsrLog("buffer null");
	            //initRxBuffer(); // Re-inizializza il buffer dopo l'errore
	            return; // Potresti voler gestire questo errore in modo diverso
	        }

	        rxBuffer = newBuffer;
	        buf_size = new_size;

	        USBH_UsrLog("buffer problem");
	    }

	    // Aggiungi il carattere ricevuto al buffer
	    rxBuffer[buf_index++] = sdata;
	    rxBuffer[buf_index] = '\0';
	    //HAL_UART_Transmit(&UartHandle, rxBuffer, buf_index, 0xFFFF);
	    USBH_UsrLog("%s\n",rxBuffer);

	    // Verifica le condizioni specificate
	        if (strstr(rxBuffer, "\r.\r") != NULL) {
	            USBH_UsrLog("Sequence '\\r.\\r' found: %s\n", rxBuffer);
	            memset(rxBuffer, 0, buf_size);  // Reset del buffer dopo l'elaborazione
	            buf_index = 0;
	        } else if ((strstr(rxBuffer, "=CAL") != NULL) && (rxBuffer[buf_index-1] == '\r')) {
	        	USBH_UsrLog("String contains '=CAL' and ends with '\\r': %s\n", rxBuffer);
	            memset(rxBuffer, 0, buf_size);  // Reset del buffer dopo l'elaborazione
	            buf_index = 0;
	        }

    USBH_UsrLog ("end processing");
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 1
  *            PLL_N                          = 20
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Configure LSE Drive Capability */
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /* Initialize the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE
                                    |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler("rcc error");
  }

  /* Initialize the CPU, AHB and APB busses clocks  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                               |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler("clock error");
  }

  /* Initialize the USB clock source */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_MSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler("periph error");
  }

  /* Enable MSI Auto calibration */
  HAL_RCCEx_EnableMSIPLLMode();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	// if (huart->Instance == USART1) {USBH_UsrLog ("one char on handle");}

	// HAL_UART_Receive_IT(&UartHandle,rxBuffer,1);

}

static void MX_RTC_Init(void){

	 RTC_TimeTypeDef sTime = {0};
	 RTC_DateTypeDef sDate = {0};

	 /** Attiva l'orologio LSE */
	    __HAL_RCC_LSE_CONFIG(RCC_LSE_ON);
	    while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
	    {
	    }

	    hrtc.Instance = RTC;
	       hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	       hrtc.Init.AsynchPrediv = 127;
	       hrtc.Init.SynchPrediv = 255;
	       hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	       hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	       hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	       hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

	      /*if (HAL_RTC_Init(&hrtc) != HAL_OK)
	          {
	              Error_Handler("RTC_INIT error");
	          }*/

	       /** Inizializzazione data */
	           sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	           sDate.Month = RTC_MONTH_JANUARY;
	           sDate.Date = 1;
	           sDate.Year = 0;

	          /* if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
	              {
	                  Error_Handler();
	              }*/

	              /** Inizializzazione ora */
	              sTime.Hours = 0;
	              sTime.Minutes = 0;
	              sTime.Seconds = 0;
	              sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	              sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	           /*  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	              {
	                  Error_Handler("set time error");
	              }*/

	          //    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, 0x32F2); // Valore di backup arbitrario

}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(const char *errorMessage)
{

	USBH_UsrLog("Errore: %s", errorMessage);
  //while(1){}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

