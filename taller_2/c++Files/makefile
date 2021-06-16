BIN				:= serial, parallel, crear_vectores

CXX 			:= g++

CFLAGS		:= -std=c++14

LDFLAGS		:= -fopenmp

HEAD			:= merge_ser.hpp helper.hpp

SRC				:= merge_ser.cpp helper.cpp

HEADP			:= merge_par.hpp helper.hpp

SRCP			:= merge_par.cpp helper.cpp


serial:	main_s.cpp $(HEAD)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) main_s.cpp

parallel: main_p.cpp $(HEADP)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCP) main_p.cpp

crear_vectores:	crear_vectores.cpp $(HEADP)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCP) crear_vectores.cpp
