# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = SimpleCTRNNMain
TARGET2 = VisualAgent

default: $(TARGET) $(TARGET2)

$(TARGET):  RANDOM CTRNN SIMPLECTRNNMAIN
	$(CC) $(CFLAGS) CTRNN.o random.o SimpleCTRNNMain.o -o $(TARGET)

$(TARGET2):  RANDOM CTRNN VISUAL_AGENT SIMPLE_VISUAL_MAIN
	$(CC) $(CFLAGS) CTRNN.o random.o VisualAgent.o SimpleVisualMain.o -o $(TARGET2)


SIMPLECTRNNMAIN:
	$(CC) $(CFLAGS) -c SimpleCTRNNMain.cpp

CTRNN:
	$(CC) $(CFLAGS) -c CTRNN.cpp

RANDOM:
	$(CC) $(CFLAGS) -c random.cpp

VISUAL_AGENT:
	$(CC) $(CFLAGS) -c VisualAgent.cpp

SIMPLE_VISUAL_MAIN:
	$(CC) $(CFLAGS) -c SimpleVisualMain.cpp

# VECTORMATRIX:
# 	$(CC) $(CFLAGS) -c VectorMatrix.cpp


clean:
	$(RM) $(TARGET) $(TARGET2) *.o
