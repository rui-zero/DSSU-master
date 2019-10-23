/******************** Med-X Institute ********************
* File Name          : Stimulation.h
* Author             : Lishen Yin
* Date First Issued  : 4/20/2012
* Description        : Main program body
********************************************************************************/

#ifndef __stimulation_h
#define __stimulation_h

#include "lcd.h"
#include "readdata.h"


typedef struct
{
	vu16 stimNumber;
	vs8	numerator;
	vu16 denominator;
	vu8 stimAmp;    
}oneTrainStimType;



/* Local includes ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/





/* Private functions ---------------------------------------------------------*/
void  Stimulation_Single_2(vu16 StimPosTime, vu16 StimNegTime,vu8 *pStimAmp,vu8 stimulation_delay);
void  Stimulation_Single(vu16 StimPosTime, vu16 StimNegTime, oneTrainStimType oneTrainStim,u8 *pStimAmp,vu8 stimulation_delay);
void stiumlationRun(u16 StimPosTime,u16 StimNegTime,u16 StimulationNumber, u16 StimFreq, vu8* paraBuf,vu8 stimulation_delay);
void stimulationTrain(u16 StimPosTime,u16 StimNegTime,u16 StimFreq,oneTrainStimType oneTrainStim,vu8 stimulation_delay);
u8 ChangeAmplifer(vu8 Amplifier, u8 flag, vu8 Amplifier_integer, vu8 Amplifier_numerator, vu16 Amplifier_denominator);






#endif /* __stimulation.h */
