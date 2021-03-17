BIN				:= serial, parallel, serial_pruebita

CXX 			:= g++-10

CFLAGS		:= -std=c++14

LDFLAGS		:= -fopenmp

HEAD			:= merge_ser.hpp

SRC				:= merge_ser.cpp

HEADP			:= merge_par.hpp

SRCP			:= merge_par.cpp

HEAD_PR 	:= serial_pruebita.hpp

SRCPR			:= serial_pruebita.cpp

serial:	main_s.cpp $(HEAD)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) main_s.cpp

parallel: main_p.cpp $(HEADP)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCP) main_p.cpp

serial_pruebita: main_s.cpp $(HEAD_Pr)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCPR) main_s.cpp
