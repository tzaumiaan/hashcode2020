CXX=g++ # Apple clang
#CXX=/usr/local/bin/g++-9 # GNU GCC
CXXFLAGS=-std=c++14 -O2 -Wall -Wextra -Wunused -Werror

SRCS=main.cpp
TARGET=main

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -rf $(TARGET)
