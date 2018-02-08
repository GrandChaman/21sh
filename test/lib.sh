#!/bin/bash

# List of importants keys

KEYS_ESC=$'\e'
KEYS_HOME=$'\e'[1~
KEYS_HOME2=$'\e'[H
KEYS_INSERT=$'\e'[2~
KEYS_BACKSPACE="\x7f"
KEYS_DELETE=$'\e'[3~
KEYS_END=$'\e'[4~
KEYS_END2=$'\e'[F
KEYS_PAGEUP=$'\e'[5~
KEYS_PAGEDOWN=$'\e'[6~
KEYS_UP=$'\e'[A
KEYS_DOWN=$'\e'[B
KEYS_RIGHT=$'\e'[C
KEYS_LEFT=$'\e'[D
KEYS_NUMPADUNKNOWN=$'\e'[G
NL=$'\n'

assert() {
	SHELL_RESULT=$(printf "$1\n" | ./21sh | cat -e)
	if [ "$(diff <(echo "$SHELL_RESULT") <(echo "$2"))" != "" ]
	then
		echo "$SHELL_RESULT != $2"
		exit 1
	fi
}
