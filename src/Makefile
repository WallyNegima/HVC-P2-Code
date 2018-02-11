CC := g++
CXXFLAGS := -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x  -lfluent
recompile: clean all
result.o: Result.cpp Result.hpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o result.o -c Result.cpp
module.o: CameraModule.cpp CameraModule.hpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o module.o -c CameraModule.cpp
main: main.cpp result.o module.o 
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x main.cpp -o exe-camera.outresult.o module.o
all: result.o module.o main
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x main.cpp -o exe-camera.out result.o module.o
clean:
	$(RM) exe-camera.out *.o
