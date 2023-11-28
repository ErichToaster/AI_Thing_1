CXX      := clang++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror
SRCS     := src/main.cpp src/evolution.cpp src/testenv1.cpp src/testenv2.cpp src/tools.cpp src/process.cpp src/manual_control.cpp
OBJS     := $(SRCS:.cpp=.o)
EXEC     := build/executable

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
