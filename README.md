For documentation please see https://github.com/johnkerl/spffl/wiki

# Setup disclaimer

This project, from 2004-2005, was for self-education, as well as software support for my master's
thesis (https://johnkerl.org/doc/kerl-ma-thesis-gc.pdf).  My efforts at portability were minimal.
Nonetheless Linux/x86 (which was my environment) has become a broad standard.

As of 2023 I'm using this repo as a little experiment, to port the build system
from [yamm](https://github.com/johnkerl/scripts/blob/main/fundam/yamm) to [cmake](https://cmake.org).

# Setup

```
cmake -B build'
cmake --build build'
cmake --build build --target test'
cmake --build build --target install' # <-- WIP as of 2023-03-13
```

TODO: more here about tests, libraries, and executables.

# See also

Please also see [RUFFL](https://github.com/johnkerl/ruffl), my Ruby port of SPFFL.
