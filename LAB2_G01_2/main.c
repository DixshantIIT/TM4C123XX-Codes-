// This program is to change the color of led on each press
// we have given a delay to prevent debounce

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
int main(void)
{
 SYSCTL_RCGC2_R |= 0x00000020; /* enable clock to GPIOF */
 GPIO_PORTF_LOCK_R = 0x4C4F434B; /* unlock commit register */
 GPIO_PORTF_CR_R = 0x1F; /* make PORTF0 configurable */
 GPIO_PORTF_DEN_R = 0x1E; /* set PORTF pins 4 pin */
 GPIO_PORTF_DIR_R = 0x0E; /* set PORTF4 pin as input user switch pin */
 GPIO_PORTF_PUR_R = 0x10; /* PORTF4 is pulled up */
 int i;
 int x=0;
 int prev=0,present=0; /*to detect the edge*/
 while(1){
 present = GPIO_PORTF_DATA_R & 0x10;
 if(prev==0x10 & present==0x0) /*a leading edge is detected*/
 {
 x=x+1; /*sequrntial setting of the LEDs*/
 for(i=0;i<800;i++){} /* debouncing */
 }
 if(x%3==0)
 {GPIO_PORTF_DATA_R = 0x02;}
 if(x%3==1)
 {GPIO_PORTF_DATA_R = 0x04;}
 if(x%3==2)
 {GPIO_PORTF_DATA_R = 0x08;}
 prev=present;
 }

}
