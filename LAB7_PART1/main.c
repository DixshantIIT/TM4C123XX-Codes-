#include<stdio.h>
#include<stdint.h>
#include"tm4c123gh6pm.h"

void CLOCK_Init()
{
    SYSCTL_RCGCPWM_R |=(1<<1);    // enable and provide clock to pwm 1 module
    SYSCTL_RCGCGPIO_R |= (1<<5);  //enable clock to PORTF
    SYSCTL_RCC_R &= ~(1<<20);     // disabling this bit means system clock is the source for pwm
}
void PIN_Init()
{GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R = 0x01;
GPIO_PORTF_DIR_R = 0x0E;
GPIO_PORTF_DEN_R = 0x1F;
GPIO_PORTF_PUR_R = 0x11;
    GPIO_PORTF_AFSEL_R |= (1<<2);          // setting port f pin 2 as alternate function reg
    GPIO_PORTF_PCTL_R |= ((1<<10)|(1<<8)); // setting PF2 as M1PWM6
    // initializing switch 1 and switch 2 as input pins
    GPIO_PORTF_DIR_R &= ~((1<<0)|(1<<4));
    GPIO_PORTF_PUR_R |= 0x11; // enabling pull up resistors for sw1 and sw2
    GPIO_PORTF_DEN_R |= (1<<2)|(1<<0)|(1<<4); // digital enabling switches
}
void PWM_Init()
{   PWM1_3_CTL_R &= ~(1<<0); // disabling the counter before generating PWM
    PWM1_3_CTL_R &= ~(1<<1); // setting down counting mode
    PWM1_3_LOAD_R |= 160; // loading 160 in the register for a time period of 100khz
    PWM1_3_CMPA_R = 80;   // comparator value for 50% duty cycle
    PWM1_3_GENA_R = (1<<3) | (1<<2) | (1<<7);
    PWM1_3_CTL_R |= (1<<0); // enabling the counter
    PWM1_ENABLE_R |= (1<<6);
}
void GPIO_Interrupt_Init()
{
    GPIO_PORTF_IM_R &= ~(0x11); // masking sw1 and sw2.
    GPIO_PORTF_IS_R &= ~(0x11); // edge triggered
    GPIO_PORTF_IBE_R &= ~(0x11);// interrupt generation controlled by GPIOIEV
    GPIO_PORTF_IEV_R |= 0x11; // rising edge causes and interrupt
    GPIO_PORTF_IM_R |= 0x11;  // unmasking sw1 and sw2

    // setting priorities using NVIC
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF1FFFFF) |(1<<21);
    NVIC_EN0_R |=(1<<30);
}
void GPIO_Interrupt_handler()
{ int k;
    k=GPIO_PORTF_MIS_R;
    GPIO_PORTF_IM_R &= ~(0x11);//sw1 and sw2 masked

    /* pressing Switch 1 -> Decreases duty cycle by 5%
     * pressing Switch 2 -> Increases duty cycle by 5%
     */
    int i = 10000;
    if(k & 0X01) //interrupt on switch 1
    {   while(i--);// for debounce
        if(PWM1_3_CMPA_R < 152)
            PWM1_3_CMPA_R += 8; // increasing duty cycle by 5%
    }
    if(k & 0X10) // Interrupt on switch 2
    {   while(i--); // for debounce
        if(PWM1_3_CMPA_R > 8)
            PWM1_3_CMPA_R -= 8;// decreasing the duty cycle by 5%
    }
    GPIO_PORTF_IM_R |= 0x11; // unmasking sw1 and sw2
    GPIO_PORTF_ICR_R |= 0x11;

}


void main()
{
    CLOCK_Init();
    PIN_Init();
    PWM_Init();
    GPIO_Interrupt_Init();
    while(1){}// do nothing

}
