For documentation please see https://github.com/johnkerl/spffl/wiki

# Setup disclaimer

This project, from 2004-2005, was for self-education, as well as software support for my master's
thesis (https://johnkerl.org/doc/kerl-ma-thesis-gc.pdf).  My efforts at portability were minimal.
Nonetheless Linux/x86 (which was my environment) has become a broad standard.

As of 2023 I'm using this repo as a little experiment, to port the build system
from [yamm](https://github.com/johnkerl/scripts/blob/main/fundam/yamm) to [cmake](https://cmake.org).

# Setup

Still a WIP. Generate/build/test/install steps:

```
alias cmz='cmake --build build --target clean && rm -rf build'

alias  cmg='cmake -B build'
alias cmgd='cmake -B build -DCMAKE_BUILD_TYPE=Debug'

alias  cmb='cmake --build build'
alias  cmt='cmake --build build --target test'
alias  cmi='cmake --build build --target install' # <-- WIP as of 2023-03-13

export PATH=$(pwd)/build/cli/spiff:$PATH
cd regression
sh regress.sh
```

To get more details about failed unit tests including line numbers:

* Run `cmg` and `cmb`
* In place of `cmt`, `./build/test/bits/test_bits` (or whichever test executable)

TODO: more here about tests, libraries, and executables.

# Compiler selection

```
cmz
cmg -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++
cmb -v
```

TODO:
```
-DCMAKE_INSTALL_PREFIX=$prefix
```

# Library use (WIP)

```
$ cmz
$ cmg -DCMAKE_INSTALL_PREFIX=./dist
$ cmb
$ cmt
$ cmi

$ g++ -std=c++20 -I dist/spffl/include -L dist/lib -lspffl examples/example1.cpp -o example1
$ install_name_tool -add_rpath $(pwd)/dist/lib example1

$ ./example1 abc def
736a54
```

# See also

Please also see [RUFFL](https://github.com/johnkerl/ruffl), my Ruby port of SPFFL.
