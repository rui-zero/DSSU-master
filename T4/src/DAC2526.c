#include  "stm32f10x_lib.h"
#include "DAC2526.h"


void initDAC2526()
{
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
  SPI_I2S_SendData(SPI1,0xf000);//DAC Power down	
	/*SPI¿ØÖÆÐÅºÅ·¢ËÍ------------------------------------------------------------------------------*/
  GPIO_SetBits(GPIOC, GPIO_Pin_4);
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
  GPIO_ResetBits(GPIOC, GPIO_Pin_4);
  SPI_I2S_SendData(SPI1,0x9000); 
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET);
  GPIO_SetBits(GPIOC, GPIO_Pin_4); //CS
}
	
void writeToDAC2526(u16 StimAmp)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	SPI_I2S_SendData(SPI1,(0x4000 | StimAmp));
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET);
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
}

void writeDACAandB(u16 StimAmpA,u16 StimAmpB)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	SPI_I2S_SendData(SPI1,(0x4000 | StimAmpB));
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET);
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	SPI_I2S_SendData(SPI1,(0xC000 | StimAmpA));
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET);
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
}

void writeDACAandBtoZero(void)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	SPI_I2S_SendData(SPI1,0x4000 );
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET);
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	SPI_I2S_SendData(SPI1,0xC000 );
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET);
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
}

