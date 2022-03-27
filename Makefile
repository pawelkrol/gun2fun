CC := g++
CFLAGS := -g -m64 -O3 -std=c++20 -Wall -Wextra
INCLUDES := -I/usr/include
LFLAGS := -L/usr/lib
LIBS := -lboost_filesystem -lboost_program_options -lm

SRCS := fileutils.cpp gun2fun.cpp
OBJS := $(SRCS:.cpp=.o)

MAIN := main.cpp
TARGET := gun2fun

.PHONY: depend clean

all: $(TARGET)

test: $(TARGET)
	chmod a+x $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
	strip $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~

distclean: clean
	$(RM) $(TARGET)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
