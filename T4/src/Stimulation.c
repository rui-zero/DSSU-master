/******************** Med-X Institute ********************
* File Name          : Stimulation.c
* Author             : Lishen Yin
* Date First Issued  : 10/21/2011
* Description        : STIMULATION program
********************************************************************************
*Function includes:
*void Stimulation( Data_TypeDef Data , StimIniPram_TypeDef StimIniPram )
*void Stimulate_Configuration(vu16 Freq)
*void  Stimulation_Single(vu16 StimPosTime, vu16 StimNegTime, vu16 StimAmp,vs8 Amplifier_integer, vs8 Amplifier_numerator, vu8 Amplifier_denominator)
*void Stimulation_Mono(vu16 StimPosTime,vu16 StimNegTime,vu16 StimulationNumber, vu16 StimFreq, vu16 StimAmp,vs8 Amplifier_integer, vs8 Amplifier_numerator, vu8 Amplifier_denominator)
********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stimulation.h"
#include "system.h"
#include "DAC2526.h"
#include "stm32f10x_lib.h" 




/************************************????????????,??????????****************************************************************/
vs16 fraction_index  = 0;				   //????,?????????
vs16 fraction_index2 = 0;				   //????,?????????
vu32 Period = 14400;  //T  related to Frequency	  //
vu8 int_flag = 0;  //?????	(Stimulation_single?????TIM???)
vu8 n_flag = 0;   //loop flag
vu16 StimulateAmpReal = 0;	  // The actual Amplitude in Stimulation
extern vu8 *stimulation_para;
extern vu16 stimulation_para_Num;
extern vu8 stimulationStart ;

extern vu8 SensoryFeedbackSystem;

vuc16 DACMap[121] = {0x0    , 0x04   , 0x08   , 0x0C   , 0x10   , 0x14   , 0x18   , 0x1C  , 0x20  , 0x24  ,
					 0x28  , 0x2C  , 0x30  , 0x34  , 0x38  , 0x3C  , 0x40  , 0x44  , 0x48  , 0x4C  ,
					 0x50  , 0x54  , 0x58  , 0x5C  , 0x60  , 0x64  , 0x68  , 0x6C  , 0x70  , 0x74  ,
					 0x78  , 0x7C  , 0x80  , 0x84  , 0x88  , 0x8C  , 0x90  , 0x94  , 0x98  , 0x9C  ,
					 0xA0  , 0xA4  , 0xA8  , 0xAC  , 0xB0  , 0xB4  , 0xB8  , 0xBC  , 0xC0  , 0xC4  ,
					 0xC8  , 0xCC  , 0xD0  , 0xD4  , 0xD8  , 0xDC  , 0xE0  , 0xE4  , 0xE8  , 0xEC  ,
					 0xF0  , 0xF4  , 0xF8  , 0xFC  , 0x100  , 0x104  , 0x108  , 0x10C  , 0x110  , 0x114  ,
					 0x118  , 0x11C  , 0x120  , 0x124  , 0x128  , 0x12C  , 0x130  , 0x134  , 0x138  , 0x13C  ,
					 0x140  , 0x144  , 0x148  , 0x14C  , 0x150  , 0x154  , 0x158  , 0x15C  , 0x160  , 0x164  ,
					 0x168  , 0x16C  , 0x170  , 0x174  , 0x178  , 0x17C  , 0x180  , 0x184  , 0x188  , 0x18C  , 0x190,
           0x194  , 0x198  , 0x19C  , 0x1A0  , 0x1A4  , 0x1A8  , 0x1AC  , 0x1B0  , 0x1B4  , 0x1B8  , 
	         0x1BC  , 0x1C0  , 0x1C4  , 0x1C8  , 0x1CC  , 0x1D0  , 0x1D4  , 0x1D8  , 0x1DC  , 0x1E0  };
 
					   
/*******************************************************************************
* Function Name  : Stimulation_Single
* Description    : stimulate one pulse
* Input          : vu16 StimPosTime, vu16 StimNegTime, vu16 StimAmp,vs8 Amplifier_integer, vs8 Amplifier_numerator, vu8 Amplifier_denominator
* Output         : None
* Return         : None
*******************************************************************************/
void  Stimulation_Single(vu16 StimPosTime, vu16 StimNegTime, oneTrainStimType oneTrainStim, u8 *pStimAmp,vu8 stimulation_delay)
{
	 u8 stimAmp;
	 u8 flag;
     u8 numerator;
     u8 integer;
	 
	 stimAmp = *pStimAmp;
	 TIM_Cmd(TIM2, ENABLE);		//??TIM


	 /*Positive Stimulation--time 100us------------------------------------------*/
	 if(stimAmp == 0)
	 {
	 }
	 else
	 {	
		       writeDACAandB(DACMap[10],DACMap[10]);
		       //writeDACAandB(DACMap[stimAmp],DACMap[stimAmp]);
		       //GPIO_SetBits(GPIOC, GPIO_Pin_5);
		       //GPIO_SetBits(GPIOB, GPIO_Pin_0);//postive pulsen start
		       GPIOB->BSRR = GPIO_Pin_0; 
		       GPIOC->BSRR = GPIO_Pin_5;

		      // writeDACAandB(DACMap[stimAmp],DACMap[stimAmp]);
		       Delay(1);
		      // GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		      // GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		       GPIOB->BRR = GPIO_Pin_0; 
		       GPIOC->BRR = GPIO_Pin_5;
		      	
      writeDACAandB(DACMap[stimAmp],0x0);
     	   
		  //Delay(5);
		     
     	GPIO_SetBits(GPIOB, GPIO_Pin_0);//postive pulsen start
		         
		 
    	Delay(StimPosTime-10);
    	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    	writeDACAandBtoZero(); //delay bewteen pp and np
    	//Delay(stimulation_delay);
		  
     	writeDACAandB(0x0, DACMap[stimAmp]);
	       
     // Delay(5);
		     
    	GPIO_SetBits(GPIOC, GPIO_Pin_5);
		      
    	Delay(StimNegTime-10);
    	GPIO_ResetBits(GPIOC, GPIO_Pin_5); 
		  Delay(50);
    	writeDACAandBtoZero();
	 }

    
//	vs8	zero=0;
    flag=1;
	if(oneTrainStim.numerator>0)
	{	 
	    flag=1;
		  numerator=oneTrainStim.numerator;
	}
	else if(oneTrainStim.numerator<=0)
  {
	  flag=0;
		numerator=(u8)(oneTrainStim.numerator&(0x7F));
		//numerator=zero-oneTrainStim.numerator ;
	}
   if(numerator!=0)
	 {integer=numerator/oneTrainStim.denominator;
	(*pStimAmp) = ChangeAmplifer(*pStimAmp,flag, integer,numerator-integer*oneTrainStim.denominator,oneTrainStim.denominator);	//(*pStimAmp) = ChangeAmplifer(*pStimAmp, oneTrainStim.numerator/oneTrainStim.denominator,oneTrainStim.numerator,oneTrainStim.denominator);
	//stimulationStart = 0;
	//USART2_Putc(0x00BC);
	Delay(10);
	 }
	while(int_flag == 0);	 //????
	int_flag = 0;
	TIM_Cmd(TIM2, DISABLE);	//??TIM 	
	 
}






/******************************************************************************
* Function Name  : Stimulation
* Description    : stimulation.
* Input          : None
* Output         : None
* Return         : None 
*******************************************************************************/
void stiumlationRun(u16 StimPosTime,u16 StimNegTime, u16 StimFreq,u16 StimulationNumber, vu8* stimulation_para,vu8 stimulation_delay)
{
	static u16 Frequncy=0;
	
	vu8* addr=stimulation_para;  //   2019.10.18 添加
 
	
	oneTrainStimType oneTrainStim;
	
	
	
	if(Frequncy!=StimFreq    ) //频率改变才需要配置定时器   2019.10.18 添加
	{
	   Frequncy=StimFreq;
		 TIM_Configuration(StimFreq);
	}
	
	
	while (StimulationNumber)
	{	
		stimulation_para=addr ; //重置到初始位置   2019.10.18 添加
		oneTrainStim.stimNumber = (vu16)(*stimulation_para++);
		oneTrainStim.stimNumber <<= 8;
		oneTrainStim.stimNumber = oneTrainStim.stimNumber + (vu16)(*stimulation_para++);		// 40 00
		oneTrainStim.numerator = *stimulation_para++;											// 00
		oneTrainStim.denominator = (vu16)(*stimulation_para++);
		oneTrainStim.denominator <<= 8;
		oneTrainStim.denominator = oneTrainStim.denominator + (vu16)(*stimulation_para++);		// 00 01
		oneTrainStim.stimAmp = *stimulation_para++;											    // 03
		if(stimulationStart==1)
		{
		   stimulationTrain(StimPosTime,StimNegTime,StimFreq,oneTrainStim,stimulation_delay);			 //????
		}
		else
        {
           break;
        }
		StimulationNumber--;
	}
}

/******************************************************

* Function Name  : stimulationTrain
* Description    : stimulation with amplitude going up or down monotonically.
* Input          : vu16 StimPosTime,vu16 StimNegTime,vu16 StimulationNumber, 
				 vu16 StimFreq, vu16 StimAmp,
					vs8 Amplifier_integer, vs8 Amplifier_numerator, vu8 Amplifier_denominator
* Output         : Stimulate pulse
* Return         : None
*******************************************************************************/

 




void stimulationTrain(u16 StimPosTime,u16 StimNegTime,u16 StimFreq,oneTrainStimType oneTrainStim,vu8 stimulation_delay)
{
	u8 *pStimAmp;
	u8 stimAmp;
	pStimAmp = &stimAmp;
	*pStimAmp = oneTrainStim.stimAmp;

 if(SensoryFeedbackSystem == 0)    	// 感知反馈系统不用应答
 { USART2_Putc(0x00AA);     }           
	while(oneTrainStim.stimNumber)
	{
      	if(stimulationStart==1)
     	{
		    Stimulation_Single(StimPosTime, StimNegTime, oneTrainStim,pStimAmp,stimulation_delay);
				//printf("ddd\n");
				//printf("%c\n",*pStimAmp);
		}
		else
	    {
	     	break;
	    }
		oneTrainStim.stimNumber=oneTrainStim.stimNumber-1;
	}
	 fraction_index  = 0;				   
   fraction_index2 = 0;

 if(SensoryFeedbackSystem == 0)    	// 感知反馈系统不用应答	
	USART2_Putc(0x00BB);                //??????
}

	


/*******************************************************************************
* Function Name  : ChangeAmplifer
* Description    : ??????????
* Input          : ????????,?????,????????,??????,??????
* Output         : ????????
* Return         : None						   
*******************************************************************************/
u8 ChangeAmplifer(vu8 Amplifier, u8 flag, vu8 Amplifier_integer, vu8 Amplifier_numerator, vu16 Amplifier_denominator)
{    if(flag==1)
	 {
     	Amplifier = Amplifier + Amplifier_integer;			//????
 		if (((fraction_index+1)*Amplifier_numerator) > ((fraction_index-fraction_index2)*Amplifier_denominator ))		  //????
		{
			Amplifier = Amplifier + 1;
			fraction_index ++;
		}
		else if (((fraction_index+1)*Amplifier_numerator) <= ((fraction_index-fraction_index2)*Amplifier_denominator ))
		{
			fraction_index ++;
			fraction_index2 ++;
		}
		else fraction_index = 0;

	}	
	else if (flag==0)
	{
		Amplifier = Amplifier - Amplifier_integer;
		
		if (((fraction_index+1)*Amplifier_numerator) > ((fraction_index-fraction_index2)*Amplifier_denominator ))		  //????
		{
			Amplifier = Amplifier - 1;
			fraction_index ++;
		}
		else if (((fraction_index+1)*Amplifier_numerator) <= ((fraction_index-fraction_index2)*Amplifier_denominator ))
		{
			fraction_index ++;
			fraction_index2 ++;
		}
		else fraction_index = 0;
	}
	return Amplifier;
}



 










/************************END OF FILE*********************************************/
