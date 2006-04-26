#!/bin/bash

hname=`hostname`
mystr=`expr substr "$hname" 1 6`

if [ "$mystr" == "shadow" ] 
then
	echo "shadow"
else
	echo $hname
fi 
