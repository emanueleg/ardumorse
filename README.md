# ardumorse

Code for morse encoding and decoding using two Arduino boards and two simple sensors.
View the system in action in this [youtube video](https://youtu.be/SznNOC0IWmg).

## Setup

**Transmitter**
* Arduino
* Active Buzzer Alarm Module (such as YL-44) attached to digital pin (#6 in the code)
* USB connection and a serial terminal for sending text 

**Receiver**
* Arduino
* 1KY-038 (KY-038 Microphone Sound Sensor Module DC5V) attached to analog pin (#2 in the code)
* USB connection and a serial terminal for showing text

##Decoding implementation notes
At startup, the average environmental audio level (called noise_floor) is obtained.
Then, the microphone is used to capture multiple (20) samples and to obtain the average audio level. If the average level is above the noise floor (plus a small threshold, let's say 5%), the audio level is considered HIGH; LOW otherwise.

##Morse Implementation notes
The morse code is stored into an array of integers. Specifically, dots and lines have been converted into binary values: dot -> 0, lines -> 1. Hence SOS (... --- ...) becomes 000, 111, 000. However, for example, A (.-) becomes 01 while T (-) is 1: these two binary values are both equals to 1. 
For this reason, a 1 has been prepended to all codes: A is stored as 101, while T is 11. 
Before transmitting, the initial 1 is discarded.
