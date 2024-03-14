CC = g++
CFlags = -c -Wall
SOURCES = main.cpp CPU_Em.cpp commands.cpp
OBJECTS = ${SOURCES:.cpp=.o}
EXECUTABLE = CPU_Em

all: ${EXECUTABLE}

%.o: %.cpp
	${CC} ${CFlags} $< -o $@

${EXECUTABLE}: ${OBJECTS}
	${CC} $^ -o $@

clean:
	del -rf *.o ${EXECUTABLE}.exe out.txt err.txt