#include <stdint.h>
#include <stdbool.h>


/*
 * clock enable portf 0x400fe000+0x608 => 0x400fe608 => RCGCGPIO    (enable the clock to port F)
 * enabling digital pin 0x40025000+0x51c => 0x4002551c=>GPIOFDEN    ( to enable digital pins in the port F)
 * DIRECTION FOR PORTF 0X40025000+0X400 => 0X40025400 => GPIOFDIR   (to set port f pins as Input or output)
 * DATA TO PORTF 0X40025000+0X00 => 0X40025000=>GPIOFDATA           ( to write data into the output pins of port F)
 *
 */


int main(void)
{
    // declaring variables to access the registers
   unsigned int *RCGCGPIOF;
   int i;
   RCGCGPIOF = (unsigned int *)0x400FE608;
   unsigned int *GPIOFDEN;
   GPIOFDEN = (unsigned int *)0x4002551C;
   unsigned int *GPIOFDIR;
   GPIOFDIR = (unsigned int *)0X40025400;
   unsigned int *GPIOFDATA;
   GPIOFDATA = (unsigned int *)0X400253FC;
   *RCGCGPIOF = 0x00000020;// turning on the clock of port F
   *GPIOFDEN  = 0x0000000E;//since the RGB pins are location on P1 , P2 , P3
   *GPIOFDIR  = 0x0000000E;//since the RGB pins are location on P1 , P2 , P3
   while(1)
   {
       *GPIOFDATA = 0X02;
       for(i=0; i<800; i++)
        {}

       *GPIOFDATA = 0X00;
       for(i=0; i<800; i++) /*delay of 0.5ms*/
        {}

   }

}
