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
 while(1)
 {
 if (GPIO_PORTF_DATA_R &= 0x10) //button isnt pressed
 {
 GPIO_PORTF_DATA_R = 0X00; /* dark */
 }
 else //button is pressed
 {
 GPIO_PORTF_DATA_R = 0X0E; /* white */
 }
 return 0;
 }
}
