#include <iostream>
#include "CameraModule.hpp"
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

//methods

// region コンストラクタ

/**
 * CameraModule.
 *
 * コンストラクタ
 * @param path /dev/hvcp2 などのモジュールへのパス
 * @param boadrate ボーレート.USBなら9600固定
 */
CameraModule::CameraModule() {
}

// endregion

// region connect モジュールにコネクトする

/**
 * connect.
 * <p>
 * モジュールにコネクトする
 * @retun
 */

int CameraModule::connect(string path, int baudrate) {

  device_ = serialOpen(path.c_str(), baudrate);
  if (device_ < 0) {
    // シリアルオープンに失敗
    cerr << "cannot open " << path;
    return -1;
  }

  return device_;
}

// endregion

// region モジュールにコマンドを送る

/**
 * sendCommand.
 * モジュールにコマンドを送る.
 */
void CameraModule::sendCommand(){

  // 送受信中の情報を全て消去
  serialFlush(device_);

  // command_ にある全てのコマンド情報を送信
  for(auto itr = command_.begin(); itr != command_.end(); ++itr ){
    serialPutchar(device_, *itr);
  }

  //レスポンスまで少し時間がかかるため, まつ
  delay(500);

}

// endregion

// region モジュールからのレスポンスを受け取る

vector<char> CameraModule::getResponse(){
  vector<char> responses;

  while(serialDataAvail(device_)){
    responses.push_back(serialGetchar(device_));
  }

  return responses;

}


// endregion

// region デバイス情報を得る系のコマンド

/**
 * getDeviceInformation.
 * デバイス情報を得る.バージョン, 取付方向など.
 *
 * @param cmd
 * @return
 */
vector<char> CameraModule::getDeviceInformation(int cmd) {

  vector<char> response;

  // cmd によって送るコマンドをわける
  setHeader(&command_);
  switch(cmd){
    case (CameraModule::CMD_GET_VERSIONS) :
      //コマンド送信
      sendCommand();

      //レスポンスを得る
      response = getResponse();

      break;
    case (CameraModule::CMD_GET_CAMERA_DIRECTION) :
      break;
    default:
      cerr << "cannot send command\n";
  }

  return response;

}

// endregion

// region

/**
 * setHeader.
 * <p>
 * モジュールへ送るコマンドのヘッダー部分を作成
 *
 * @param command
 */
void CameraModule::setHeader(vector<char> *command) {

  command->clear();
  command->push_back(0xFE);
  command->push_back(0x00);
  command->push_back(0x00);
  command->push_back(0x00);

}

// endregion

