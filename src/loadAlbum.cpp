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

  // モジュールのアルバム情報をROMに保存
  response = cameraModule->registerToModuleRom();

  //解析してエラーが無ければ情報をプリント
  cameraModule->responseAnalyze(CameraModule::REGISTER_TO_ROM,
                                -1, -1, &response);

  // エラー処理
  if(cameraModule->hasError()){
    cerr << "error save to rom\n";
    return -1;
  }

  return 0;
}
