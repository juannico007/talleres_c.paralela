BIN				:= serial, parallel, crear_vectores

CXX 			:= g++-10

CFLAGS		:= -std=c++14

LDFLAGS		:= -fopenmp

HEAD			:= merge_ser.hpp

SRC				:= merge_ser.cpp

HEADP			:= merge_par.hpp

SRCP			:= merge_par.cpp


serial:	main_s.cpp $(HEAD)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) main_s.cpp

parallel: main_p.cpp $(HEADP)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCP) main_p.cpp

crear_vectores:	crear_vectores.cpp $(HEAD)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) crear_vectores.cpp
