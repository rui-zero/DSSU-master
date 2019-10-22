/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : main.h
* Author             : MCD Application Team
* Version            : V1.0
* Date               : 10/08/2007
* Description        : Header for main.c module
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "spi_flash.h"
typedef struct
{
	vu8 databuf[1024];
	vu16 queueStart;
	vu16 queueEnd;
}queueBufferType;

typedef struct receiveData
{
	vu8 startFlag;                   //communication start flag
	vu8 dataType;                    //make sure the data that will be recevied is a codedata or parameter data: code:1 ; data:2
	vu8 dataTypeFlag;                //if we have received the datatype
	vu8 dataStartFlag;               //whether the data is receiving
	vu8* dataBuf;                     //derect to the databuf adress
	vu16 temp;
	vu8 codeStartFlag;
    vu8 dataEnd;
	vu8 dataEndFlag;                 //
	vu8 stimulationChannelFlag;
	vu8 stimulationChannel;
}ReceiveDataType;




/* Private Define ------------------------------------------------------------------*/
#define Type     ((vu8)0x00)
#define DSSU_ID  ((vu8)0x01)





#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
