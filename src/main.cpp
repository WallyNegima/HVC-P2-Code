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

  // region get settings and コネクション確認
  while( response.empty() ) {
    response = cameraModule->getDeviceInformation(CameraModule::CMD_GET_VERSIONS);
  }

  // endregion

  // region loop detect face

  response.clear();
  while( response.empty() ) {
    response = cameraModule->detectObject(
        CameraModule::DETECT_OPTION1_ALL,
        CameraModule::DETECT_OPTION2_ALL,
        CameraModule::IMAGE_OPTION_NON
    );
  }
  cameraModule->responseAnalyze(CameraModule::DETECT_RESPONSE, &response);
  cout << "Detect Results\n";
  vector<Result> results = cameraModule->getFaceResults();
  for(auto itr = results.begin(); itr != results.end(); ++itr){
    cout << "X          :" << itr->getPosX() << "\n";
    cout << "Y          :" << itr->getPosY() << "\n";
    cout << "Size       :" << itr->getSize() << "\n";
    cout << "Confidence :" << itr->getConfidence() << "\n";
  }


  // endregion

}
