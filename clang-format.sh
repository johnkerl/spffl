#!/bin/bash

# Temp: This needs to be a makefile target, CI job, etc.

clang-format -i $(find src  -name '*.h' -o -name '*.cpp')
clang-format -i $(find cli  -name '*.h' -o -name '*.cpp')
clang-format -i $(find test -name '*.h' -o -name '*.cpp')
