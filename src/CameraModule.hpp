#include <iostream>
#include <vevtor>
#include <string>
#include "Result.hpp"
using namespace std::vector;
using namespace std::string;

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
inline std::vector<Result> getResults(){
    return results;
}

/**
 * setResults.
 * <p>
 * 検出結果をオブジェクトに格納
 *
 * @param results
 */
inline void setResults(std::vector<Result> results){
    this.results = results;
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
inline string getPath(){
    return path;
}


/**
 * setPath.
 * <p>
 * モジュールへのパスをセット
 *
 * @param path
 */
inline void setPath(string path){
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
inline int getBaudrate(){
    return baudrate;
}

/**
 * setBaudrate.
 * <p>
 * ボーレートを設定
 * @param baudrate
 */
inline void setBaudrate(int baudrate){
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
inline int getDevice(){
    return device;
}

/**
 * setDevice.
 * <p>
 * デバイスIDをセット
 *
 * @param device
 */
inline void setDevice(int device){
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
inline int getCommandBytes(){
    return commandBytes;
}

/**
 * setCommandBytes.
 * <p>
 * モジュールに送信するコマンドのバイト数をセット
 *
 * @param commandBytes
 */
inline void setCommandBytes(int commandBytes){
    this->commandBytes = commandBytes;
}
// endregion