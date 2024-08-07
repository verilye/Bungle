CC = clang++
CFLAGS = -g -Wall -std=c++17
SRCS = bungle.cpp parser.cpp token.cpp scanner.cpp error.cpp interpreter.cpp 
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
TARGET = bungle

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
