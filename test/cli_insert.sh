#!/bin/bash

# Purpose : test typing normal characters after some arrows to stdin

source ./test/lib.sh

assert 'Hello'"$KEYS_LEFT"'World' "HellWorldo$"
assert 'Hello'"$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT"'World' "WorldHello$"
assert 'Hello'"$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT"'World' "WorldHello$"
assert 'Hello'"$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_RIGHT$KEYS_RIGHT$KEYS_RIGHT$KEYS_RIGHT$KEYS_RIGHT$KEYS_RIGHT$KEYS_RIGHT$KEYS_RIGHT$KEYS_RIGHT"'World' "HelloWorld$"
assert 'Hello'"$KEYS_UP$KEYS_UP$KEYS_UP"'World' "WorldHello$"
assert 'Hello'"$KEYS_DOWN$KEYS_DOWN$KEYS_DOWN"'World' "WorldHello$"
