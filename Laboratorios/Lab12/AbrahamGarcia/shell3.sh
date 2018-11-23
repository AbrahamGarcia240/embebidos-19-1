#!/bin/bash
arreglo=(12 9 24 2 15 21)
function suma1
{
let sum=0
for x in ${arreglo[*]}
do
	let sum=sum+x #uso let para que bash sepa que ahora ya no son cadenas, son numeros
done 

echo "La suma es : ${sum}"
}


cadena="Que pez"


echo "La cadena es : $cadena"
echo "El elemento 1 del arreglo es: ${arreglo[1]}" 
echo "El elemento 1 del arreglo es: ${arreglo[2]}"
echo "El elemento 1 del arreglo es: ${arreglo[3]}"
echo "Los elementos del arreglo son: ${arreglo[*]}"  
echo "El nnumero de elementos del arreglo es: ${#arreglo[*]} "

suma1

