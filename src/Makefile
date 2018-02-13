CC := g++
CXXFLAGS := -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x  -lfluent
recompile: clean all
result.o: Result.cpp Result.hpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o result.o -c Result.cpp
module.o: CameraModule.cpp CameraModule.hpp result.o
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o module.o -c CameraModule.cpp result.o
main.out: main.cpp result.o module.o CameraModule.hpp Result.hpp 
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x  main.cpp result.o module.o -o main.out
all: result.o module.o main.out
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x main.cpp -o exe-camera.out result.o module.o
clean:
	$(RM) *.out *.o
