/******************** Med-X Institute ********************
* File Name          : readdata.h
* Author             : Lishen Yin
* Date First Issued  : 4/20/2012
********************************************************************************/


#ifndef __ReadData_h
#define __ReadData_h






/* Private typedefine ---------------------------------------------------------*/
typedef struct				 //  �̼������ṹ�壬ÿ��ִ�е����̼�ǰ��ȡ�Ĳ���
{
vu16 StimulationNumber;
vu16 StimAmp ;
vs8 StimAddInt ;
vs8 StimAddNem ;
vu8 StimAddDen ;
vu16 StimMonoTime ;
} StimPram_TypeDef ;



typedef struct			  //��ʼ�̼������ṹ�壬ִ�����д̼�ǰ��ȡ��ͨ�ò���
{
vu16 StimPosTime ;
vu16 StimNegTime ;
vu16 StimFreq ;
vu16 DataLength;
} StimIniPram_TypeDef;



typedef struct 					   //���ݽṹ�壬��������ռ��ָ��
{
vu8 Storage[900];
vu8 *front;
vu8 *end;
vu8 *now;
} Data_TypeDef;






/* Private functions ---------------------------------------------------------*/

StimIniPram_TypeDef ReadData(Data_TypeDef *Data);




























#endif /* ___ReadData_h */
