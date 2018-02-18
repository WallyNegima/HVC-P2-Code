#include <iostream>
#include "CameraModule.hpp"
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

//public methods

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

// region デバイス情報を得る系のコマンド

/**
 * getDeviceInformation.
 * <p>
 * デバイス情報を得る.バージョン, 取付方向など.
 *
 * @param cmd
 * @return response
 */
vector<char> CameraModule::getDeviceInformation(int cmd) {

  vector<char> response;

  // cmd によって送るコマンドをわける
  setHeader(&command_);
  switch (cmd) {
    case (CameraModule::CMD_GET_VERSIONS) :
      
      command_.push_back(0x00);
      command_.push_back(0x00);
      command_.push_back(0x00);

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

// region detectObject 物体検出実行メソッド

/**
 * detectObject.
 * <p>
 * 物体検出を行うメソッド
 *
 * @param option1 目つむり,視線,性別,年齢,顔向き,顔検出,手検出,体検出
 * @param option2 顔認証,表情
 * @param imageOption なし,QVGA,VGA
 * @return response
 */
vector<char> CameraModule::detectObject(char option1, char option2, char imageOption) {

  vector<char> response;

  // 顔を検出するコマンドをセット
  setHeader(&command_);
  command_.push_back(0x04);
  command_.push_back(0x03);
  command_.push_back(0x00);
  command_.push_back(option1);
  command_.push_back(option2);
  command_.push_back(imageOption);

  // モジュールにコマンド送信
  sendCommand();

  // レスポンスを受け取る
  response = getResponse();

  return response;

}

// endregion

// private methods

// region setHeader.

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

}

// endregion

// region モジュールにコマンドを送る

/**
 * sendCommand.
 * モジュールにコマンドを送る.
 */
void CameraModule::sendCommand() {

  // 送受信中の情報を全て消去
  serialFlush(device_);

  // command_ にある全てのコマンド情報を送信
  for (auto itr = command_.begin(); itr != command_.end(); ++itr) {
    serialPutchar(device_, *itr);
  }

  //レスポンスまで少し時間がかかるため, まつ
  delay(600);

}

// endregion

// region モジュールからのレスポンスを受け取る

vector<char> CameraModule::getResponse() {
  vector<char> responses;

  while (serialDataAvail(device_)) {
    responses.push_back(serialGetchar(device_));
  }

  return responses;

}

// endregion

