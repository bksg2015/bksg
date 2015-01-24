CC = clang++
CXXFLAGS = -O3 -std=c++11
LIBFLAGS = -lgmpxx

NAMELIST = utf8_string_iterator
TARGET = string_iterator

all : $(TARGET)

$(TARGET): $(addsuffix .o,$(NAMELIST))
	cp $(addsuffix .o,$(NAMELIST)) $(addsuffix .o, $(TARGET))

.cpp.o : $< $(<:.cpp=.hpp)
	$(CC) $(CXXFLAGS) $< -c -o $(<:.cpp=.o)
	
clear :
	rm ./*.o 
