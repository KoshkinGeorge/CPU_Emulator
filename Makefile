CC = g++
CFlags = -c
SOURCE = main.cpp
OBJECTS = ${SOURCE:.cpp=.o}
EXECUTABLE = CPU_Em

all: ${EXECUTABLE}
	./$<

%o: %cpp
	${CC} ${CFlags} $< -o $@

${EXECUTABLE}: ${OBJECTS}
	${CC} $^ -o ${EXECUTABLE}

clean:
	del -rf *.o ${EXECUTABLE}