CC = g++
CXXFLAGS = -O3 -std=c++11

NAMELIST = declaration expression integer lex template_instance type
TARGET = parser
OBJS = ../string/string_iterator.o

all : $(TARGET)

$(TARGET): $(addsuffix .o,$(NAMELIST))
	$(CC) $(CXXFLAGS) $(addsuffix .o,$(NAMELIST)) $(OBJS) -o $(TARGET).o

.cpp.o : $< $(<:.cpp=.hpp)
	$(CC) $(CXXFLAGS) $< -c -o $(<:.cpp=.o)
	
clear :
	rm ./*.o 
