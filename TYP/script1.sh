#!/bin/bash
X1=$1
X2=$2
X1=$(( $X1+$X2 ))
echo $X1
if [ $X1 -gt 0 ] ; then
    echo "Сумма положительна"
elif [ $X1 -lt 0 ] ; then
    echo "Сумма отрицательна"
else
    echo "Сумма нулевая"
fi