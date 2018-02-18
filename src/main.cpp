#include <stdio.h>
#include <iostream>
#include "CameraModule.hpp"
using namespace std;

// region const params

const string cameraPath = "/dev/hvcp2";
const int baudrate = 9600;

// endregion

int main(){
  CameraModule* cameraModule = new CameraModule();
  vector<char> response;

  // region connect to camera module

  cameraModule->connect(cameraPath, baudrate);

  // endregion

  // region get settings
  
  response = cameraModule->getDeviceInformation(CameraModule::CMD_GET_VERSIONS);
  cout << "Camera version\n";
  for(auto itr = response.begin(); itr != response.end(); ++itr){
    printf("0x%02X", *itr);
  }

  // endregion

  // region loop ditect face
  
  response = cameraModule->detectObject(
      CameraModule::DETECT_OPTION1_ALL,
      CameraModule::DETECT_OPTION2_ALL,
      CameraModule::IMAGE_OPTION_NON
  );

  cout << "\nDetect Results\n";
  for(auto itr = response.begin(); itr != response.end(); ++itr){
    printf("0x%02X", *itr);
  }

  // endregion

}
