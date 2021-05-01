BIN				:= serial, parallel

CXX 			:= mpic++

CFLAGS		:= 

LDFLAGS		:= 

HEAD			:= pgmio.hpp helper.hpp

SRC				:= pgmio.cpp helper.cpp

serial:	reconstruct_ser.cpp $(HEAD)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) reconstruct_ser.cpp

parallel: reconstruct_par_v2.cpp $(HEADP)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCP) reconstruct_par_v2.cpp

