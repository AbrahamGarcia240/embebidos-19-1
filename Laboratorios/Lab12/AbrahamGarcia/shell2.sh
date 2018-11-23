#!/bin/bash

function suma
{
	
	result=$(($1+$2))
	echo $result
}

function resta
{
	
	result=$(($1-$2))
	echo $result
}

function prod
{
	
	result=$(($1*$2))
	echo $result
}

function Cociente
{
	
	result=$(($1/$2))
	echo $result
}


echo "1.- Suma"
echo "2.- Resta"
echo "3.- Producto"
echo "4.- Cociente"
echo "Dame la opcion"
read opcion




case $opcion in
	1) 
	echo "Dame el numero1:"
	read num1

	echo "Dame el numero2:"
	read num2
	suma num1 num2;;

			
	2)
	echo "Dame el numero1:"
	read num1

	echo "Dame el numero2:"
	read num2
	resta num1 num2;;
	

	3)
	echo "Dame el numero1:"
	read num1

	echo "Dame el numero2:"
	read num2
	prod num1 num2;;

	4)
	echo "Dame el numero1:"
	read num1

	echo "Dame el numero2:"
	read num2
	Cociente num1 num2;;
	

	*)
	echo "POR ESO MEXICO ESTA COMO ESTA";;
esac




