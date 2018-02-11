#include <iostream>
#include <string>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "CameraModule.hpp"
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
CameraModule::CameraModule(string path, int baudrate) {
    this->path = path;
    this->baudrate = baudrate;
}

// endregion

// region connect モジュールにコネクトする

/**
 * connect.
 * <p>
 * モジュールにコネクトする
 * @retun
 */
int CameraModule::connect() {
    string path = this->path;
    char* serialPath = new char[path.size() + 1]; // メモリ確保
    int baudrate = this->baudrate;

    // string -> char* 変換
    std::char_traits<char>::copy(serialPath, path.c_str(), path.size() + 1);

    device = serialOpen(serialPath, baudrate);
    if( device < 0 ){
        // シリアルオープンに失敗
        cerr << "cannot open " + serialPath;
        return -1;
    }
    this.setDevice(device);

    delete[] serialPath; // メモリ解放

    return 0;
}

// endregion