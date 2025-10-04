#!/usr/bin/env bash

wget http://192.168.1.177/index.php?SetButtonPressedLights=FF00000000 -O output.txt
wget http://192.168.1.177/index.php?SetButtonReleasedLights=00FF000000 -O output.txt
