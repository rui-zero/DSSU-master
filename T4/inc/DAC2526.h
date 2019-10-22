/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DAC2526_H
#define __DAC2526_H

#include  "stm32f10x_lib.h"



void initDAC2526(void);
void writeToDAC2526(u16 StimAmp);
void writeDACAandB(u16 StimAmpA,u16 stimAmpB);
void writeDACAandBtoZero(void);

#endif /* __DAC2526_H */
