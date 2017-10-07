#include "Gpio_helper.h"


	
void GpioSetup()
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);               //Enable GPIO peripherals
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))         //Wait for peripherals to be ready
    {
    
		}
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
    {
    
		}
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
    
		}
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    
		}

		
		// Set GPIO output pins
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3); //Set ports for on-board LED as outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //^^^^^
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1); //^^^^^
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0); //Set ports for external LEDs as outputs
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1); //^^^^^
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2); //^^^^^
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3); //^^^^^
		
		//Set on-board momentary switches as inputs
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
		GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
		
		//Set off-board momentary switches as inputs
		GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_1);
	  GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,GPIO_PIN_3);
		
		//Configure switch type
		GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU); //PortF
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);	
		GPIOPadConfigSet(GPIO_PORTD_BASE,GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU); //PortD
		GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_3,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU); //PortE
	}
		
void CycleLEDS ()
{
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0xF);        //Turns on an LED
  for(int ui32Loop = 0; ui32Loop < 500000; ui32Loop++)   //delays for a bit
  {
	}      
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x0);        //Turns off and LED and continues for the rest of the LEDs
	
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0xF);        //^^^
  for(int ui32Loop = 0; ui32Loop < 500000; ui32Loop++)
  {
	}      
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x0);
	
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xF);        //^^^
  for(int ui32Loop = 0; ui32Loop < 500000; ui32Loop++)
  {
	}      
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x0);
	
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0xF);        //^^^
  for(int ui32Loop = 0; ui32Loop < 500000; ui32Loop++)
  {
 	}      
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x0);
	
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0xF);        //^^^
  for(int ui32Loop = 0; ui32Loop < 500000; ui32Loop++)
  {
 	}      
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
	
}

void TestSwitches()
{
	int8_t switchE3;                                              
	int8_t switchD1;
	int8_t switchSW1;
	switchE3 = GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_3);   //Reads in pin values and stores them as variables
	switchD1 = GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_1);
  switchSW1 = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
	if ( switchE3 < 1)                                    //If a switch is pressed then cycle through through connected LEDs
		CycleLEDS();              
	else                                                  //Otherwise let the user know that the switch is set high and print its value 
		printf("\nSwitch E3 set high (%d)\n", switchE3);    //                 (continue for the rest of the LEDs)
	
	if ( switchD1 < 1)
		CycleLEDS();
	else
		printf("\nSwitch D1 set high (%d) \n", switchD1);
	
	if ( switchSW1 < 1)
		CycleLEDS();
	else
		printf("\nSwitch SW1 set high (%d) \n", switchSW1);
 }
		
	