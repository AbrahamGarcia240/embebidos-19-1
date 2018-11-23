#!/bin/bash
 
#Este programa configura el BCM_GPIO 17 usando el FHS y un script de shell
#declaro el arreglo de pines a usar
pin=(17 18 27 22 23 24 25 )

my_string1="/sys/class/gpio/gpio"
#export - Sirve para exportar el control del GPIO desde el kernel al espacio de usuario,
#escribiendo su número al archivo.

direction="/direction"

for x in ${pin[*]}
do
     my_string="$my_string1${x}"
     my_string="$my_string$direction"
    echo ${x} > /sys/class/gpio/export
    echo "out" > ${my_string}
    echo $my_string
done


 
#direction - Atributo que configura la direccion de entrada (in) o salida (out) del gpio



#declaro el arreglo para el gpio17
gp17=(0 1 1 0 1 0 1 0 1 1)
#declaro la cadena del gpio17

my_string2="/value"
 
#value - Atributo que permite escribir un valor digital al GPIO

#declaro una variable de control
let i=0
while [ 1 ]
do
    if [ $i -gt 9 ] 
    then 
        let $i=0
    fi
    for x in ${pin[*]} #para cada segmento
    do
         my_string="$my_string1${x}"
         my_string+="$my_string2"
        echo "${gp17[${i}]}" > ${my_string}
        sleep 1
    done
done
#unexport - Revierte el efecto de exportar al espacio de usuario,
#escribiendo su número al archivo.

un="/sys/class/gpio/unexport"
for x in ${pin[*]}
do
    echo ${x} > ${un}
    echo "out" > ${my_string}
done

exit 0

