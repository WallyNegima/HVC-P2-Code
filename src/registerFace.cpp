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

  // faceID, DataID, 名前を入力していなかったら終了
  if(argc != 4){
    cerr << argc << "\n";
    cerr << "FaceID, DataID, 名前をコマンドライン引数として入力してください\n";
    return -1;
  }

  // 顔を検出して認証するまでコマンドを送信
  while( response.empty() ){
    response = cameraModule->registerFace(
        atoi(argv[1]),
        atoi(argv[2])
    );
  }

  // モジュールからのレスポンスを解析して, 検出結果を得る
  cameraModule->responseAnalyze(CameraModule::REGISTER_FACE,
                                -1,-1, &response);

  FaceResult result = cameraModule->getFaceResults().front();
  cout << "userID     :" << argv[1];
  cout << "dataID     :" << argv[2];
  cout << "userName   :" << argv[3];
  cout << "imageWidth :" << result.getImageWidth();
  cout << "imageHeight:" << result.getImageHeight();

}
