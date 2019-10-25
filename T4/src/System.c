/******************** Med-X Institute ********************
* File Name          : system.c
* Author             : Lishen Yin
* Date First Issued  : 4/20/2012
* Description        : Main program body
********************************************************************************
* History:
* 10/21/2011: V0.1
* 10/31/2011: V0.2
* 11/07/2011: v0.3
* 11/21/2011: v0.4
********************************************************************************
 Fuction Including: 
	void System_initialization(void)
	void RCC_Configuration(void)
	void GPIO_Configuration(void)
	void SPI_Configuration(void)
	void NVIC_Configuration(void)
	void TIM_Configuration(vu32 StimPeriod)
	void SysTick_Config(void)
	void Delay(u32 nCount)
	void Decrement_TimingDelay(void)
	void Can_Configuration(void)

***********************************************************************************/
#include "spi_flash.h"
#include <stdio.h>
#include "stm32f10x_lib.h" 
#include "system.h"
#include "STM32_Reg.h" 
#include "STM32_Init.h"     



/**************************系统初始化所需变量******************/
int TimingDelay = 0; 

extern void usart1(void);


ErrorStatus HSEStartUpStatus;
TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
/*******************************************************************************/


/*************************
* Function Name  : System_initialization
* Description    : System_initialization
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void System_initialization(void)				 //系统初始化流程
{ USART_DeInit(USART2);
/* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();
  
  /* NVIC configuration ------------------------------------------------------*/
  NVIC_Configuration();
  
  /* Configure the systick */    
  SysTick_Config();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();

  /*SPI configuration ----------------------------------------------------------*/
  SPI_Configuration();

  /*CAN configuration ----------------------------------------------------------*/
  Can_Configuration();

  USART_Configuration();

  //USART2_Putc(u16 c);

  //USART2_ReceiveC(void);
  }

void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;
  //u16 USART_IT

/* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
        - USART Clock disabled
        - USART CPOL: Clock is active low
        - USART CPHA: Data is captured on the middle 
        - USART LastBit: The clock pulse of the last data bit is not output to 
                         the SCLK pin
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_Clock = USART_Clock_Disable;
  USART_InitStructure.USART_CPOL = USART_CPOL_Low;
  USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_InitStructure.USART_LastBit = USART_LastBit_Disable;

  
  USART_Init(USART2, &USART_InitStructure);
  USART_ITConfig(USART2, USART_IT_PE, ENABLE); 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
  USART_Cmd(USART2, ENABLE);/* Enable USART2 */
  

}
/*******************************************************************************/


void USART2_Putc(u16 c)  
{  
    USART_SendData(USART2, c);  
   
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET ); 
}  

u16 USART2_ReceiveC(void)
{
	 u16 i = 0;
	 i = USART_ReceiveData(USART2);
	 while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	 return i;
}


/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
 
    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }



  }

/* Enable peripheral clocks --------------------------------------------------*/
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  /* CAN Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);

}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_PinRemapConfig(GPIO_Remap1_CAN, ENABLE);// remap
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Configure PC.5 and PC7 as Output push-pull----s1-------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /* Configure PB.0 as Output push-pull----s2-------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*Configure PC.4 as Output push-pull----DAC CS -----------------------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /*SPI1 PA.4=>NSS | PA.5=>SCK |PA.6=>MIS0|PA.7=MOSI-------------------------------------------*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

 
  
  
  


  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
/////////////////////////////////////////////////////////////////////////////////////////////
 /* Configure USART2 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* Configure USART2 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //////////////////////////////////////////////////////////////////////////////////////
}	

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* Enable the TIM2 gloabal Interrupt 	*/
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 



   /* Enable CAN RX0 interrupt IRQ channel */
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	/*USART2    */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/*EXTI
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);*/
	
	NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick,!0,0);
}

/*******************************************************************************
* Function Name  : SPI_Configuration
* Description    : Configures SPI.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Configuration(void)
{
  SPI_InitTypeDef SPI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//两线全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//主
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;//16位
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //CPOL=1时钟悬空高;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //CPHA=1 数据捕获第2个
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//软件NSS
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//4分频
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位在前
  SPI_InitStructure.SPI_CRCPolynomial = 7;//CRC7
  SPI_Init(SPI1, &SPI_InitStructure);
  
  /* Enable SPI1  */
  SPI_Cmd(SPI1, ENABLE);
}



/*******************************************************************************
* Function Name  : CAN_Configuration
* Description    : Configures CAN
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Can_Configuration(void)
{
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  
  CAN_setup();
  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber=1;
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
	
  CAN_start();
}


/*******************************************************************************
* Function Name  : Can_send
* Description    : send messages to MU
* Input          : type, Idnumber, status
* Output         : None
* Return         : None
*******************************************************************************/
void Can_send(vu8 type, vu8 Idnumber, vu8 status)	
{

  CanTxMsg TxMessage;
  u32 i = 0;
  u8 TransmitMailbox;

  TxMessage.StdId=0x00;
  TxMessage.ExtId=0x1234;
  TxMessage.IDE=CAN_ID_EXT;
  TxMessage.RTR=CAN_RTR_DATA;
  TxMessage.DLC=3;
  TxMessage.Data[0]= type;
  TxMessage.Data[1]= Idnumber;
  TxMessage.Data[2]= status;

  TransmitMailbox=CAN_Transmit(&TxMessage);
  i = 0;
  while((CAN_TransmitStatus(TransmitMailbox) != CANTXOK) && (i != 0xFF))
  {
    i++;
  }

  i = 0;
  while((CAN_MessagePending(CAN_FIFO0) < 1) && (i != 0xFE))
  {
    i++;
  }
}
/*******************************************************************************
* Function Name  : TIM_Configuration
* Description    : Configures TIMer
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_Configuration(vu32 StimPeriod)
{  
  /* ---------------------------------------------------------------
    TIM2 Configuration: Output Compare Timing Mode:
    TIM2CLK = 72 MHz, Prescaler = 360, TIM2 counter clock = 0.2 MHz
  --------------------------------------------------------------- */
  

  TIM_TimeBaseStructure.TIM_Period = 200000/StimPeriod - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = 360;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_DeInit(TIM2);
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 

  										  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 
  
}

/*******************************************************************************
* Function Name  : SysTick_Config
* Description    : Configure a SysTick Base time to 10 ms.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
 void SysTick_Config(void)
{
  /* Configure HCLK clock as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
 
  /* SysTick interrupt each 1 MHz with HCLK equal to 72MHz */
  SysTick_SetReload(72);

  /* Enable the SysTick Interrupt */
  SysTick_ITConfig(ENABLE);
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length (time base 10 us).
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(u32 nCount)
{
  TimingDelay = nCount;

  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
  
  while(TimingDelay >0)
  {
		
  }
  /* Disable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Disable);

  /* Clear the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Clear);
}

/*******************************************************************************
* Function Name  : Decrement_TimingDelay
* Description    : Decrements the TimingDelay variable.
* Input          : None
* Output         : TimingDelay
* Return         : None
*******************************************************************************/
void Decrement_TimingDelay(void)
{
  {
    TimingDelay--;
  }
}
void CAN_start (void)  {

  CAN->MCR &= ~CAN_MCR_INRQ;                      // normal operating mode, reset INRQ
  while (CAN->MSR & CAN_MCR_INRQ);

}


void CAN_setup (void)  {
  unsigned int brp = stm32_GetPCLK1();

  RCC->APB1ENR |= RCC_APB1ENR_CANEN;              // enable clock for CAN

                                                  // Note: MCBSTM32 uses PB8 and PB9 for CAN
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;             // enable clock for Alternate Function
  AFIO->MAPR   &= 0xFFFF9FFF;                     // reset CAN remap
  AFIO->MAPR   |= 0x00004000;                     //   set CAN remap, use PB8, PB9
												  
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;             // enable clock for GPIO B
  GPIOB->CRH &= ~(0x0F<<0);
  GPIOB->CRH |=  (0x08<<0);                       // CAN RX pin PB.8 input push pull 
  
  GPIOB->CRH &= ~(0x0F<<4);
  GPIOB->CRH |=  (0x0B<<4);                       // CAN TX pin PB.9 alternate output push pull 

  //NVIC->ISER[0] |= (1 << (USB_HP_CAN_TX_IRQChannel  & 0x1F));// enable interrupt
  NVIC->ISER[0] |= (1 << (USB_LP_CAN_RX0_IRQChannel & 0x1F));// enable interrupt

  CAN->MCR = (CAN_MCR_NART | CAN_MCR_INRQ);       // init mode, disable auto. retransmission
                                                  // Note: only FIFO 0, transmit mailbox 0 used
  CAN->IER = (CAN_IER_FMPIE0 | CAN_IER_TMEIE);    // FIFO 0 msg pending, Transmit mbx empty

  /* Note: this calculations fit for PCLK1 = 36MHz */
  brp  = (brp / 18) / 500000;                     // baudrate is set to 500k bit/s
                                                                          
  /* set BTR register so that sample point is at about 72% bit time from bit start */
  /* TSEG1 = 12, TSEG2 = 5, SJW = 4 => 1 CAN bit = 18 TQ, sample at 72%    */
  CAN->BTR &= ~(((        0x03) << 24) | ((        0x07) << 20) | ((         0x0F) << 16) | (          0x1FF)); 
  CAN->BTR |=  ((((4-1) & 0x03) << 24) | (((5-1) & 0x07) << 20) | (((12-1) & 0x0F) << 16) | ((brp-1) & 0x1FF));
}
