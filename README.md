# ardumorse

Arduino


See the system in action in this [youtube video](https://youtu.be/SznNOC0IWmg).

## Setup

**Transmitter**
* Arduino
* Active Buzzer Alarm Module (such as YL-44) attached to digital pin (#6 in the code)
* USB connection and a serial terminal for sending text 

**Receiver**
* Arduino
* 1KY-038 (KY-038 Microphone Sound Sensor Module DC5V) 
* USB connection and a serial terminal for showing text

##Decoding implementation notes
At startup the average environmental level (noise floor) is obtained.
The, the microphone is used to capture multiple (20) samples and obtain the average audio level. If the average level is above the noise floor (plus a small threshold, let's say 5%), the audio level is considered HIGH, LOW otherwise

##Morse Implementation note
