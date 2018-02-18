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

// region responseAnalyze レスポンスを分析する

/**
 * responseAnalyze.
 * <p>
 * 返ってきたレスポンスを分析するメソッド
 *
 * @param func
 */
void CameraModule::responseAnalyze(int func, vector<char> response) {

  switch (func) {
    case (CameraModule::DETECT_RESPONSE) :
      // 物体検出結果を分析

      // エラー検出
      if (hasHeaderErr(&response)) {
        break;
      }

      // データ長さ取得
      int bodyNum = response.front();
      response.erase(response.begin());
      int handNum = response.front();
      response.erase(response.begin());
      int faceNum = response.front();
      response.erase(response.begin());

      // 0で固定されている分を削除 カメラモジュールの仕様.
      response.erase(response.begin());


      // 検出した体情報をbodyResultsに格納
      for(int i=0; i<bodyNum; i++){
        Result result;
        result.setPosX(getLongFromResponse(&response));
        result.setPosY(getLongFromResponse(&response));
        result.setSize(getLongFromResponse(&response));
        result.setConfidence(getLongFromResponse(&response));
        bodyResults_.push_back(result);
      }

      // 検出した体情報をbodyResultsに格納
      for(int i=0; i<handNum; i++){
        Result result;
        result.setPosX(getLongFromResponse(&response));
        result.setPosY(getLongFromResponse(&response));
        result.setSize(getLongFromResponse(&response));
        result.setConfidence(getLongFromResponse(&response));
        handResults_.push_back(result);
      }

      // 検出した体情報をbodyResultsに格納
      for(int i=0; i<faceNum; i++){
        Result result;
        result.setPosX(getLongFromResponse(&response));
        result.setPosY(getLongFromResponse(&response));
        result.setSize(getLongFromResponse(&response));
        result.setConfidence(getLongFromResponse(&response));
        faceResults_.push_back(result);
      }

      cerr << response.size();
      break;
    default :
      cerr;
  }

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

// region hasHeaderErr レスポンスのエラーチェック

/**
 * hasHeaderErr.
 * <p>
 * レスポンスにエラーがないかチェック
 *
 * @param response
 * @return false or true エラーがあればtrueを返す
 */
bool CameraModule::hasHeaderErr(vector<char> *response) {

  // 空っぽならエラー
  if (response->empty()) {
    return true;
  }

  // 1バイト目
  if (response->front() != 0xFE) {
    return true;
  }
  response->erase(response->begin() + 0);

  // 2バイト目
  if (response->front() != 0x00) {
    cerr << "err code is" << response->front() << "\n";
    return true;
  }
  response->erase(response->begin() + 0);

  return false;

}

// endregion

// region getLongFromResponse 2バイト読み込んでlongで返す

long CameraModule::getLongFromResponse(vector<char> *response) {

  // 空っぽならエラーで, -1を返す
  if(response->empty()){
    return -1;
  }

  long lsb, msb;
  lsb = response->front();
  msb = response->at(1);

  // 2バイト分消去
  response->erase(response->begin(), response->begin() + 1);

  // 8ビットMSBをシフトさせて, long型にして返す
  return lsb | msb<<8;

}

// endregion

