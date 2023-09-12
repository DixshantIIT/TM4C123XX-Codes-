#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
/* SysTick memory-mapped registers */
#define STCTRL *((volatile long *) 0xE000E010)    // control and status
#define STRELOAD *((volatile long *) 0xE000E014)    // reload value
#define STCURRENT *((volatile long *) 0xE000E018)    // current value

#define COUNT_FLAG  (1 << 16)   // bit 16 of CSR automatically set to 1
                                //   when timer expires
#define ENABLE      (1 << 0)    // bit 0 of CSR to enable the timer
#define CLKINT      (1 << 2)    // bit 2 of CSR to specify CPU clock

#define CLOCK_MHZ 16

void Delay(int us)
{   STCURRENT = 0;
    STRELOAD = us*16;                       // reload value for 'ms' milliseconds
    STCTRL |= 0x05;        // set internal clock, enable the timer

    while ((STCTRL & COUNT_FLAG) == 0)  // wait until flag is set
    {
        ;   // do nothing
    }
    STCTRL = 0;                // stop the timer

    return;
}
void system_intialize()
{
           SYSCTL_RCGC2_R |= 0x00000020;       /* enable clock to GPIOF */
           GPIO_PORTF_LOCK_R = 0x4C4F434B;     /* unlock commit register */
           GPIO_PORTF_CR_R = 0x1F;             /* make PORTF0 configurable */
           GPIO_PORTF_DEN_R = 0x1E;            /* set PORTF pins 4 pin */
           GPIO_PORTF_DIR_R = 0x0E;            /* set PORTF4 pin as input user switch pin */
           GPIO_PORTF_PUR_R = 0x10;            /* PORTF4 is pulled up */
}

int main(void)
{
        system_intialize();

        while(1)
        {
            GPIO_PORTF_DATA_R = 0x02;
            Delay(200);
            GPIO_PORTF_DATA_R = 0x00;
            Delay(800);
        }

}
