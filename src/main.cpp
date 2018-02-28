#include <stdio.h>
#include <iostream>
#include "CameraModule.hpp"
using namespace std;

// region const params

const string cameraPath = "/dev/hvcp2";
const int baudrate = 9600;

// endregion

// プロトタイプ宣言
int checkCommand(int inputNum, CameraModule* cameraModule, vector<char> response);

int main(){

  CameraModule* cameraModule = new CameraModule();
  vector<char> response;

  // region connect to camera module

  cameraModule->connect(cameraPath, baudrate);

  // endregion


  // region check

  while( response.empty() ) {
    response = cameraModule->getDeviceInformation(CameraModule::CMD_GET_VERSIONS);
  }
  response.clear();

  // endregion

  // region ループ

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

    responseNum = checkCommand(inputNum, cameraModule, response);

    if( responseNum == 99){
      break;
    }

  }

  // endregion

  cout << "FINISH\n";

  return 0;

}

int checkCommand(int inputNum, CameraModule* cameraModule, vector<char> response){

  switch (inputNum){

    case (CameraModule::DETECT_RESPONSE) : {

      cout << "DETECT OBJECT\n";

      // region loop detect face

      // 顔を検出するまで, コマンドをモジュールに送信し続ける
      while( response.empty() ) {
        response = cameraModule->detectObject(
            CameraModule::DETECT_OPTION1_ALL,
            CameraModule::DETECT_OPTION2_ALL,
            CameraModule::IMAGE_OPTION_NON
        );
      }

      // モジュールからのレスポンスを解析して, 検出結果を得る
      cameraModule->responseAnalyze(CameraModule::DETECT_RESPONSE,
                                    CameraModule::DETECT_OPTION1_ALL,
                                    CameraModule::DETECT_OPTION2_ALL,
                                    &response);

      // 検出結果のプリント
      cout << "Detect Results\n";
      vector<FaceResult> results = cameraModule->getFaceResults();
      for(auto itr = results.begin(); itr != results.end(); ++itr) {
        cout << "X          :" << itr->getPosX() << "\n";
        cout << "Y          :" << itr->getPosY() << "\n";
        cout << "Size       :" << itr->getSize() << "\n";
        cout << "Confidence :" << itr->getConfidence() << "\n";
        cout << "hDirection :" << itr->getHorizontalDirection() << "\n";
        cout << "vDirection :" << itr->getVerticalDirection() << "\n";
        cout << "inclination:" << itr->getInclination() << "\n";
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

      return CameraModule::DETECT_RESPONSE;

    }
    case (CameraModule::REGISTER_FACE) : {

      cout << "REGISTER FACE\n";

      // region register face

      int faceId, dataId;
      string name;

      cout << "faceIDを入力:";
      cin >> faceId;
      cout << "dataIDを入力:";
      cin >> dataId;
      cout << "名前を入力:";
      cin >> name;

      while(true){
        // 顔を検出して認証するまでコマンドを送信
        while( response.empty() ){
          response = cameraModule->registerFace(
              faceId,
              dataId
          );
        }

        // モジュールからのレスポンスを解析して, 検出結果を得る
        cameraModule->responseAnalyze(CameraModule::REGISTER_FACE,
                                      -1,-1, &response);

        // エラー処理
        if(cameraModule->hasError()){
          cout << "retry\n";
        }else{
          break;
        }

      }
      
      FaceResult result = cameraModule->getFaceResults().front();
      cout << "userID     :" << faceId << "\n";
      cout << "dataID     :" << dataId << "\n";
      cout << "userName   :" << name << "\n";
      cout << "imageWidth :" << result.getImageWidth() << "\n";
      cout << "imageHeight:" << result.getImageHeight() << "\n";

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

      cout << "saved to Module ROM!\n";

      // endregion

      return CameraModule::REGISTER_FACE;
    }
    case (CameraModule::SAVE_ALBUM) : {

      cout << "SAVE ALBUM\n";

      // region save album to file

      // アルバム情報をホストへ吐き出す
      response = cameraModule->saveAlbum();
      cameraModule->responseAnalyze(CameraModule::SAVE_ALBUM,
                                    -1, -1, &response);

      // エラー処理
      if(cameraModule->hasError()){
        cerr << "error save album to file\n";
        return -1;
      }

      cout << "save album data to 'album.txt!'";

      // endregion

      return CameraModule::SAVE_ALBUM;
    }
    case (CameraModule::LOAD_ALBUM) : {

      cout << "LOAD ALBUM\n";

      // region load album data

      cameraModule->loadAlbum();

      cameraModule->responseAnalyze(
          CameraModule::LOAD_ALBUM,
          -1,
          -1,
          &response);

      if(cameraModule->hasError()){
        cerr << "error load album\n";
        return -1;
      }

      // endregion

      return CameraModule::LOAD_ALBUM;
    }
    case (CameraModule::DELETE_ALBUM) : {

      cout << "DELETE ALBUM\n";

      // 顔を検出するまで, コマンドをモジュールに送信し続ける
      while( response.empty() ) {
        response = cameraModule->deleteAlbum();
      }

      cameraModule->responseAnalyze(
          CameraModule::DELETE_ALBUM,
          -1,
          -1,
          response
      );

      if(cameraModule->hasError()){
        cerr << "error : delete album\n";
        return -1;
      }

      return CameraModule::DELETE_ALBUM;
    }
    case (99) : {
      return 99;
    }

  }

  return -1;
}

