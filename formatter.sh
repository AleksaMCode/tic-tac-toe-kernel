#!/bin/bash
# The cool idea for formatting is from: https://stackoverflow.com/a/36046965/9917714
find src/ -iname *.h -o -iname *.c | xargs clang-format -i
