#!/bin/bash
GOT=$(cat -e author 2>&-)
EXP="fle-roy$"
if [ "$GOT" == "$EXP" ]
then
	exit 0
else
	exit 1
fi
