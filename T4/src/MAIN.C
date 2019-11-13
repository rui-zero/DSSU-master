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


vu8 reFlag = 1;								//猜测为 正在传数据
vu16 dataLenth = 0;							//数据的总长度，根据通信协议有(datalenth-6)/6为不同斜率的段数
vu8 dataBuf[3072];							//0,1共16位为脉宽，小于10或大于1000则视为10；
                                            //2,3共16位为频率
											//6,7共16位为刺激次数，8为分子，9，10为分母，11为刺激幅度，此6B共48b为一段的输出
											
											
vu16 dataBufEnd = 0;
vu8 codeBuf = 0;							//1表示连接求反馈，2表示开始刺激
vu8 codeUpdata = 0;		                    //收到的代码有变化
vu16 stimulation_Freq = 0;
vu16 stimulation_width = 0;
vu8  stimulation_delay=0;
vu16 stimulation_Amp = 0;
vu8 dataIsReady = 0;						//数据有效，可以输出
vu8 MUconnectFlag = 0;						//连接标志位 
vu8 stimulationStart = 0;					//开始刺激标志位
vu8 dataUpdata = 0;							//数据有更新
vu8 dataReErr = 0;
vu8 *stimulation_para;						//databuf的第6个Byte
vu16 stimulation_para_Num = 0;				//不同斜率的段数
ReceiveDataType receiveDataFromCom;				  //串口接收数据的
//MasterUnitStateType MasterUnitState;			  //MasterUnit状态标志位
//queueBufferType queueBuffer[8];					  //队列的缓存区
vu8 datajixu=0;


vu8 SensoryFeedbackSystem=0;   //感知反馈系统
vu8 SensoryFeedbackDataReady=0;
vu8 SensoryFeedbackDataBuf[3];
u16 stimulation_widthMax=0;  //脉宽最大值， 不可超过的值
/******************************************标志位********************************************/


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
			stimulationStart = 0;						 //为什么这句不在1当中？？？
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
			codeUpdata=0;             //搜索设备时应当返回6字节，第6字节为33表示连接成功
			break;
			default:
			codeUpdata = 0;
			break;
		}
		
		 codeBuf=0;
	}
	
	
	if ((dataUpdata == 1) && (reFlag == 0))
	{
			
					stimulation_width = dataBuf[0];
					stimulation_width <<=8;
					stimulation_width =  stimulation_width + dataBuf[1];

					
					stimulation_Freq = dataBuf[2];
					stimulation_Freq <<=8;
					stimulation_Freq =  stimulation_Freq + dataBuf[3];
					
					stimulation_delay = dataBuf[4];  //延迟 rui  2019.10.14 添加注释
					stimulation_para = &(dataBuf[6]);					      //这边什么鬼?40 00    00   00 01   03 // 刺激次数？
					stimulation_para_Num = dataBuf[5];//(dataLenth - 6 )/6; //循环次数
					
					stimulation_widthMax=1000000/stimulation_Freq/2 - 50;  // 计算脉宽的最大值		
					if ((stimulation_width < 11) || (stimulation_width>stimulation_widthMax)) //检查脉宽是否超过最大值
					     stimulation_width = 50;
					
					if((stimulation_Freq>=10)&&(stimulation_Freq<=1000)&&(dataBuf[4]<=0xFF))
					{ if((dataBuf[11]<=255)&&(dataBuf[12]==0xFF)&&(dataBuf[13]==0xFF)&&(dataBuf[14]==0xFF))			//取消120	限制，改成255								
							 //	00 28 00 0A 0A 01 40 00 00 00 01 03 FF FF FF
										{ 
											if( stimulation_width >10  )	
											{									
												dataIsReady = 1;
											
										  
												 USART2_Putc(0x0029);
											}
					Delay(10);} }                        //表示读入数据有效，返回1字节29
						
					dataUpdata = 0;			
	}
	
	
	if (( MUconnectFlag == 1)&&(stimulationStart == 1)&&(dataIsReady == 1))
	{   
		 Delay(10);
		 stiumlationRun( stimulation_width,   //正脉冲宽度
		                stimulation_width,   //负脉冲宽度度
		                stimulation_Freq,    //
		                stimulation_para_Num,
		                stimulation_para,
		                stimulation_delay     );
		stimulationStart=0;	
	}
	
	if(SensoryFeedbackSystem == 1 )     //  感知反馈跳过启动指令   2019.10.24
	{
		static u16 Frequncy=0;
		
		if(Frequncy!=stimulation_Freq    ) //频率改变才需要配置定时器   2019.10.24 添加
	  {
	       Frequncy=stimulation_Freq;
		     TIM_Configuration(stimulation_Freq);
	  }
		
    while(SensoryFeedbackSystem)
		{ 
			   if(SensoryFeedbackDataReady)
         {
				    stimulation_width = dataBuf[0];
				  	stimulation_width <<=8;
					  stimulation_width =  stimulation_width + dataBuf[1];
					
					  if ((stimulation_width < 11) || (stimulation_width > stimulation_widthMax)) //检查脉宽是否超过最大值
					  stimulation_width = 11;
						
						SensoryFeedbackDataReady=0;
				 }
			
		
	        Stimulation_SingleSFS( stimulation_width, 
		                             stimulation_width, 
		                             &dataBuf[11],         //电流幅值
		                             stimulation_delay );
		}
	}		

	if(dataReErr == 1)
	{
		dataReErr = 0;	
	}
	
  stimulationStart = 0; 	}
	
}


 

/************************END OF FILE*********************************************/

