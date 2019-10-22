/******************** Med-X Institute ********************
* File Name          : ReadDATA.c
* Author             : Lishen Yin
* Date First Issued  : 04/13/2012
* Description        : STIMULATION program
********************************************************************************
*Function includes:
* StimIniPram_TypeDef  ReadData (Data_TypeDef *Data)

********************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "spi_flash.h"
#include <stdio.h>
#include "stm32f10x_lib.h" 
#include "readdata.h"
#include "stimulation.h"











/*******************************************************************************
* Function Name  : ReadData
* Description    : Read the Stimulation Data from storage
* Input          : Data
* Output         : Stimulate Parameter
* Return         : Stimulate Parameter
*******************************************************************************/
StimIniPram_TypeDef  ReadData (Data_TypeDef *Data)		//解读数据函数
{
  StimIniPram_TypeDef StimIniPram;				 //定义刺激参数结构体的形参 

 /**************************数据赋值，测试用*******************************************************************/
  Data->Storage[0] = 1;
  Data->Storage[1] = 0;
  Data->Storage[2] = 17;
  Data->Storage[3] = 1;
  Data->Storage[4] = 144;
  Data->Storage[5] = 0;
  Data->Storage[6] = 50;
  Data->Storage[7] = 0;
  Data->Storage[8] = 0;
  Data->Storage[9] = 0;
  Data->Storage[10] = 0;
  Data->Storage[11] = 2;
  Data->Storage[12] = 5;
  Data->Storage[13] = 0x00;
  Data->Storage[14] = 0xFF;
  Data->Storage[15] = 0xFF;
  Data->Storage[16] = 0xFF;

 /**********************************************************************************************************************/ 

  Data->end =&Data->Storage[16];				 //测试用，尾指针 ，指向存储空间末尾
  
  
  Data->now = &Data->Storage[0];				 //now指针指向存储空间首位

  Data->now++; // 跳过channel号，指向数据长度

  StimIniPram.DataLength   = ( vu16 )*Data->now;		   //接收的数据长度
  StimIniPram.DataLength = StimIniPram.DataLength << 8;
  Data->now++;
  StimIniPram.DataLength 	= StimIniPram.DataLength  +  ( vu16 )*Data->now;
  Data->now++;

  StimIniPram.StimPosTime   = ( vu16 )*Data->now;		   //接收刺激时长
  StimIniPram.StimPosTime = StimIniPram.StimPosTime << 8;
  Data->now++;
  StimIniPram.StimPosTime	= StimIniPram.StimPosTime +  ( vu16 )*Data->now;
  StimIniPram.StimNegTime = StimIniPram.StimPosTime;  //正负向刺激时间一致
  Data->now++;
  

  StimIniPram.StimFreq   = ( vu16 )*Data->now;				   //接收刺激频率
  StimIniPram.StimFreq = StimIniPram.StimFreq << 8;
  Data->now++;
  StimIniPram.StimFreq	= StimIniPram.StimFreq +  ( vu16 )*Data->now;
  
  Data->now =Data->now + 3;		 //跳过delay, circulate time
  

  return   StimIniPram;			  // 返回刺激参数




}









