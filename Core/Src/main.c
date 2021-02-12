
/**
  ******************************************************************************

  ADC Code For STM32F407VG
  Author:   Mouadh Dahech
  Updated:  1/16/2021

  ******************************************************************************
  Copyright (C) 

  ******************************************************************************
*/



#include "main.h"

uint16_t ADC_VAL[2] = {0,0};


int main(void)
{
  SystemClock();
  ADC_config();
  ADC_Enable();

  while (1)
  {
    ADC_start(15);
    ADC_VAL[0] = get_val();

    ADC_start(14);
    ADC_VAL[1] = get_val();   
  }
  return 0 ; 
}