# SpearsEmbeddedSystemsMidterm

This program displays basic use and initialization of vital embedded system concepts including PWM, ADC, GPIO, UART, SysTick and more.     This code is not perfect but does exhibit important factors of modularity and cohesion. An effort was made to keep the code relatively clean and easy to understand. In preparing this program I have developed critical skills in understanding how embedded systems work and how to use them to achieve a goal. Additionally, I have gained the ability to program the key peripherals of the microcontroller.               

The structure of the program is as follows:                                                                                                  First, this program sets up the hardware needed for the main function by calling the SetupHardware function, which calls the setup routines for  the necessary hardware components.                                                                                                   Then, displays a user-friendly menu with options to choose from. Option 1 will cycle through the connected LEDs if a switch is pressed and display the values of the switches that aren't pressed in order to test the GPIO. Option 2 will test use of the SysTick by turn on an LED for exactly one second. Option 3 will visually display proper use of the PWM module by turning on 2 LEDs at different brightness levels. Option 4 will test the ADC by sampling 3 channels and printing their value to the user interface. If an unrecognized option is selected then the the program will print "Wai you do dis?"                                                                                           
