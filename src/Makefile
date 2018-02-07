CC := g++
CXXFLAGS := -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x  -lfluent
exe-camera: main.cpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -o exe-camera.out main.cpp
faceRegister: faceRegister.cpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x -lsqlite3 -o faceRegister.out faceRegister.cpp
test: test.cpp
	g++ -I/usr/local/include -L/usr/local/lib -lwiringPi -std=gnu++0x  -o libTester.out test.cpp
clean:
	$(RM) exe-camera faceRegister
