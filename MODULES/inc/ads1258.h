#ifndef __ADS1258_H
#define __ADS1258_H

#include "stm32f4xx.h"

#define START PBout(12)

void ads1258_Init(void);
u8 ads1258_ReadRegister(u8 addr);
void ads1258_WriteRegister(u8 addr,u8 data);
void ads1258_ReadData(void);
void ad_Data_Proc_Eth(void);
void ad_Data_Proc_Gprs(void);
void convert_AD_RawData(void);
void convert_AD_RawData_avr(void);
void Send_AD_RawData_1(u8 i);
void Send_AD_RawData_2(u8 i);
void Send_AD_RawData_3(u8 i);
void Save_AD_RawData_SD(void);
void Save_AD_RawData_USB(void);
void ad_DataConvert(u8 result[4]);


#endif


