CC := g++
CXXFLAGS := -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x  -lfluent
recompile: clean all
result.o: Result.cpp Result.hpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o result.o -c Result.cpp
module.o: CameraModule.cpp CameraModule.hpp result.o
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o module.o -c CameraModule.cpp result.o
all: result.o module.o main.cpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o cam.out main.cpp result.o module.o
register.out: faceRegister.cpp module.o result.o
    g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o register.out registerFace.cpp result.o module.o
clean:
	$(RM) *.out *.o
