g++ \
	-g \
	-I../utils -I../classes \
	-L$HOME/bin/sp/dynamic -lspffl \
	../classes/qpoly_t.cpp \
	qff.cpp cyclopoly.cpp
	#-I. -I$HOME/bin/sp/inc \
