# EE 690 Lab Report 8
### Group : 1
### Name : Dixshant Jha and Kaushik Powar 
### ROLL NO. : EE23MT025 AND EE23MT011
### FACULTY ; Dr. ABHIJIT KSHIRSAGAR

## OBJECTIVE : 
 
Part 1:

Program a microcontroller to transmit:

"F0" if SW1 is pressed

"AA" if SW2 is pressed 

over UART with baud rate 9600 and odd parity. 

Your program should also listen for incoming data on the UART with the same baud and parity config; if "AA" is received LED should be GREEN; if "F0" is received, the LED should be BLUE and if any error is detected LED should be RED. Test this by communicating with your neighboring group.

### What is UART ?
UART is a common peripheral that allows the microcontroller to transmit and receive data in a serial format.

UART is a simple serial communication protocol that allows the transfer of data between 2 devices.

## Functional Description 
The UART is configured to transmit and receive via TEX and REX bits, which are set using UARTCTL(UART control) register.

### Initialization of UART :
1. Enabling the UART mode.  
2. Enable the clock to the appropriate GPIO module.
3. Setting the Alternate Function register.
4. Set the appropriate Baud Rate.
5. At Last setting the appropriate Register for performing the transmission and receiving of the data.


## Calculation :

System Clock Frequency (f) = 16 MHz
Baud Rate = 9600

BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)

BRD = (16 * 10^6)/16*9600

BRD = BRDI + BRDF = 104.16667

BRDI = 104 and BRDF = 0.16667

for Calculating the value for UARTFBRRD[DIVFRAC] = integer(BRDF * 64 + 0.5)
UARTFBRRD[DIVFRAC] = integer(0.16667 * 64 + 0.5) = 11


## Observation 

In the above experiment we perform the transmission and reception of the data in between 2 different boards using the TXE and RXE provided by the UART in the cortex m4 board. 
We program the board in accordance to the baud rate specified in the objective i.e, 9600. 
And using the baud rate we calculate the respective values and give the integral part to UARTIBRD and fraction part to UARTFBRD that needs to be initialized for the code functionality.
In the experiment we program the 2 board in such a way that the first board is responsible for the transmission of the specified data and the second board will receive the respective data and  Acknowledgment according to the received data by blinking the LED(Blue and Green) and also blink the Red LED whenever there is some error.
Whenever we press the switch 1 on the board1, 0xF0 is transmitted to the board and if the board2 receives the data without any error then the green LED will glow and if the switch2 is pressed then the blue LED will glow. In case of any error the red LED will glow. And to check that the transmitted data is wrong or write we will use the PD7 to transmit the data from board2 to the Oscilloscope and then observe the output as shown in the image below.

## Output :

### Output for F0 Transmite<br>

