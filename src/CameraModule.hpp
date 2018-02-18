#pragma once

#include <string>
#include <vector>
#include "Result.hpp"
#include "SerialUtil.hpp"

using namespace std;

/**
カメラモジュール管理クラス
コマンドの送信
応答の受信,管理など
*/
class CameraModule{

  // region private params

private:
  vector<Result> results_;
  int device_;
  vector<char> command_;
  int commandBytes_;
  void setHeader(vector<char> *command);
  void sendCommand();
  vector<char> getResponse();

  // endregion

  // region public params

public:
  // region static number

  static const int CMD_GET_VERSIONS = 0;
  static const int CMD_GET_CAMERA_DIRECTION = 1;
  static const char DETECT_OPTION1_ALL = 0b11111111;
  static const char DETECT_OPTION2_ALL = 0b00000011;
  static const char IMAGE_OPTION_NON = 0x00;
  static const char IMAGE_OPTION_QVGA = 0x01;
  static const char IMAGE_OPTION_VGA = 0x02;

  // endregion
  CameraModule();
  int connect(string path, int baudrate);
  vector<char> getDeviceInformation(int cmd);
  vector<char> detectObject(char option1, char option2, char imageOption);
  // accessor
  vector<Result> getResults();
  void setResults(vector<Result> results);
  int getDevice();
  void setDevice(int device);
  int getCommandBytes();
  void setCommandBytes(int commandBytes);

  // endregion

};

// region Results accessor

/**
 * getResults.
 * <p>
 * 検出結果を取得する
 *
 * @return results
 */
inline vector<Result> CameraModule::getResults(){
  return results_;
}

/**
 * setResults.
 * <p>
 * 検出結果をオブジェクトに格納
 *
 * @param results
 */
inline void CameraModule::setResults(vector<Result> results){
  results_ = results;
}

// endregion

// region device accessor

/**
 * getDevice.
 * <p>
 * シリアルオープン後のデバイスIDを取得
 *
 * @return device
 */
inline int CameraModule::getDevice(){
  return this->device_;
}

/**
 * setDevice.
 * <p>
 * デバイスIDをセット
 *
 * @param device
 */
inline void CameraModule::setDevice(int device){
  device_ = device;
}

// endregion

// region command accessor

// endregion

// region commandBytes accessor

/**
 * getCommandbytes.
 * <p>
 * モジュールに送信するコマンドのバイト数を取得
 *
 * @return commandBytes
 */
inline int CameraModule::getCommandBytes(){
  return commandBytes_;
}

/**
 * setCommandBytes.
 * <p>
 * モジュールに送信するコマンドのバイト数をセット
 *
 * @param commandBytes
 */
inline void CameraModule::setCommandBytes(int commandBytes){
  commandBytes_ = commandBytes;
}
// endregion

