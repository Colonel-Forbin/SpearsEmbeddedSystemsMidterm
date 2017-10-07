#include "ADC_PWM_helper.h"


void PWMSetup() //Sets up AND starts PWM on PB6
{
	GPIOPinTypePWM(GPIO_PORTB_BASE,GPIO_PIN_6); //Configure GPIO PB6 as a PWM pin
	GPIOPinConfigure( GPIO_PB6_M0PWM0 );        //Set GPIO PB6 to PWM0  
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); //Enable PWM0 peripheral
	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)) //Wait for PWM0 to be ready
    {    
		}
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); //Set the PWM generator for count down mode with immediate updates to the parameters
	PWMGenPeriodSet(PWM0_BASE,PWM_GEN_0, 8000);    //Sets a 10 KHz frequency for the 80 MHz clock
  PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,1500);   //Creates a 18.75% duty cycle 
  PWMGenEnable(PWM0_BASE, PWM_GEN_0);		         //Start timers in generator 0
	PWMOutputState(PWM0_BASE, (PWM_OUT_0_BIT | PWM_OUT_1_BIT), true);		//Enable the output
}

void TestPWM() //Displays the PWM in full working order by visually comparing brightness of two LEDs
{
	PWMSetup();                                                         //Send PWM signal
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0xF);                     //Send full-strength signal
	for(int ui32Loop = 0; ui32Loop < 50000000; ui32Loop++)              //delay to soak in the PWM beauty
  {
 	}
	PWMOutputState(PWM0_BASE, (PWM_OUT_0_BIT | PWM_OUT_1_BIT), false);  //Turn off PWM signal
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x0);                     //Turn off full-strength signal
	
	
}

void ADCSetup()
{
	uint32_t ADCvalueE0; //Value for the for ADC data to be stored in
	uint32_t ADCvalueE1;
	uint32_t ADCvalueE4;
	
	GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4); //Configure GPIO pins for ADC
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);                       //Enable ADC0 module
	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) { }             //Wait for ADC0 to be ready
	
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 1);     //Set trigger type and priorities for ADC sequences
	ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 2);     //^^^
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 3);     //^^^
	
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_IE | ADC_CTL_END |ADC_CTL_CH3);  //Set step number and configure channel numbers for ADC sequences
	ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_IE | ADC_CTL_END |ADC_CTL_CH2);  //^^^
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END |ADC_CTL_CH9);  //^^^
	
	ADCSequenceEnable(ADC0_BASE, 1);                                  //Enable ADC sampling on sequences 1,2 and 3
	ADCSequenceEnable(ADC0_BASE, 2);                                  //^^^
	ADCSequenceEnable(ADC0_BASE, 3);                                  //^^^
	
	ADCProcessorTrigger(ADC0_BASE, 1);                                //Triggers ADC sampling sequence 1
	while(!ADCIntStatus(ADC0_BASE, 1, false)) { }                     //Wait until sampling sequence 1 is complete
	ADCSequenceDataGet(ADC0_BASE, 1, &ADCvalueE0);                    //Read in sampling sequence 1 value(s) 
	
	ADCProcessorTrigger(ADC0_BASE, 2);                                //Triggers ADC sampling sequence 2
	while(!ADCIntStatus(ADC0_BASE, 2, false)) { }                     //Wait until sampling sequence 2 is complete
	ADCSequenceDataGet(ADC0_BASE, 2, &ADCvalueE1);                    //Read in sampling sequence 2 value(s)
	
	ADCProcessorTrigger(ADC0_BASE, 3);                                //Triggers ADC sampling sequence 3
	while(!ADCIntStatus(ADC0_BASE, 3, false)) { }                     //Wait until sampling sequence 3 is complete
	ADCSequenceDataGet(ADC0_BASE, 3, &ADCvalueE4);                    //Read in sampling sequence 3 value(s)
	
	
	printf("\n ADC E0 value = %d \n", ADCvalueE0);                    //Print sampling sequence 1 value(s)
	printf("\n ADC E1 value = %d \n", ADCvalueE1);                    //Print sampling sequence 2 value(s)
	printf("\n ADC E4 value = %d \n", ADCvalueE4);                    //Print sampling sequence 3 value(s)
	
	
}
