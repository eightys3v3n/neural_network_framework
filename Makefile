c=g++
norm=$c -std=c++17 -Wall -Wextra
part=$c -std=c++17 -Wall -Wextra -c

all: tests console


# universal
find.o: find.cpp
	$(part) find.cpp -o find.o

simulation.o: simulation.cpp
	$(part) -o simulation.o simulation.cpp

network.o: network.cpp level.hpp
	$(part) -o network.o network.cpp

level.o: level.cpp neuron.hpp
	$(part) -o level.o level.cpp


# tests
tests: mainTest.o findTest.o find.o neuronTest.o neuron_console.o
	$(norm) mainTest.o findTest.o find.o neuronTest.o neuron_console.o -o tests

mainTest.o: mainTest.cpp findTest.o
	$(part) mainTest.cpp -o mainTest.o

findTest.o: findTest.cpp find.o
	$(part) findTest.cpp -o findTest.o

neuronTest.o: neuronTest.cpp neuron_console.o
	$(part) neuronTest.cpp -o neuronTest.o


# console builds
console: find.o math_console.o neuron_console.o level.o network_console.o main_console.o simulation.o
	$(norm) main_console.o find.o math_console.o network_console.o level.o neuron_console.o simulation.o -o console

main_console.o: main.cpp network.hpp graphics.hpp
	$(part) -o main_console.o main.cpp

network_console.o: network.cpp level.hpp
	$(part) -o network_console.o network.cpp

neuron_console.o: neuron.cpp
	$(part) -o neuron_console.o neuron.cpp

graphics_console.o: graphics.cpp network.hpp
	$(part) -o graphics_console.o graphics.cpp

math_console.o: math.cpp
	$(part) -o math_console.o math.cpp

clean:
	if [ -n "*.o" ]; then rm *.o; fi