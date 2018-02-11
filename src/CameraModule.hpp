#include <iostream>
#include <vector>
#include <string>
#include "Result.hpp"

using namespace std;

/*
カメラモジュール管理クラス
コマンドの送信
応答の受信,管理など
*/
class CameraModule{
    // region private params
private:
    std::vector<Result> results;
    static string path;
    static int baudrate;
    static int device;
    static vector<char> command;
    static int commandBytes;

    // endregion

    // region public params

public:
    CameraModule(string path, int baudrate);
    int connect();
    vector<Result> getResults();
    void setResults(vector<Result> results);
    string getPath();
    void setPath(string path);
    int getBaudrate();
    void setBaudrate(int baudrate);
    int getDevice();
    void setDevice(int device);
    int getCommandBytes();
    void setCommandbytes(int commandBytes);
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
    return this->results;
}

/**
 * setResults.
 * <p>
 * 検出結果をオブジェクトに格納
 *
 * @param results
 */
inline void CameraModule::setResults(vector<Result> results){
    this->results = results;
}

// endregion

// region path accessor

/**
 * getPath.
 * <p>
 * モジュールのパスを取得
 *
 * @return
 */
inline string CameraModule::getPath(){
    return this->path;
}


/**
 * setPath.
 * <p>
 * モジュールへのパスをセット
 *
 * @param path
 */
inline void CameraModule::setPath(string path){
    this->path = path;
}

// endregion

// region baudrate accessor

/**
 * getBoadrate.
 * <p>
 * ボーレートを取得
 *
 * @return boadrate
 */
inline int CameraModule::getBaudrate(){
    return this->baudrate;
}

/**
 * setBaudrate.
 * <p>
 * ボーレートを設定
 * @param baudrate
 */
inline void CameraModule::setBaudrate(int baudrate){
    this->baudrate = baudrate;
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
    return this->device;
}

/**
 * setDevice.
 * <p>
 * デバイスIDをセット
 *
 * @param device
 */
inline void CameraModule::setDevice(int device){
    this->device = device;
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
    return this->commandBytes;
}

/**
 * setCommandBytes.
 * <p>
 * モジュールに送信するコマンドのバイト数をセット
 *
 * @param commandBytes
 */
inline void CameraModule::setCommandBytes(int commandBytes){
    this->commandBytes = commandBytes;
}
// endregion