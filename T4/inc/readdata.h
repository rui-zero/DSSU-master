/******************** Med-X Institute ********************
* File Name          : readdata.h
* Author             : Lishen Yin
* Date First Issued  : 4/20/2012
********************************************************************************/


#ifndef __ReadData_h
#define __ReadData_h






/* Private typedefine ---------------------------------------------------------*/
typedef struct				 //  刺激参数结构体，每次执行单调刺激前读取的参数
{
vu16 StimulationNumber;
vu16 StimAmp ;
vs8 StimAddInt ;
vs8 StimAddNem ;
vu8 StimAddDen ;
vu16 StimMonoTime ;
} StimPram_TypeDef ;



typedef struct			  //初始刺激参数结构体，执行所有刺激前读取的通用参数
{
vu16 StimPosTime ;
vu16 StimNegTime ;
vu16 StimFreq ;
vu16 DataLength;
} StimIniPram_TypeDef;



typedef struct 					   //数据结构体，包括储存空间和指针
{
vu8 Storage[900];
vu8 *front;
vu8 *end;
vu8 *now;
} Data_TypeDef;






/* Private functions ---------------------------------------------------------*/

StimIniPram_TypeDef ReadData(Data_TypeDef *Data);




























#endif /* ___ReadData_h */
