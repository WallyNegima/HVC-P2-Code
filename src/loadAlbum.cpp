//
// Created by 永間 on 2018/02/25.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "CameraModule.hpp"
using namespace std;

// region const params

const string cameraPath = "/dev/hvcp2";
const int baudrate = 9600;

// endregion



int main(int argc, char* argv[]){

  CameraModule* cameraModule = new CameraModule();
  vector<char> response;

  // region connect to camera module

  cameraModule->connect(cameraPath, baudrate);

  // endregion

  // region load album data

  cameraModule->loadAlbum();

  // endregion

  cameraModule->responseAnalyze(
    CameraModule::LOAD_ALBUM,
    -1,
    -1,
    &response);
  cout << "load album!\n";

  return 0;
}
