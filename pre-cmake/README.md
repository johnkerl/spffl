For documentation please see https://github.com/johnkerl/spffl/wiki

# Setup disclaimer

This project was for self-education, as well as software support for my
master's thesis (http://johnkerl.org/doc/kerl-ma-thesis-gc.pdf).  My efforts at
portability were minimal.  Nonetheless Linux/x86 (which was my environment) has
become a broad standard.

Also note that SPFFL uses an out-of-source-tree build:  object files, shared
libraries, and executables go to `$HOME/bin/sp`.

# Setup

One-time setup:
```
mkdir -p $HOME/bin/sp
mkdir -p $HOME/bin/sp/dynamic

# In your bash init:
export PATH=${PATH}:$HOME/bin/sp
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$HOME/bin/sp/dynamic
```

Then:
```
make -C tools
```
This runs the `build` and `regression` targets.

# Regression tests vs. unit tests
Given my knowledge of best practices for software testing circa 2004, I created
regression tests to verify overall behavior, but I did not create unit tests to
help verify per-source-file behavior.  (I've learned more than a few things
since then.)  For more current testing methodology (along with greatly reduced
line count, and far more elegant type genericity using language dynamics rather
than C++ templates) please see RUFFL, my Ruby port of SPFFL:
https://github.com/johnkerl/ruffl
