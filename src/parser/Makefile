CC = clang++
CXXFLAGS = -O3 -std=c++11
LIBFLAGS = -lgmpxx

NAMELIST = declaration expression integer lex template_instance type
TARGET = parser

all : $(TARGET)

$(TARGET): $(addsuffix .o,$(NAMELIST))
	$(CC) $(CXXFLAGS) $(LIBFLAGS) $(addsuffix .o,$(NAMELIST)) -o $(TARGET).o

.cpp.o : $< $(<:.cpp=.hpp)
	$(CC) $(CXXFLAGS) $< -c -o $(<:.cpp=.o)
	
clear :
	rm ./*.o 
