CC := g++
CFLAGS := -g -m64 -O3 -std=c++2c -Wall -Wextra
INCLUDES := -I/usr/include
LFLAGS := -L/usr/lib
LIBS := -lboost_filesystem -lboost_program_options -lm

SRCS := fileutils.cpp funpaint.cpp memory.cpp gun2fun.cpp rle.cpp
PRES := $(SRCS:.cpp=.i)
OBJS := $(SRCS:.cpp=.o)

MAIN := main.cpp
TARGET := gun2fun

TEST := test.cpp

.PHONY: depend clean check

all: $(TARGET)

check: test
	./$<

test: $(TEST)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(OBJS) $(LFLAGS) $(LIBS)
	strip $@

run: $(TARGET)
	./$<

$(TARGET): $(MAIN) $(PRES) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(OBJS) $(LFLAGS) $(LIBS)
	strip $@

%.i: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -E $< -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.i *.o *~
	$(RM) test

distclean: clean
	$(RM) $(TARGET)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
