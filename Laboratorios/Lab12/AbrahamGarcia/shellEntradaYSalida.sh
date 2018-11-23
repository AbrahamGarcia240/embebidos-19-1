#!/bin/bash

echo "17" > /sys/class/gpio/export #hacer un for para cada puerto que voy a usar

echo "out" > /sys/class/gpio17/direction #lo habilito como salida, en este caso use gpio17


while [ 1 ]
	echo "1" > /sys/class/gpio/gpio17/value
	#sleep 1
	echo "0" > /sys/class/gpio/gpio17/value
done

echo "17" > /sys/class/gpio/unexport
exit 0