# TmxPro's Fanmod code

## Arduino

Arduino project to flash onto your arduino.
This will work with no modifications on all atmega328 based boards.


## Python

This script will take temps from the system(or from iLO) and controls the fans via the Arduino.

This script needs pyserial and wmi on windows or psutil on linux to work.
On windows you need to have Open Hardware Monitor running to get local temps.
https://openhardwaremonitor.org/

On linux you could just run install.sh to copy:
- systemd service file to right position
- script to /opt/fanmod/
- config will be in etc (fanmod.ini)

After that you can modify the config and enable the service as an usual systemd service:

systemd enable --now hpfans