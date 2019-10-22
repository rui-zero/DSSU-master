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
StimIniPram_TypeDef  ReadData (Data_TypeDef *Data)		//������ݺ���
{
  StimIniPram_TypeDef StimIniPram;				 //����̼������ṹ����β� 

 /**************************���ݸ�ֵ��������*******************************************************************/
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

  Data->end =&Data->Storage[16];				 //�����ã�βָ�� ��ָ��洢�ռ�ĩβ
  
  
  Data->now = &Data->Storage[0];				 //nowָ��ָ��洢�ռ���λ

  Data->now++; // ����channel�ţ�ָ�����ݳ���

  StimIniPram.DataLength   = ( vu16 )*Data->now;		   //���յ����ݳ���
  StimIniPram.DataLength = StimIniPram.DataLength << 8;
  Data->now++;
  StimIniPram.DataLength 	= StimIniPram.DataLength  +  ( vu16 )*Data->now;
  Data->now++;

  StimIniPram.StimPosTime   = ( vu16 )*Data->now;		   //���մ̼�ʱ��
  StimIniPram.StimPosTime = StimIniPram.StimPosTime << 8;
  Data->now++;
  StimIniPram.StimPosTime	= StimIniPram.StimPosTime +  ( vu16 )*Data->now;
  StimIniPram.StimNegTime = StimIniPram.StimPosTime;  //������̼�ʱ��һ��
  Data->now++;
  

  StimIniPram.StimFreq   = ( vu16 )*Data->now;				   //���մ̼�Ƶ��
  StimIniPram.StimFreq = StimIniPram.StimFreq << 8;
  Data->now++;
  StimIniPram.StimFreq	= StimIniPram.StimFreq +  ( vu16 )*Data->now;
  
  Data->now =Data->now + 3;		 //����delay, circulate time
  

  return   StimIniPram;			  // ���ش̼�����




}








