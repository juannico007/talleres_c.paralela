BIN 				:=	main_s main_p


CFLAGS			:=  -std=c++14
LDFLAGS			:=  -pthread


CXX 				:=  g++

HEADS				:= matrix_one.hpp helper.hpp
SRC					:= matrix_one_s.cpp helper.cpp
SRCP  			:= matrix_one_p.cpp helper.cpp


main_s: main_s.cpp $(HEADS)
	$(CXX) $(CFLAGS) -o $@ $(SRC) main_s.cpp

main_p: main_p.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCP) main_p.cpp

clean:
	rm $(BIN) *.o core*
