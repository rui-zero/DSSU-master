/******************** Med-X Institute ********************
* File Name          : System.h
* Author             : Lishen Yin
* Date First Issued  : 4/20/2012
********************************************************************************/



#ifndef __system_h
#define __system_h

#define _USART1
#define _USART2
#define _USART3

#ifdef _USART1
  #define USART1              ((USART_TypeDef *) USART1_BASE)
#endif /*_USART1 */

#ifdef _USART2
  #define USART2              ((USART_TypeDef *) USART2_BASE)
#endif /*_USART2 */

#ifdef _USART3
  #define USART3              ((USART_TypeDef *) USART3_BASE)
#endif /*_USART3 */
/*****************private functions*******************************************************/



void System_initialization(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void SPI_Configuration(void);
void Can_Configuration(void);
void Can_send(vu8 type, vu8 Idnumber, vu8 status);
void TIM_Configuration(vu32 StimPeriod);
void SysTick_Config(void);
void Delay(u32 nCount);
void Decrement_TimingDelay(void);
void CAN_start (void );
void CAN_setup (void);
void USART_Configuration(void);
void USART1_Putc(u16 c);
u16  USART1_ReceiveC(void);
void USART2_Putc(u16 c);
u16  USART2_ReceiveC(void);
void USART3_Putc(u16 c);
u16  USART3_ReceiveC(void);

/*************************************************************************/



#endif /* __system.h */
