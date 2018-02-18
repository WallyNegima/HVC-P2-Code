#pragma once

#include <string>
#include <vector>
#include "Result.hpp"
#include "FaceResult.hpp"

using namespace std;

/**
カメラモジュール管理クラス
コマンドの送信
応答の受信,管理など
*/
class CameraModule{

  // region private params

private:
  vector<FaceResult> faceResults_;
  vector<Result> handResults_;
  vector<Result> bodyResults_;
  int device_;
  vector<char> command_;
  int commandBytes_;
  void setHeader(vector<char> *command);
  void sendCommand();
  vector<char> getResponse();
  bool hasHeaderErr(vector<char> *response);
  long getResponseBytes(vector<char> *response);
  long getLongFromResponse(vector<char> *response);

  // endregion

  // region public params

public:
  // region static number

  // カメラ情報取得用定数
  static const int CMD_GET_VERSIONS = 0;
  static const int CMD_GET_CAMERA_DIRECTION = 1;
  //物体検出オプション用定数
  static const char DETECT_OPTION1_ALL = 0b11111111;
  static const char DETECT_OPTION2_ALL = 0b00000011;
  static const char IMAGE_OPTION_NON = 0x00;
  static const char IMAGE_OPTION_QVGA = 0x01;
  static const char IMAGE_OPTION_VGA = 0x02;
  //レスポンス解析用定数
  static const int DETECT_RESPONSE = 0;

  // endregion
  CameraModule();
  int connect(string path, int baudrate);
  vector<char> getDeviceInformation(int cmd);
  vector<char> detectObject(char option1, char option2, char imageOption);
  void responseAnalyze(int func, vector<char> *response);
  // accessor
  vector<Result> getBodyResults();
  void setBodyResults(vector<Result> results);
  vector<Result> getHandResults();
  void setHandResults(vector<Result> results);
  vector<Result> getFaceResults();
  void setFaceResults(vector<Result> results);
  int getDevice();
  void setDevice(int device);
  vector<char> getCommand();
  void setCommand(vector<char> command);
  int getCommandBytes();
  void setCommandBytes(int commandBytes);

  // endregion

};

// region BodyResults accessor

/**
 * getResults.
 * <p>
 * 検出結果を取得する
 *
 * @return results
 */
inline vector<Result> CameraModule::getBodyResults(){
  return bodyResults_;
}

/**
 * setResults.
 * <p>
 * 検出結果をオブジェクトに格納
 *
 * @param results
 */
inline void CameraModule::setBodyResults(vector<Result> results){
  bodyResults_ = results;
}

// endregion

// region HandResults accessor

/**
 * getHandResults.
 * <p>
 * 検出結果を取得する
 *
 * @return HandResults
 */
inline vector<Result> CameraModule::getHandResults(){
  return handResults_;
}

/**
 * setResults.
 * <p>
 * 検出結果をオブジェクトに格納
 *
 * @param results
 */
inline void CameraModule::setHandResults(vector<Result> results){
  handResults_ = results;
}

// endregion

// region FaceResults accessor

/**
 * getResults.
 * <p>
 * 検出結果を取得する
 *
 * @return results
 */
inline vector<Result> CameraModule::getFaceResults(){
  return faceResults_;
}

/**
 * setResults.
 * <p>
 * 検出結果をオブジェクトに格納
 *
 * @param results
 */
inline void CameraModule::setFaceResults(vector<Result> results){
  faceResults_ = results;
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
inline vector<char> CameraModule::getCommand(){
  return command_;
}

inline void CameraModule::setCommand(vector<char> command){
  command_ = command;
}

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

