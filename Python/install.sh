#!/bin/bash
if [ "$EUID" -ne 0 ]
	then echo "Please run as root"
	exit
fi
pip3 install -r requirements.txt
cp hpfans.service /etc/systemd/system/
mkdir /opt/fanmod
cp controller.py /opt/fanmod
cp exampleconfig.ini /etc/fanmod.ini
systemctl reload-daemon