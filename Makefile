PROG	= vonatjegy
OBJ	= main.o jegy.o teljesjegy.o diakjegy.o gyujtojegy.o vonat.o datum.o heterostore.o menu.o memtrace.o
HEAD	= main.cpp utas.h jegy.h jegy.cpp diakjegy.h diakjegy.cpp gyujtojegy.h gyujtojegy.cpp vonat.h vonat.cpp datum.h datum.cpp heterostore.hpp heterostore.cpp menu.h menu.cpp memtrace.h memtrace.cpp gtest_lite.h
TEST	= input/standard_input.txt
DATA	= input/adatok.zip
JPORTA_PACK = main.cpp $(HEAD)

CXXFLAGS= -std=c++11 -Wall -Werror -g -DCPORTA -DMEMTRACE 

all:	$(PROG)

main: $(OBJ)
	$(CXX) -o $(PROG) $(OBJ)

$(OBJ): $(HEAD)

test:	$(PROG) $(TEST)
	for i in $(TEST); do \
	  ./$(PROG) < $$i ; \
	done 

clean:	
	rm -f $(PROG) $(OBJ)

tar:	
	tar -czf $(PROG).tgz $(SRC) $(HEAD) $(TEST) $(DATA)

zip:	
	zip kesz.zip $(JPORTA_PACK)
