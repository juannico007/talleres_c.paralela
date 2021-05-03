BIN				:= serial, parallel

CXX 			:= g++
CXXP			:= mpic++
CFLAGS		:= 

LDFLAGS		:= 

HEAD			:= pgmio.hpp

SRC				:= pgmio.cpp 

serial:	reconstruct_ser.cpp $(HEAD)
	$(CXX) $(CFLAGS) -o $@ $(SRC) reconstruct_ser.cpp

parallel: reconstruct_par.cpp $(HEAD)
	$(CXXP) $(CFLAGS) -o $@ $(SRC) reconstruct_par.cpp

