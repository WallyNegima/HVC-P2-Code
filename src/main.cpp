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
  cameraModule->responseAnalyze(CameraModule::DETECT_RESPONSE,
                                CameraModule::DETECT_OPTION1_ALL,
                                CameraModule::DETECT_OPTION2_ALL,
                                &response);
  cout << "Detect Results\n";
  vector<FaceResult> results = cameraModule->getFaceResults();
  for(auto itr = results.begin(); itr != results.end(); ++itr) {
    cout << "X          :" << itr->getPosX() << "\n";
    cout << "Y          :" << itr->getPosY() << "\n";
    cout << "Size       :" << itr->getSize() << "\n";
    cout << "Confidence :" << itr->getConfidence() << "\n";
    cout << "hDirection :" << itr->getHorizontalDirection() << "\n";
    cout << "vDirection :" << itr->getVerticalDirection() << "\n";
    cout << "inclination:" << itr->getInclination() < , "\n";
    cout << "age        :" << itr->getAge() << "\n";
    cout << "sex        :" << itr->getSex() << "\n";
    cout << "hSight     :" << itr->getHorizontalSight() << "\n";
    cout << "vSight     :" << itr->getVerticalSight() << "\n";
    cout << "eyeCloseL  :" << itr->getEyeCloseLeft() << "\n";
    cout << "eyeCloseR  :" << itr->getEyeCloseRight() << "\n";
    cout << "noneEx     :" << itr->getNoneEX() << "\n";
    cout << "joyEx      :" << itr->getJoyEx() << "\n";
    cout << "surpEx     :" << itr->getSurpriseEx() << "\n";
    cout << "angryEx    :" << itr->getAngryEx() << "\n";
    cout << "sadEx      :" << itr->getSadEx() << "\n";
    cout << "totalEx    :" << itr->getTotalEx() << "\n";
    cout << "faceId     :" << itr->getFaceId() << "\n";
  }


  // endregion

}
