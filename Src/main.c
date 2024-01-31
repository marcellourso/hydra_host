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



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
FIL MyFile;                   /* File object */
char USBDISKPath[4];          /* USB Host logical drive path */
USBH_HandleTypeDef hUSBHost; /* USB Host handle */

typedef enum {
  APPLICATION_IDLE = 0,
  APPLICATION_START,
  APPLICATION_RUNNING,
}MSC_ApplicationTypeDef;

MSC_ApplicationTypeDef Appli_state = APPLICATION_IDLE;
UART_HandleTypeDef UartHandle;



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
const char* header = "Rec,DInizio,HInizio,DEND,hEND,Ciclo,NFiltro,Linea,DPwrDown,LeakTest,SpanTest,VolIngr,VolStd,PercTEff,TExtMin,TExtMed,TExtMax,TFiltMin,TFiltMed,TFiltMax,PAtmMin,PAtmMed,PAtmMax,CoeffVPort,CadPIniz,CadPMed,CadPMax,ValDTMax,DataDTMax,OraDTMax,TSSDTMax,ValDTMed,BitAtten\r";

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


    tx_buff[0] = 0x34;
    tx_buff[1] = 0x34;
    tx_buff[2] = 0x0D;
    buf_index = 0;
    buf_size = RX_BUFFER_SIZE;

    SN[0] = '\0';
    data = NULL;

  /* Configure the system clock to 80 MHz */
  SystemClock_Config();

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



  if (HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler("uart init error");
  }

  // HAL_UART_Receive_IT(&UartHandle, rxBuffer, 1); //interrupt serial

  initRxBuffer();

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
    	tx_buff[0] = 0x34;
    	tx_buff[1] = 0x34;
    	tx_buff[3] = 0x0D;
    	//HAL_UART_Transmit(&UartHandle, tx_buff, 3, 0xFFFF);
       Appli_state = APPLICATION_IDLE;
       break;
      case APPLICATION_IDLE:
    	  break;

     default:

    	 break;
      }

     //Simula la ricezione dei dati
//         const char *testDataSN = "=CAL,123,456,789\rAnotherMessage\r.\r=CAL,987\r";
//         const char *testDataST = "0003,20/05/04,19:00,21/05/04,19:00,0004,0004,A,00:00,20.05,+00.4,013.711,012.568,100.0,296.7,297.6,298.1,298.6,299.2,299.3,101.1,101.1,101.3,00.6,08.0,08.3,50.2,+02.0,20/05/04,20:00,000:00,+04.5,000000000\n\r0003,20/05/04,19:00,21/05/04,19:00,0004,0004,A,00:00,20.05,+00.4,013.711,012.568,100.0,296.7,297.6,298.1,298.6,299.2,299.3,101.1,101.1,101.3,00.6,08.0,08.3,50.2,+02.0,20/05/04,20:00,000:00,+04.5,000000000\r.\r";
           //const char *testDataSC = "=SN0000\r0000,01/01/** 18:25,01/01/** 18:35,0001,0001,A,00:00,00.00,+00.0,000.000,000.000,093.7,293.0,293.9,294.9,295.0,296.0,296.9,101.0,101.2,101.5,23.2,00.0,05.1,08.3,003.7,01/01/** 18:33,000:00,+02.0,055.0,0000C004\r0001,01/01/** 18:25,01/01/** 18:35,0001,0001,B,00:00,00.00,+00.0,000.000,000.000,094.0,293.0,293.9,294.9,295.0,296.0,296.9,101.0,101.2,101.5,23.2,00.0,00.6,08.3,003.9,01/01/** 18:34,000:00,+02.0,055.0,0000C004\r0002,01/01/** 18:35,01/01/** 18:45,0002,0002,A,00:00,00.00,+00.0,000.000,000.000,089.5,293.0,293.9,294.9,295.0,296.0,296.9,101.0,101.2,101.5,23.2,00.0,01.6,08.4,003.7,01/01/** 18:41,000:00,+02.0,055.1,0000C004\r0003,01/01/** 18:35,01/01/** 18:45,0002,0002,B,00:00,00.00,+00.0,000.000,000.000,090.5,293.0,293.9,294.9,295.0,296.0,296.9,101.0,101.2,101.5,23.2,00.0,06.4,08.4,003.8,01/01/** 18:40,000:00,+02.0,055.1,0000C004\r0004,01/01/** 18:45,01/01/** 18:55,0003,0003,A,00:00,00.00,+00.0,000.000,000.000,088.7,293.0,294.0,294.9,295.0,295.9,296.9,101.0,101.3,101.5,23.2,00.0,01.8,08.5,003.7,01/01/** 18:49,000:00,+01.9,055.0,0000C004\r0005,01/01/** 18:45,01/01/** 18:55,0003,0003,B,00:00,00.00,+00.0,000.000,000.000,089.3,293.0,294.0,294.9,295.0,296.0,296.9,101.0,101.3,101.5,23.2,00.0,01.7,08.4,003.7,01/01/** 18:49,000:00,+01.9,055.0,0000C004\r0006,01/01/** 18:55,01/01/** 19:05,0004,0004,A,00:00,00.00,+00.0,000.000,000.000,079.3,293.0,293.9,294.9,295.0,295.9,296.9,101.0,101.3,101.5,23.1,00.0,05.0,08.3,003.7,01/01/** 18:59,000:00,+01.9,054.8,0000C004\r0007,01/01/** 18:55,01/01/** 19:05,0004,0004,B,00:00,00.00,+00.0,000.000,000.000,079.7,293.0,293.9,294.9,295.0,295.9,296.9,101.0,101.3,101.5,23.1,00.0,00.6,08.5,003.8,01/01/** 19:02,000:00,+01.9,054.8,0000C004\r\r\r\r\r";
//         //	 const char *ptr = strstr(testDataST, "\r.\r");

//       for (size_t i = 0; i < strlen(testDataSC); ++i) {
//
//        	 rxBuffer[buf_index++] = testDataSC[i];
//            rxBuffer[buf_index] = '\0';
//
//
//           if (strstr(rxBuffer, "\r\r\r\r\r")) {
//
//      		// USBH_UsrLog("Sequenza '\r\r\r\r\r' trovata fino alla posizione %d",i);
//
//
//              //USBH_UsrLog("buffer completo: %s",testDataSC);
//
//              	  	  // Estrai SN
//            	       char *startSN = strchr(rxBuffer, '=') + 1;
//            	       if (startSN != NULL) {
//            	           char *endSN = strchr(startSN, '\r');
//            	           if (endSN != NULL && (endSN - startSN < sizeof(SN))) {
//            	               strncpy(SN, startSN, endSN - startSN);
//            	               SN[endSN - startSN] = '\0';  // Termina correttamente la stringa SN
//            	           }
//            	       }
//
//            	       // Estrai data
//            	       char *startData = strchr(rxBuffer, '\r') + 1;  // Inizio dei dati dopo il primo '\r'
//            	       if (startData != NULL) {
//            	           char *endData = strstr(startData, "\r\r\r\r\r");  // Fine dei dati prima dei cinque '\r'
//            	           if (endData != NULL) {
//            	               size_t dataSize = endData - startData;
//            	               data = (char *)malloc(dataSize + 1);  // Alloca memoria per i dati
//            	               if (data != NULL) {
//            	                   strncpy(data, startData, dataSize);
//            	                   data[dataSize] = '\0';  // Termina correttamente la stringa data
//            	               }
//            	           }
//            	       }
//
//
//            	       // Reset del buffer dopo l'elaborazione
//            	       memset(rxBuffer, 0, RX_BUFFER_SIZE);
//            	       buf_index = 0;
//
//            	       USBH_UsrLog("serial: %s\nDATA:%s",SN,data);
//
//            	       // Ora puoi utilizzare SN e data come necessario
//            	       // Ricorda di liberare la memoria allocata per data qui
//
//
//      	         	            	    return 0;
//
//       	         	                            }
//
//        }




     if (USARTx->ISR & USART_ISR_RXNE) {

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


         sdata = (uint8_t)(USARTx->RDR); // Leggi un byte dal buffer di ricezione di USARTx
         rxBuffer[buf_index++] = sdata;
         rxBuffer[buf_index] = '\0';



         //HAL_UART_Transmit(&UartHandle, &sdata, 1, 0xFFFF);
         //HAL_UART_Transmit(&UartHandle, &lf, 1, 0xFFFF);
         //HAL_UART_Transmit(&UartHandle, rxBuffer,buf_index, 0xFFFF);
//       if ((strstr(rxBuffer, "=CAL") != NULL) && (rxBuffer[buf_index-1] == '\r')) {
//
//        	         char* token = strtok((char *)rxBuffer, ",");
//        	         int field_count = 0;
//        	         while (token != NULL) {
//        	             field_count++;
//        	             if (field_count == 4) {
//        	                 // Assumi che SN sia definita e abbastanza grande da contenere il token
//        	                 sprintf(SN, "H%s", token);
//        	                 USBH_UsrLog(SN); // Modificato per loggare direttamente il token
//        	                 memset(rxBuffer, 0, buf_size);  // Reset del buffer dopo l'elaborazione
//        	                 buf_index = 0;
//        	                 break;
//        	             }
//        	             token = strtok(NULL, ",");
//        	          }
//
//        	        }
//
//         // Controlla se la stringa finisce per "\r.\r"
//           else if (strstr(rxBuffer, "\r.\r") && (rxBuffer[buf_index-1] == '\r') ) {
//
//        	   //USBH_UsrLog("buffer: %s",rxBuffer);
//
//
//        		 // Calcola la dimensione del buffer finale
//        	            	     int bufferSize = sizeof(header) + sizeof(rxBuffer);
//
//        	            	     // Alloca il buffer per la stringa finale
//        	            	     char *finalString = (char *)malloc(bufferSize);
//        	            	     if (finalString == NULL) {
//        	            	         // Gestione dell'errore di allocazione della memoria
//        	            	    	 USBH_UsrLog("null final");
//        	            	         return;
//        	            	     }
//
//        	            	     // Inizializza il buffer con la stringa dell'header
//        	            	     strcpy(finalString, header);
//
//        	            	     // Aggiungi la stringa di dati esistenti
//        	            	     strcat(finalString, rxBuffer);
//        	            	     USBH_UsrLog(finalString);
//
//        	            	     // Libera la memoria allocata per finalString una volta che non è più necessaria
//        	            	     free(finalString);
//
//        	            	     // Reset del buffer e dell'indice dopo l'elaborazione
//        	            	     memset(rxBuffer, 0, RX_BUFFER_SIZE);
//        	            	     buf_index = 0;
//
//        	                            }

           if ((strstr(rxBuffer, "\r\r\r") != NULL)) {

        	  // USBH_UsrLog("terminatore trovato, stringa: %s",rxBuffer);
        	   //return;


        	   // Estrai SN
        	       char *startSN = strchr(rxBuffer, '=') + 1;
        	       if (startSN != NULL) {
        	           char *endSN = strchr(startSN, '\r');
        	           if (endSN != NULL && (endSN - startSN < sizeof(SN))) {
        	               strncpy(SN, startSN, endSN - startSN);
        	               SN[endSN - startSN] = '\0';  // Termina correttamente la stringa SN
        	               //char SN_with_extension[64]; // Assicurati che sia abbastanza grande per contenere SN + ".csv" + carattere nullo
        	               //sprintf(SN_with_extension, "%s.csv", SN); // Concatena ".csv" a SN e memorizza il risultato in SN_with_extension
        	           }
        	       }



        	       // Estrai data
        	       char *startData = strchr(rxBuffer, '\r') + 1;  // Inizio dei dati dopo il primo '\r'
        	       if (startData != NULL) {
        	           char *endData = strstr(startData, "\r\r\r");  // Fine dei dati prima dei cinque '\r'
        	           if (endData != NULL) {
        	               size_t dataSize = endData - startData;
        	               data = (char *)malloc(dataSize + 1);  // Alloca memoria per i dati
        	               if (data != NULL) {
        	                   strncpy(data, startData, dataSize);
        	                   data[dataSize] = '\0';  // Termina correttamente la stringa data
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
        	             //USBH_UsrLog(finalString);


        	       // Reset del buffer dopo l'elaborazione
        	       memset(rxBuffer, 0, RX_BUFFER_SIZE);
        	       buf_index = 0;

        	       strcat(SN,".csv");
        	       USBH_UsrLog("serial:%s\nDATA:%s\nFinal:%s",SN,data,finalString);
        	       MSC_Application(finalString,SN);

        	       free(finalString); // libera la memoria allocata
   	               free(data);  // libera la memoria allocata



        	       //return;

        	       // Ora puoi utilizzare SN e data come necessario
        	       // Ricorda di liberare la memoria allocata per data qui


        	   } // end data end reached

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
	              if((bytesread != byteswritten))
	              {
	                /* Read data is different from the expected data */
	                Error_Handler("compare read error");
	              }
	              else
	              {
	                /* Success of the demo: no error occurrence */
	                USBH_UsrLog ("Success data writing");
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

	if (huart->Instance == USART1) {USBH_UsrLog ("one char on handle");}

	HAL_UART_Receive_IT(&UartHandle,rxBuffer,1);

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

