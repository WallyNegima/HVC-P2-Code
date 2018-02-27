//
// Created by 永間 on 2018/02/27.
//
#include <stdio.h>
#include <iostream>
#include "CameraModule.hpp"
using namespace std;

// region const params

const string cameraPath = "/dev/hvcp2";
const int baudrate = 9600;

// プロトタイプ宣言
int checkCommand(int inputNum);

int main(int argc, char* argv[]){

  CameraModule* cameraModule = new CameraModule();
  vector<char> response;

  // region connect to camera module

  cameraModule->connect(cameraPath, baudrate);

  // endregion

  // 無限ループで色々できる
  while(true){
    int inputNum, responseNum;
    cout << "-----MENUS-----\n";
    cout << CameraModule::DETECT_RESPONSE << " : 顔を検出する\n";
    cout << CameraModule::REGISTER_FACE << " : 顔を認証して登録する\n";
    cout << CameraModule::SAVE_ALBUM << " : アルバム情報をファイルに保存\n";
    cout << CameraModule::LOAD_ALBUM << " : アルバム情報をファイルからカメラに読み込む\n";
    cout << CameraModule::DELETE_ALBUM << " : アルバム情報をカメラから削除\n";
    cout << "99: EXIT\n";
    cout << "入力\n";
    cin >> inputNum;

    responseNum = checkCommand(inputNum);
    if( responseNum == -1){
      break;
    }

  }

  cout << "FINISH\n";

  return 0;

}

int checkCommand(int inputNum){
  switch (inputNum){
    case (CameraModule::DETECT_RESPONSE) : {
      cout << "DETECT OBJECT\n";

      return CameraModule::DETECT_RESPONSE;

    }
    case (CameraModule::REGISTER_FACE) : {
      cout << "REGISTER FACE\n";

      return CameraModule::REGISTER_FACE;
    }
    case (CameraModule::SAVE_ALBUM) : {
      cout << "SAVE ALBUM\n";

      return CameraModule::SAVE_ALBUM;
    }
    case (CameraModule::LOAD_ALBUM) : {
      cout << "LOAD ALBUM\n";

      return CameraModule::LOAD_ALBUM;
    }
    case (CameraModule::DELETE_ALBUM) : {
      cout << "DELETE ALBUM\n";

      return CameraModule::DELETE_ALBUM;
    }
    case (99) : {
      return -1;
    }
  }
}

