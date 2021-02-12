/**
  ******************************************************************************

  ADC Code For STM32F407VG
  Author:   Mouadh Dahech
  Updated:  1/16/2021

  ******************************************************************************
  Copyright (C) 

  ******************************************************************************




   ************* ADC Clock Configuration**********
  ************** STEPS TO FOLLOW *****************
	1. Enable ADC and GPIO clock
	2. Set the prescalar in the Common Control Register (CCR)
	3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)
	4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
	5. Set the Sampling Time for the channels in ADC_SMPRx
	6. Set the Regular channel sequence length in ADC_SQR1
	7. Set the Respective GPIO PINs in the Analog Mode
	************************************************/
//#define CR1 *((int*)0xffffffff)

#include "ADC.h"
void ADC_config()
{
  // 1. Enable ADC and GPIO clock
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

 // 2. Set the prescalar in the Common Control Register (CCR) 
  ADC->CCR |= ADC_CCR_ADCPRE_0;

 // 3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)
  ADC1->CR1 |= ADC_CR1_SCAN;
  ADC1->CR1 &= ADC_CR1_RES_0;
 
 // 4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
  ADC1->CR2 |= ADC_CR2_CONT;
  ADC1->CR2 |= ADC_CR2_EOCS;
  ADC1->CR2 &= ADC_CR2_ALIGN;

// 5. Set the Sampling Time for the channels in ADC_SMPRx
ADC1->SMPR1 |= ADC_SMPR1_SMP15_0;

// 6. Set the Regular channel sequence length in ADC_SQR1
ADC1->SQR1 |= (0x1 << 20);

// 7. Set the Respective GPIO PINs in the Analog Mode
GPIOC->MODER |= (0x3 << 10);

}

void ADC_Enable()
{
  // 1. Enable ADC 
  ADC1->CR2 |= (1 << 0);

 // Wait some Times the ADC to stablise 
  uint16_t i = 10000;
  while(i--);
}

void ADC_start(int channel)
{
	/************** STEPS TO FOLLOW *****************
	1. Set the channel Sequence in the SQR Register
	2. Clear the Status register
	3. Start the Conversion by Setting the SWSTART bit in CR2
	************************************************/
  
  ADC1->SQR3 = 0;
  ADC1->SQR3 |= (channel<<0);
  
  ADC1->SR  = 0;
  ADC1->CR2 |= (1<<30);  


}

uint16_t get_val (void)
{ 
  // Wait while conversion complete 
  while(!(ADC1->SR & (1<<1)));

  // return the conversion data 
  return ADC1->DR;
}
// 
void ADC_Disable()
{
  ADC1->CR2 &= ~(1<<0);
} 