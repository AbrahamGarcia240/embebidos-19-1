# Para hacerlo ejecutable uso "chmod +x shell1.sh"


# Este es el interprete que va a usar el shell
#!/bin/bash

echo "Hola mundo..."
echo "La suma de  6 + 8=$((6+8))"

var=7
ver2=4

echo "La variable 1 es $var"
suma=$var+$ver2
echo "La suma es: $suma"

suma2=$(($var+$ver2))
echo "La suma es: $suma2"

suma3=$[$var+$ver2]
echo "La suma es: $suma3"

let "suma4=var+ver2"
echo "La suma es: $suma4"

echo "Dame el numero1:"
read num1

echo "Dame el numero2:"
read num2

suma2=$(($num1+$num2))
echo "La suma es: $suma2"

