/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_it.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"
#include "System.h"
#include "readdata.h"
#include "Stimulation.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//#define DSSU_ID  ((vu8)0x03)
u16 capture = 0;
vu8 i=0;                            //传数据时用于计数
vu8 datadata[20];                   //中间过渡
extern vu8 reFlag;
extern vu16 dataLenth;
extern vu8 dataBuf[3072];
extern vu16 dataBufEnd;
extern vu8 codeBuf ;
extern vu8 codeUpdata;
extern vu8 dataReErr;
extern vu8 int_flag;
extern vu8 dataUpdata;
extern vu8 dataIsReady;
extern vu8 stimulationStart;
extern vu8 datajixu;
extern ReceiveDataType receiveDataFromCom;

extern vu8 SensoryFeedbackSystem;
extern vu8 SensoryFeedbackDataBuf[3];
extern vu8  SensoryFeedbackDataReady;
//extern queueBufferType queueBuffer[8];

/******************************************标志位********************************************/



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickHandler(void)
{
  /* Decrement the TimingDelay variable */
  Decrement_TimingDelay();
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : This function handles DMA1 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : This function handles DMA1 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : This function handles DMA1 Channel 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : This function handles DMA1 Channel 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel6_IRQHandler
* Description    : This function handles DMA1 Channel 6 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel7_IRQHandler
* Description    : This function handles DMA1 Channel 7 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
   

}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
  CanRxMsg RxMessage;

  RxMessage.StdId=0x00;
  RxMessage.ExtId=0x00;
  RxMessage.IDE=0;
  RxMessage.DLC=0;						  //为3表示搜索设备？4表示数据发完？（2.3两位表示数据长度）
  RxMessage.FMI=0;
  RxMessage.Data[0]=0x00;				  //同步头，必须为80
  RxMessage.Data[1]=0x00;				  //dssu_id  =  1 ，为FF时，若data[2]=3，刺激开始标志位=0。
  RxMessage.Data[2]=0x00;				  //赋值给codeBuf,1为发命令，2为发数据
  RxMessage.Data[3]=0x00;
  RxMessage.Data[4]=0x00;
  RxMessage.Data[5]=0x00;
  RxMessage.Data[6]=0x00;
  RxMessage.Data[7]=0x00;

  CAN_Receive(CAN_FIFO0, &RxMessage);
  
  if((RxMessage.DLC ==3) && (reFlag == 0))
  {
  	if (RxMessage.Data[0] == 0x80)
	{
		if (RxMessage.Data[1] == DSSU_ID )
		{
			codeBuf = RxMessage.Data[2];
			codeUpdata = 1;
		}
		if ( RxMessage.Data[1] == 0xFF)
		{
			if (RxMessage.Data[2] == 3)
			{
				stimulationStart = 0;
			
			}
			else
			{
				codeBuf = RxMessage.Data[2];
				codeUpdata = 1;
			}
		}

	}
	return;
  }	
  if ((RxMessage.DLC == 4) && (reFlag == 0))
  {
  	if (RxMessage.Data[0] == 0x80)
	{
		
		if (RxMessage.Data[1] == DSSU_ID )
		{
			reFlag = 1;
			dataLenth = RxMessage.Data[2];
			dataLenth <<= 8;
			dataLenth = dataLenth + RxMessage.Data[3];
			dataBufEnd = 0;
			dataIsReady = 0;
		}
	}
	return;
   }
   if(reFlag == 1)
   {
   		u8 i;
		for (i = 0;i < RxMessage.DLC; i++)
		{
			dataBuf[dataBufEnd] = RxMessage.Data[i];
			dataBufEnd++;
		}
		//dataLenth = dataLenth - RxMessage.DLC;

		if(dataLenth < dataBufEnd)
		{
			dataReErr = 1;
			reFlag = 0;
		}
		else
		{
			if (dataLenth == dataBufEnd)
				reFlag = 0;
				dataUpdata = 1;
		}
		return;
	}
	
}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET)
	{
		int_flag = 1;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
	return ;	
}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{  	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
	{	
		receiveDataFromCom.temp = USART_ReceiveData(USART1);
		if ( receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom.temp == 0x80)				        //同步头80，说明开始传输
			{
				receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataTypeFlag = 0;
				receiveDataFromCom.dataStartFlag = 0;
				receiveDataFromCom.dataEndFlag = 0;
				receiveDataFromCom.dataEnd = 0;
				receiveDataFromCom.codeStartFlag = 0;
				receiveDataFromCom.stimulationChannelFlag = 0;
			}
			
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			return;
		}

		if ( (receiveDataFromCom.dataTypeFlag == 0)&&(receiveDataFromCom.startFlag == 1))
		{
			if (receiveDataFromCom.temp == 1)								//传命令
			{
				receiveDataFromCom.codeStartFlag = 1;
				receiveDataFromCom.dataTypeFlag = 1; 
			}
			else if (receiveDataFromCom.temp == 2)							 //传数据
			{
				
				receiveDataFromCom.stimulationChannelFlag = 1;
				receiveDataFromCom.dataTypeFlag = 1;
			}
			else
			{
				receiveDataFromCom.startFlag = 0;
				receiveDataFromCom.dataTypeFlag = 0;
				
			}
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			return;
		
		}

		if ((receiveDataFromCom.codeStartFlag == 1)&&(receiveDataFromCom.startFlag == 1))            //传命令
		{
			codeBuf = receiveDataFromCom.temp;
			//MasterUnitState.codeUpdataFlag = 1;
			codeUpdata=1;
			receiveDataFromCom.startFlag = 0;
			receiveDataFromCom.dataTypeFlag = 0;
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			return;
		}

		if ((receiveDataFromCom.stimulationChannelFlag == 1)&&(receiveDataFromCom.startFlag == 1))	   //传数据
		{
			if (receiveDataFromCom.temp==1)// <= 8 && receiveDataFromCom.temp >= 1)
			{	vu8 i;
			    vu8 datadata[20];
			    reFlag=1;
				receiveDataFromCom.stimulationChannel = receiveDataFromCom.temp - 1;
				//receiveDataFromCom.stimulationChannelFlag = 0;
				//receiveDataFromCom.dataBuf = queueBuffer[receiveDataFromCom.stimulationChannel].databuf;
				//receiveDataFromCom.dataStartFlag = 1;
			    //MasterUnitState.updataChannelNumber = receiveDataFromCom.stimulationChannel;
			    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
				dataUpdata=1;
				for(i=0;i<17;i++)	           //12位+3位停止位+2位00 0C
				{
						 datadata[i]=USART_ReceiveData(USART1);
						 USART_ClearITPendingBit(USART1, USART_IT_RXNE);
				}
				if((datadata[14]==0xFF)&&(datadata[15]==0xFF)&&(datadata[16]==0xFF))    //停止位，说明数据传完
				{	for(i=0;i<12;i++)
					{dataBuf[i]=datadata[i+2];}
				     reFlag=0;}
				USART_ClearITPendingBit(USART1, USART_IT_RXNE);
				return;
			}
			else
			{
				receiveDataFromCom.startFlag = 0;
				USART_ClearITPendingBit(USART1, USART_IT_RXNE);
				return;
			}
				
		}
		}
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{	   	
	extern vu32 TimingDelay; 
	if(USART_GetFlagStatus(USART2,USART_IT_RXNE)==SET)
	{	
		receiveDataFromCom.temp = USART_ReceiveData(USART2);
		if ( receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom.temp == 0x80)				        //同步头80，说明开始传输
			{
				receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataTypeFlag = 0;
				receiveDataFromCom.dataStartFlag = 0;
				receiveDataFromCom.dataEndFlag = 0;
				receiveDataFromCom.dataEnd = 0;
				receiveDataFromCom.codeStartFlag = 0;
				receiveDataFromCom.stimulationChannelFlag = 0;
			}
			
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			return;
		}

		if ( (receiveDataFromCom.dataTypeFlag == 0)&&(receiveDataFromCom.startFlag == 1))
		{
			if (receiveDataFromCom.temp == 1)								//传命令
			{
				receiveDataFromCom.codeStartFlag = 1;
				receiveDataFromCom.dataTypeFlag = 1; 
			}
			else if (receiveDataFromCom.temp == 2)							 //传数据
			{
				
				receiveDataFromCom.stimulationChannelFlag = 1;
				receiveDataFromCom.dataTypeFlag = 1;
			}
			else if(receiveDataFromCom.temp == 4 ) // 感知反馈系统传输的数据  2019.10.18
			{
			   SensoryFeedbackSystem=1;
				 i=0;
			}	
			else 
			{
				receiveDataFromCom.startFlag = 0;
				receiveDataFromCom.dataTypeFlag = 0;
				
			}
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			return;
		
		}
		

		if((receiveDataFromCom.codeStartFlag == 1)&&(receiveDataFromCom.startFlag == 1))            //传命令
		{
			codeBuf = receiveDataFromCom.temp;
			//MasterUnitState.codeUpdataFlag = 1;
			codeUpdata=1;
			receiveDataFromCom.startFlag = 0;
			receiveDataFromCom.dataTypeFlag = 0;
			if(codeBuf==2)
			{     //codeBuf=2证明是80 01 02停止电刺激的命令
				   stimulationStart = 0;
				   TimingDelay = 1;

				   USART_SendData(USART2, 0x00BB);  
   
				  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
				  while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET ); 
			}
			else{
				USART_SendData(USART2, 0x00AA);  
   
				while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET ); 
		}
			

			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			return;
		}

		if ((receiveDataFromCom.stimulationChannelFlag == 1)&&(receiveDataFromCom.startFlag == 1))	   //传数据
		{
			if ((receiveDataFromCom.temp==1)&&(datajixu==0))// <= 8 && receiveDataFromCom.temp >= 1)
			{	
			    i=0;
			    reFlag=1;
				receiveDataFromCom.stimulationChannel = receiveDataFromCom.temp - 1;
				//receiveDataFromCom.stimulationChannelFlag = 0;
				//receiveDataFromCom.dataBuf = queueBuffer[receiveDataFromCom.stimulationChannel].databuf;
				//receiveDataFromCom.dataStartFlag = 1;
			    //MasterUnitState.updataChannelNumber = receiveDataFromCom.stimulationChannel;
			  USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				//dataUpdata=1;
			/*	for(i=0;i<17;i++)	           //12位+3位停止位+2位00 0C
				{
						 datadata[i]=USART_ReceiveData(USART2);
						 USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				}   */
				datajixu=1;}
			

				
				
			if ((receiveDataFromCom.temp!=1)&&(datajixu==0))
			{receiveDataFromCom.startFlag = 0;
				return;
			}
			if ((datajixu==1)&&(i<=17)&&(i>0))
			{datadata[i]=receiveDataFromCom.temp;}
				i=i+1;
			if ((datajixu==1)&&(i==18))
			{//if((datadata[17]==0xFF)&&(datadata[15]==0xFF)&&(datadata[16]==0xFF))    //停止位，说明数据传完
				datajixu=0;
				for(i=0;i<15;i++)
					{dataBuf[i]=datadata[i+3];}
				     reFlag=0;
					   dataUpdata=1;
					
				receiveDataFromCom.startFlag = 0;
				USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				return;}
			
		}
		
		
		
			if(SensoryFeedbackSystem==1)
			{
			  
				SensoryFeedbackDataBuf[i]= receiveDataFromCom.temp ;
      
				if(i==2)
				{
//					  dataBuf[0]=SensoryFeedbackDataBuf[0];
//					  dataBuf[1]=SensoryFeedbackDataBuf[1];
//					  dataBuf[11]=SensoryFeedbackDataBuf[2];
//				    dataUpdata=1;
//				    reFlag=1;
					  SensoryFeedbackDataReady=1;
            i=0;					
				}
				else
        {
				   i++;
				}
			
		   
				USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				return;
			}

	/*	if ((receiveDataFromCom.dataStartFlag == 1)&&(receiveDataFromCom.startFlag == 1))
		{
			if (receiveDataFromCom.temp == 0xFF)
			{
				receiveDataFromCom.dataEnd++;
			}
			else
			{
				if (receiveDataFromCom.dataEnd == 1)
				{
					*(receiveDataFromCom.dataBuf++) = 0xff;
					*(receiveDataFromCom.dataBuf++) = receiveDataFromCom.temp;
					receiveDataFromCom.dataEnd = 0;
				}
				else if	(receiveDataFromCom.dataEnd == 2)
				{
					*(receiveDataFromCom.dataBuf++) = 0xff;
					*(receiveDataFromCom.dataBuf++) = 0xff;
					*(receiveDataFromCom.dataBuf++) = receiveDataFromCom.temp;
					receiveDataFromCom.dataEnd = 0;
				}
				else
				{
					*(receiveDataFromCom.dataBuf++) = receiveDataFromCom.temp;
				}
			}
			if (receiveDataFromCom.dataEnd == 3)
			{
				receiveDataFromCom.dataEnd = 0;
				receiveDataFromCom.startFlag = 0;
				receiveDataFromCom.dataEndFlag = 1;
			//	MasterUnitState.dataUpdateFlag = 1;
			}
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			return;
		}
	}  */
}
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) == SET) //检查ORE标志
  {
      USART_ClearFlag(USART2,USART_FLAG_ORE);
      USART_ReceiveData(USART2);
  }
 }
/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{  	if(USART_GetFlagStatus(USART3,USART_IT_RXNE)==SET)
	{	
		receiveDataFromCom.temp = USART_ReceiveData(USART3);
		if ( receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom.temp == 0x80)				        //同步头80，说明开始传输
			{
				receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataTypeFlag = 0;
				receiveDataFromCom.dataStartFlag = 0;
				receiveDataFromCom.dataEndFlag = 0;
				receiveDataFromCom.dataEnd = 0;
				receiveDataFromCom.codeStartFlag = 0;
				receiveDataFromCom.stimulationChannelFlag = 0;
			}
			
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);
			return;
		}

		if ( (receiveDataFromCom.dataTypeFlag == 0)&&(receiveDataFromCom.startFlag == 1))
		{
			if (receiveDataFromCom.temp == 1)								//传命令
			{
				receiveDataFromCom.codeStartFlag = 1;
				receiveDataFromCom.dataTypeFlag = 1; 
			}
			else if (receiveDataFromCom.temp == 2)							 //传数据
			{
				
				receiveDataFromCom.stimulationChannelFlag = 1;
				receiveDataFromCom.dataTypeFlag = 1;
			}
			else
			{
				receiveDataFromCom.startFlag = 0;
				receiveDataFromCom.dataTypeFlag = 0;
				
			}
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);
			return;
		
		}

		if ((receiveDataFromCom.codeStartFlag == 1)&&(receiveDataFromCom.startFlag == 1))            //传命令
		{
			codeBuf = receiveDataFromCom.temp;
			//MasterUnitState.codeUpdataFlag = 1;
			codeUpdata=1;
			receiveDataFromCom.startFlag = 0;
			receiveDataFromCom.dataTypeFlag = 0;
			if(codeBuf==2)
			{stimulationStart = 0;}
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);
			return;
		}

		if ((receiveDataFromCom.stimulationChannelFlag == 1)&&(receiveDataFromCom.startFlag == 1))	   //传数据
		{
			if (receiveDataFromCom.temp==1)// <= 8 && receiveDataFromCom.temp >= 1)
			{	vu8 i;
			    vu8 datadata[20];
			    reFlag=1;
				receiveDataFromCom.stimulationChannel = receiveDataFromCom.temp - 1;
				//receiveDataFromCom.stimulationChannelFlag = 0;
				//receiveDataFromCom.dataBuf = queueBuffer[receiveDataFromCom.stimulationChannel].databuf;
				//receiveDataFromCom.dataStartFlag = 1;
			    //MasterUnitState.updataChannelNumber = receiveDataFromCom.stimulationChannel;
			    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
				dataUpdata=1;
				for(i=0;i<17;i++)	           //12位+3位停止位+2位00 0C
				{
						 datadata[i]=USART_ReceiveData(USART3);
						 USART_ClearITPendingBit(USART3, USART_IT_RXNE);
				}
				if((datadata[14]==0xFF)&&(datadata[15]==0xFF)&&(datadata[16]==0xFF))    //停止位，说明数据传完
				{	for(i=0;i<12;i++)
					{dataBuf[i]=datadata[i+2];}
				     reFlag=0;}
				USART_ClearITPendingBit(USART3, USART_IT_RXNE);
				return;
			}
			else
			{
				receiveDataFromCom.startFlag = 0;
				USART_ClearITPendingBit(USART3, USART_IT_RXNE);
				return;
			}
				
		}
		}
}

/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : This function handles TIM8 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : This function handles TIM8 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : This function handles TIM8 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_CC_IRQHandler
* Description    : This function handles TIM8 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : This function handles ADC3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : FSMC_IRQHandler
* Description    : This function handles FSMC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : This function handles TIM5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : This function handles SPI3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles UART4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : This function handles UART5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM6_IRQHandler
* Description    : This function handles TIM6 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : This function handles TIM7 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : This function handles DMA2 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : This function handles DMA2 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel4_5_IRQHandler
* Description    : This function handles DMA2 Channel 4 and DMA2 Channel 5
*                  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
