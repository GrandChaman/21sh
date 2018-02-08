#!/bin/bash

# Purpose : test typing normal characters and some delete to stdin

source ./test/lib.sh

assert 'Hello'"$KEYS_DELETE"'World' "HelloWorld$"
assert 'Hello'"$KEYS_LEFT$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE"'World' "HellWorld$"
assert 'Hello'"$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_LEFT$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE$KEYS_DELETE"'World' "World$"
assert 'HelloWorld'"$KEYS_DELETE" "HelloWorld$"
