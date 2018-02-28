#include <iostream>
#include "CameraModule.hpp"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>

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
  error_ = false;
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

  cerr << "connected!\n";

  return device_;
}

// endregion

// region hasError レスポンスがエラーかどうかを返す

bool CameraModule::hasError(){
  return error_;
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

// region registerFace 顔を登録するメソッド

vector<char> CameraModule::registerFace(int faceId, int dataId) {

  vector<char> response;

  // 顔を登録するコマンドをセット
  setHeader(&command_);
  command_.push_back(0x10);
  command_.push_back(0x03);
  command_.push_back(0x00);
  // 4バイト中, 下16ビットを使用する.
  // 0xFF(256) という数字がchar型では格納できないため, unsigned charでキャスト.
  unsigned char lsb = faceId & 0xFF;
  unsigned char msb = (faceId >> 8) & 0xFF;
  command_.push_back(lsb);
  command_.push_back(msb);
  command_.push_back(dataId);

  // モジュールにコマンドを送信
  sendCommand();

  // レスポンスを受け取る
  response = getResponse();

  return response;

}

// endregion

// region registerToModuleRom カメラのROMにアルバムを保存

/**
 * registerToModuleRom.
 * <p>
 * アルバム情報をカメラモジュールのROMに保存
 *
 * @return response
 */
vector<char> CameraModule::registerToModuleRom() {

  vector<char> response;

  // アルバム情報をROMに保存するコマンドをセット
  setHeader(&command_);
  command_.push_back(0x22);
  command_.push_back(0x00);
  command_.push_back(0x00);

  // モジュールにコマンド送信
  sendCommand();

  // レスポンスを受け取る
  response = getResponse();

  return response;

}


// endregion

// region getModuleAlbum アルバム情報をホストに吐き出す

vector<char> CameraModule::saveAlbum() {

  vector<char> response;

  // アルバム情報をホストに吐き出すコマンドをセット
  setHeader(&command_);
  command_.push_back(0x20);
  command_.push_back(0x00);
  command_.push_back(0x00);

  // モジュールにコマンド送信
  sendCommand();

  // レスポンスを受け取る
  response = getResponse();

  return response;

}

// endregion

// region loadAlbum アルバム情報をカメラに読み込む

/**
 * loadAlbum.
 * <p>
 * アルバムファイルからデータを読み取って,
 * カメラモジュールにアルバム情報をセットする
 *
 * @return response
 */
vector<char> CameraModule::loadAlbum(){

  vector<char> response;

  // アルバム情報をカメラにロードするコマンドをセット
  setHeader(&command_);
  command_.push_back(0x21);
  command_.push_back(0x04);
  command_.push_back(0x00);

  // ファイルから読み取っていく
  string fileName = "album.txt";
  ifstream ifs(fileName, ios::in);
  string line = "";

  //アルバムデータを1行ずつ取り出して格納
  while( !ifs.eof() ){
    getline(ifs, line);
    if( line.empty() ){
       break;
    }
    int temp = atoi(line.c_str());
    unsigned char datum = temp & 0xFF;
    command_.push_back(datum);
  }

  ifs.close();

  //コマンド送信
  sendCommand();

  delay(1000);

  //レスポンスを得る
  response = getResponse();
  
  return response;

}

// endregion

// region deleteAlbum カメラのアルバム情報を削除する

vector<char> CameraModule::deleteAlbum() {

  vector<char> response;

  // アルバム情報をカメラにロードするコマンドをセット
  setHeader(&command_);
  command_.push_back(0x13);
  command_.push_back(0x00);
  command_.push_back(0x00);

  //コマンド送信
  sendCommand();

  //レスポンスを得る
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
 *
 * @param func
 * @param option1 nullもありえる
 * @param option2 nullもありえる
 * @param response
 */
void CameraModule::responseAnalyze(
    int func,
    char option1,
    char option2,
    vector<char> *response) {

  switch (func) {
    // 物体検出結果を分析
    case (CameraModule::DETECT_RESPONSE) : {
      // region 物体検出結果分析部分

      // エラー検出
      if (hasHeaderErr(response)) {
        error_ = true;
        break;
      }

      // データ長さ取得
      long responseDataSize = getResponseBytes(response);

      faceResults_.clear();
      bodyResults_.clear();
      handResults_.clear();

      // 検出した物体の数を取得
      int bodyNum = response->at(0);
      int handNum = response->at(1);
      int faceNum = response->at(2);
      response->erase(response->begin(), response->begin() + 4);

      // 検出した体情報をbodyResultsに格納
      for (int i = 0; i < bodyNum; i++) {
        Result result;
        result.setPosX(getLongFromResponse(response));
        result.setPosY(getLongFromResponse(response));
        result.setSize(getLongFromResponse(response));
        result.setConfidence(getLongFromResponse(response));
        bodyResults_.push_back(result);
      }

      // 検出した体情報をhandResultsに格納
      for (int i = 0; i < handNum; i++) {
        Result result;
        result.setPosX(getLongFromResponse(response));
        result.setPosY(getLongFromResponse(response));
        result.setSize(getLongFromResponse(response));
        result.setConfidence(getLongFromResponse(response));
        handResults_.push_back(result);
      }

      // 検出した体情報をfaceResultsに格納
      for (int i = 0; i < faceNum; i++) {
        FaceResult result;
        result.setPosX(getLongFromResponse(response));
        result.setPosY(getLongFromResponse(response));
        result.setSize(getLongFromResponse(response));
        result.setConfidence(getLongFromResponse(response));

        // 顔向き推定
        if (option1 & 0b00001000) {
          result.setHorizontalDirection(getLongFromResponse(response));
          result.setVerticalDirection(getLongFromResponse(response));
          result.setInclination(getLongFromResponse(response));
          result.setDirectionConfidence(getLongFromResponse(response));
        }

        // 年齢推定
        if (option1 & 0b00010000) {
          result.setAge((long) response->front());
          response->erase(response->begin());
          result.setAgeConfidence(getLongFromResponse(response));
        }

        // 性別推定
        if (option1 & 0b00100000) {
          result.setSex((long) response->front());
          response->erase(response->begin());
          result.setSexConfidence(getLongFromResponse(response));
        }

        // 視線推定
        if (option1 & 0b01000000) {
          result.setHorizontalSight((long) response->at(0));
          result.setVerticalSight((long) response->at(1));
          response->erase(response->begin(), response->begin() + 2);
        }

        // 目つむり推定
        if (option1 & 0b10000000) {
          result.setEyeCloseLeft(getLongFromResponse(response));
          result.setEyeCloseRight(getLongFromResponse(response));
        }

        // 表情
        if (option2 & 0b00000001) {
          result.setNoneEx((long) response->at(0));
          result.setJoyEx((long) response->at(1));
          result.setSurpriseEx((long) response->at(2));
          result.setAngryEx((long) response->at(3));
          result.setSadEx((long) response->at(4));
          result.setTotalEx((long) response->at(5));
          response->erase(response->begin(), response->begin() + 6);
        }

        // 顔認証
        if (option2 & 0b00000010) {
          result.setFaceId(getLongFromResponse(response));
          result.setFaceScore(getLongFromResponse(response));
        }

        faceResults_.push_back(result);
      }

      break;

      // endregion
    }
    // 顔を認証時のレスポンスを解析
    case (CameraModule::REGISTER_FACE) : {

      // region 顔認証後のレスポンス解析部分

      // エラー検出
      // 2バイト分
      if (hasHeaderErr(response)) {
        error_ = true;
        break;
      }

      // データ長さ取得
      // 4バイト分
      long responseDataSize = getResponseBytes(response);

      // 顔画像データを取得
      vector<char> image;
      long imageWidth = getLongFromResponse(response);
      long imageHeight = getLongFromResponse(response);

      for (long height = 0; height < imageHeight; ++height) {
        for (long width = 0; width < imageWidth; ++width) {
          image.push_back(response->front());
          response->erase(response->begin());
        }
      }
      FaceResult result;
      result.setGrayScale(image);
      result.setImageWidth(imageWidth);
      result.setImageHeight(imageHeight);
      faceResults_.push_back(result);

      break;

      // endregion

    }
    // カメラのアルバム情報をROMに保存
    case (CameraModule::REGISTER_TO_ROM) : {

      // region カメラのアルバム情報をROMに保存時の解析

      // エラー検出
      // 2バイト分
      if (hasHeaderErr(response)) {
        error_ = true;
        break;
      }

      // データ長さ取得
      // 4バイト分
      long responseDataSize = getResponseBytes(response);

      break;

      // endregion

    }
    // カメラのアルバム情報をホストに保存
    case (CameraModule::SAVE_ALBUM) : {

      // region アルバム情報をホストに保存する時の解析

      // エラー検出
      // 2バイト分
      if (hasHeaderErr(response)) {
        error_ = true;
        break;
      }

      //album.txtに アルバムサイズ, CRCの情報を書き込む
      // ファイル出力ストリーム
      string fileName = "album.txt";
      ofstream ofs(fileName, ios::out);
      for(auto itr = response->begin(); itr != response->end(); ++itr){
        int datum = *itr;
        ofs << datum << endl;
      }
        
      ofs.close();

      break;

      // endregion

    }
    // カメラのアルバム情報をファイルから読み込んだ時
    case (CameraModule::LOAD_ALBUM) : {

      // region カメラのアルバム情報をファイルから読み込んだ時の解析

      // エラー検出
      // 2バイト分
      if (hasHeaderErr(response)) {
        error_ = true;
        break;
      }

      // データ長さ取得
      // 4バイト分
      long responseDataSize = getResponseBytes(response);

      // endregion

      break;

    }

    case (CameraModule::DELETE_ALBUM) : {
      
      // region

      // エラー検出
      // 2バイト分
      if (hasHeaderErr(response)) {
        error_ = true;
        break;
      }

      // データ長さ取得
      // 4バイト分
      long responseDataSize = getResponseBytes(response);

      break;

      // endregion  
    }
    default :
      cerr;
  }

  response->clear();

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

  // カメラモジュールのエラーをfalseに
  error_ = false;

  // command_ にある全てのコマンド情報を送信
  for (auto itr = command_.begin(); itr != command_.end(); ++itr) {
    serialPutchar(device_, *itr);
  }

  //レスポンスまで少し時間がかかるため, まつ
  delay(700);

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

// region hasHeaderErr レスポンスのエラーチェック 2バイト分

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
    cerr << "response is empty\n";
    return true;
  }

  // 1バイト目
  if (response->front() != 0xFE) {
    cerr << "header err : " << response->front() << "\n";
    return true;
  }
  response->erase(response->begin());

  // 2バイト目
  if (response->front() != 0x00) {
    cerr << "err code is" << response->front() << "\n";
    return true;
  }
  response->erase(response->begin());

  return false;

}

// endregion

// region getResponseBytes レスポンスのデータ長を取得

/**
 * getResponseBytes.
 * <p>
 * レスポンスのデータ長を返す
 *
 * @param response
 * @return
 */
long CameraModule::getResponseBytes(vector<char> *response) {

  if (response->empty()) {
    return -1;
  }
  long llsb, mlsb, lmsb, mmsb;
  llsb = response->at(0);
  mlsb = response->at(1) << 8;
  lmsb = response->at(2) << 16;
  mmsb = response->at(3) << 24;
  long dataSize = mmsb | lmsb | mlsb | llsb;
  response->erase(response->begin(), response->begin() + 4);

  return dataSize;
}

// endregion

// region getLongFromResponse 2バイト読み込んでlongで返す

/**
 * getLongFromResponse.
 * <p>
 * レスポンス列のうち, LSB|MSB と並んでいるものを整形して数字で返す
 * @param response
 * @return
 */
long CameraModule::getLongFromResponse(vector<char> *response) {

  // 空っぽならエラーで, -1を返す
  if (response->empty()) {
    return -1;
  }

  long lsb, msb;
  lsb = response->front();
  msb = response->at(1);

  // 2バイト分消去
  response->erase(response->begin(), response->begin() + 2);

  // 8ビットMSBをシフトさせて, long型にして返す
  return lsb | msb << 8;

}

// endregion

