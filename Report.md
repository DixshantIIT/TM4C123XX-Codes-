# Embedded Systems Lab Report

<!-- Insert your details here -->
* Kaushik Powar [ee23mt011@iitdh.ac.in] 
* Dixshant Jha [ee23mt025@iitdh.ac.in]
* Group: 01 <br>
* [02/10/2023]

### Problem Statement:

Generate a 50% duty cycle PWM waveform on TM4C123GH6PM, change the duty cycle of the signal on the press of on-board user switches

### Procedure:

#### Task 1: 
##### Create a PWM waveform with frequency = 100KHz and variable duty cycle.

The program should begin with d = 50%.

On pressing one switch the duty should be increased by 5% and on pressing other switch it should be decreased by 5%.

1. Enable System Clock as source to PWM Modules using RCC and RCGC registers.
2. Enable clock and initialize GPIO Port F accordingly.
3. Enable Interrupts on both the on-board switches.
4. Enable the Alternate function on the desired pin, where the PWM signal will be generated, using AFSEL and PCTL registers.
5. Disable/Turn off the PWM generator, Load the 'load' and 'compare' values in their respective registers, config the PWM genrator using the PWM_GENA(B) register, enable the the PWM generator and give the pwm signal to the desired pin.
6.On the press of user switch 1(2) increase(decrease) the duty cycle, by modifying the compare value.

#### Task 2:
##### Implement the same but using only 1 switch (SW1 OR SW2) – short press for d increase and long press for decrease.

1. Enable System Clock as source to PWM Modules using RCC and RCGC registers.
2. Enable clock and initialize GPIO Port F accordingly.
3. Enable Interrupts on both the on-board switches.
4. Enable the Alternate function on the desired pin, where the PWM signal will be generated, using AFSEL and PCTL registers.
5. Disable/Turn off the PWM generator, Load the 'load' and 'compare' values in their respective registers, config the PWM genrator using the PWM_GENA(B) register, enable the the PWM generator and give the pwm signal to the desired pin.
6. On the falling edge, when the user switch is pressed, turn on the systick timer and load a reload value in 'STRELOAD' register corresponding to 0.5 sec of delay.
7. On the rising edge, when the button is released, we check the 'COUNT_FLAG' of the systick timer, if set then we decrease the duty cycle, if not set then we increase the duty cycle of the pwm signal and turn of the systick timer.

### Measurements:

With 16MHz clock given to PWM module, to generate a 100kHz signal, we need to wait for 16MHz/100kHz clock cycles. Therefore, the load value for the PWM module is set to be 160.
To generate a PWM signal of 50 percent duty cycle, the compare value must be 160/2 = 80.
When increasing(decreasing) the duty cycle by 5% we must decrement(increment) the compare value by 8 units.

### Results:



PWM signals of different duty cycles are generated on TM4C123GH6PM
 
