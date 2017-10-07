#include "Systick_helper.h"


void PLLSetup()
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); //Set system clock to 80 MHz	
	//SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ); (for a 50MHz clock speed)
}

void SystickSetup()
{
	NVIC_ST_CTRL_R = 0;              //disable SysTick during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF;   //maximum reload value
	NVIC_ST_CURRENT_R = 0;           //any write to current clears it
	NVIC_ST_CTRL_R = 0x00000005;     //enable SysTick with core clock

}

void Systick_Wait(uint32_t tickestdelay)        
{
	NVIC_ST_RELOAD_R = tickestdelay-1;            //number of counts to wait
	NVIC_ST_CURRENT_R = 0;                        //any value written to CURRENT clears
	while ((NVIC_ST_CTRL_R&0x0010000)==0) { }	    //wait for COUNT flag
}

void Systick_Wait10ms(uint32_t tickestdelay)
{
	for(uint32_t i = 0 ; i < tickestdelay ; i++)  
	{
		
		Systick_Wait(800000);                              //wait 10 ms. (12.5 ns period for 80MHz clock implies 800000 will set this function up properly)
    
	}
}