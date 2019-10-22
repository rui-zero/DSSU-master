/******************** Med-X Institute ********************
* File Name          : main.c
* Author             : Lishen Yin
* Date First Issued  : 4/23/2012
* Description        : Main program body
********************************************************************************
*Function including:
*int main(void)
********************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include "main.h"
#include "system.h"
#include "DAC2526.h"
#include "STM32_Reg.h" 
#include "STM32_Init.h"                           // STM32 Initializatio 
#include "stimulation.h"


vu8 reFlag = 1;								//�²�Ϊ ���ڴ�����
vu16 dataLenth = 0;							//���ݵ��ܳ��ȣ�����ͨ��Э����(datalenth-6)/6Ϊ��ͬб�ʵĶ���
vu8 dataBuf[3072];							//0,1��16λΪ������С��10�����1000����Ϊ10��
                                            //2,3��16λΪƵ��
											//6,7��16λΪ�̼�������8Ϊ���ӣ�9��10Ϊ��ĸ��11Ϊ�̼����ȣ���6B��48bΪһ�ε����
vu16 dataBufEnd = 0;
vu8 codeBuf = 0;							//1��ʾ����������2��ʾ��ʼ�̼�
vu8 codeUpdata = 0;		                    //�յ��Ĵ����б仯
vu16 stimulation_Freq = 0;
vu16 stimulation_width = 0;
vu8  stimulation_delay=0;
vu16 stimulation_Amp = 0;
vu8 dataIsReady = 0;						//������Ч���������
vu8 MUconnectFlag = 0;						//���ӱ�־λ 
vu8 stimulationStart = 0;					//��ʼ�̼���־λ
vu8 dataUpdata = 0;							//�����и���
vu8 dataReErr = 0;
vu8 *stimulation_para;						//databuf�ĵ�6��Byte
vu16 stimulation_para_Num = 0;				//��ͬб�ʵĶ���
ReceiveDataType receiveDataFromCom;				  //���ڽ������ݵ�
//MasterUnitStateType MasterUnitState;			  //MasterUnit״̬��־λ
//queueBufferType queueBuffer[8];					  //���еĻ�����
vu8 datajixu=0;


vu8 SensoryFeedbackSystem=0;   //��֪����ϵͳ
/******************************************��־λ********************************************/


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif


  System_initialization();
  initDAC2526();
  GPIO_SetBits(GPIOA, GPIO_Pin_12);
  GPIO_ResetBits(GPIOA, GPIO_Pin_11);
  GPIO_SetBits(GPIOA, GPIO_Pin_10);
	//Delay(10);
	USART2_Putc(0x002B);
	//Delay(10);
  while(1)
  {
	if (codeUpdata == 1)
	{
		switch (codeBuf)
		{
			case 1:
			MUconnectFlag = 1; 
			stimulationStart = 1;
			codeUpdata = 0;
			
			//CAN_Send_channel_Code(1,DSSU_ID);				 //DSSU_ID=0X01   Default
			
			break;
			case 2:
			stimulationStart = 0;						 //Ϊʲô��䲻��1���У�����
			codeUpdata = 0; 
			USART2_Putc(0x00BB);
			break;
			case 3: 
			USART2_Putc(0x00BC);
			//USART2_Putc(0x00C3);
			//USART2_Putc(0x00C4);  
      //USART2_Putc(0x00CF);
			//USART2_Putc(0x00D3);
			//USART2_Putc(0x0033);      
			codeUpdata=0;             //�����豸ʱӦ������6�ֽڣ���6�ֽ�Ϊ33��ʾ���ӳɹ�
			break;
			default:
			codeUpdata = 0;
			break;
		}
	}
	
	if ((dataUpdata == 1) && (reFlag == 0))
	{
			{
					stimulation_width = dataBuf[0];
					stimulation_width <<=8;
					stimulation_width =  stimulation_width + dataBuf[1];
					if ((stimulation_width < 10) && (stimulation_width > 1000))
					stimulation_width = 10;
					stimulation_Freq = dataBuf[2];
					stimulation_Freq <<=8;
					stimulation_Freq =  stimulation_Freq + dataBuf[3];
					stimulation_delay = dataBuf[4];  //�ӳ� rui  2019.10.14 ����ע��
					stimulation_para = &(dataBuf[6]);					      //���ʲô��?40 00    00   00 01   03 // �̼�������
					stimulation_para_Num = dataBuf[5];//(dataLenth - 6 )/6; //ѭ������
					if((stimulation_Freq>=10)&&(stimulation_Freq<=1000)&&(dataBuf[4]<=0xFF))
						{ if((dataBuf[11]<=255)&&(dataBuf[12]==0xFF)&&(dataBuf[13]==0xFF)&&(dataBuf[14]==0xFF))			//ȡ��120	���ƣ��ĳ�255								
							 //	00 28 00 0A 0A 01 40 00 00 00 01 03 FF FF FF
										{ 
											if( stimulation_width >10  )	
											{									
												dataIsReady = 1;
												dataUpdata = 0;
												if(SensoryFeedbackSystem==0) USART2_Putc(0x0029);
											}
						Delay(10);} }                        //��ʾ����������Ч������1�ֽ�29
						
			} 				
	}
	
	
	if (( MUconnectFlag == 1)&&(stimulationStart == 1)&&(dataIsReady == 1))
	{   
			Delay(10);
		stiumlationRun( stimulation_width,   //���������
		                stimulation_width,   //��������ȶ�
		                stimulation_Freq,    //
		                stimulation_para_Num,
		                stimulation_para,
		                stimulation_delay     );
		stimulationStart=0;	
	}
	
	if( (SensoryFeedbackSystem == 1 )&&(dataIsReady==1))    //  ��֪������������ָ��   2018.10.18
	{
	   			Delay(10);
		  stiumlationRun( stimulation_width,   //���������
		                  stimulation_width,   //��������ȶ�
		                  stimulation_Freq,    //
		                  stimulation_para_Num,
		                  stimulation_para,
		                  stimulation_delay     );
		
	   SensoryFeedbackSystem=0;
	}		

	if(dataReErr == 1)
	{
		dataReErr = 0;	
	}
  stimulationStart = 0; 	}
   
}


 

/************************END OF FILE*********************************************/
