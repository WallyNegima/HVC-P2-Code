#include <iostream.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "CameraModule.hpp"
using namespace std::string;

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
    string serialPath = this->path;
    int baudrate = this->baudrate;

    device = serialOpen(serialPath, baudrate);
    if( device < 0 ){
        // シリアルオープンに失敗
        cerr << "cannot open " + serialPath;
        return -1;
    }
    this.setDevice(device);

    return 0;
}

// endregion