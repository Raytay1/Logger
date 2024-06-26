# the compiler: gcc for C program, define as g++ for C++
  CC = g++
 
  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
  CFLAGS= -g -Wall
  LDLIBS= -pthread
 
  # The build target 
  TARGET = logger
 
  all: $(TARGET)
 
  $(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LDLIBS)
 
  clean:
	$(RM) $(TARGET)