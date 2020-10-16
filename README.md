# TmxPro's Fanmod code

This readme is bit empty, I will update it soon with tutorials on how to actually use the code :)

## Arduino

Arduino project to flash onto your arduino.
This will work with no modifications on all atmega328 based boards.


## Python

This script will take temps from the system(or from iLO) and controls the fans via the Arduino.

This script needs pyserial and wmi on windows or psutil on linux to work.
On windows you need to have Open Hardware Monitor running to get the temps.
https://openhardwaremonitor.org/