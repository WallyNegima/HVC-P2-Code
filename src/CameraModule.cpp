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

int CameraModule::connect(string& path, int baudrate) {

   int device_ = serialOpen(path.c_str(), baudrate);
   if( device_ < 0 ){
       // シリアルオープンに失敗
       cerr << "cannot open " <<  serialPath;
       return -1;
   }

   return device_;
}
// endregion
