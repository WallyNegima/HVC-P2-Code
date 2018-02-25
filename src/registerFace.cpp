//
// Created by 永間 on 2018/02/25.
//
#include "CameraModule.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;

// region const params

const string cameraPath = "/dev/hvcp2";
const int baudrate = 9600;

// endregion

int main(int argc, char* argv[]){

  CameraModule* cameraModule = new CameraModule();
  vector<char> response;

  // region connect to cameraModule

  cameraModule->connect(cameraPath, baudrate);

  // endregion

  if(argc != 4){
    cerr << argc << "\n";
    cerr << "FaceID, DataID, 名前をコマンドライン引数として入力してください\n";
    return -1;
  }

  while( response.empty() ){
    response = cameraModule->registerFace(
        atoi(argv[1]),
        atoi(argv[2])
    );
  }

  for(auto itr = response.begin(); itr != response.end(); ++itr){
    cout << *itr;
  }

}
