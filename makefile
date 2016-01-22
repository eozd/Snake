CXX = clang++
CXXFLAGS = -g -O -Wall -Weffc++ -pedantic  \
-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
-Wcast-qual -Wconversion \
-Wdisabled-optimization \
-Werror -Wfloat-equal -Wformat=2 \
-Wformat-nonliteral -Wformat-security  \
-Wformat-y2k \
-Wimport  -Winit-self  \
-Winvalid-pch   \
-Wlong-long \
-Wmissing-field-initializers -Wmissing-format-attribute   \
-Wmissing-include-dirs -Wmissing-noreturn \
-Wpacked  -Wpadded -Wpointer-arith \
-Wredundant-decls \
-Wshadow -Wstack-protector \
-Wstrict-aliasing=2 -Wswitch-default \
-Wunreachable-code -Wunused \
-Wunused-parameter \
-Wvariadic-macros \
-Wwrite-strings -w -Wl,-subsystem,windows \
-std=c++11

TARGET = bin/main.exe

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
LIB = -lsfml-graphics -lsfml-window -lsfml-system
INC = -Iinclude

$(TARGET): $(OBJECTS)
	$(CXX) $(LIB) -o $@ $^

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	rm $(OBJECTS)
	rm $(TARGET)

tester:
	$(CXX) $(CXXFLAGS) test\tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: cleanles to either reference or create
