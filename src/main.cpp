#include <stdio.h>
#include <iostream>
#include "CameraModule.hpp"
using namespace std;
//using namespace std::vector;

// region const params

const string cameraPath = "/dev/hvcp2";
const int baudrate = 9600;

// endregion

int main(){
  CameraModule* cameraModule = new CameraModule();

  // region connect to camera module

  cameraModule->connect(cameraPath, baudrate);


  // endregion

  // region get settings

  // endregion

  // region loop ditect face

  // endregion

}
