#!/bin/bash

# Purpose : test typing normal characters to stdin

source ./test/lib.sh

assert "Hello World" "Hello World$"
assert "How are you doing pal ?" "How are you doing pal ?$"
assert "That's some $NL pretty code" "That's some $"
