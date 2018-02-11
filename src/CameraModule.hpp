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
    std::vector<Result> results_;
    static string path_;
    static int baudrate_;
    static int device_;
    static vector<char> command_;
    static int commandBytes_;

    // endregion

    // region public params

public:
    CameraModule(string path, int baudrate);
    int connect();
    
    // region Results accessor

    /**
     * getResults.
     * <p>
     * 検出結果を取得する
     *
     * @return results
     */
    vector<Result> getResults(){
        return this->results_;
    }

    /**
     * setResults.
     * <p>
     * 検出結果をオブジェクトに格納
     *
     * @param results
     */
    void setResults(vector<Result> results){
        this->results_ = results;
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
    string getPath(){
        return path_;
    }
    
    /**
     * setPath.
     * <p>
     * モジュールへのパスをセット
     *
     * @param path
     */
    void setPath(string path){
        this->path_ = path;
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
    int getBaudrate(){
        return this->baudrate_;
    }
    
    /**
     * setBaudrate.
     * <p>
     * ボーレートを設定
     * @param baudrate
     */
    void setBaudrate(int baudrate){
        this->baudrate_ = baudrate;
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
    int getDevice(){
        return this->device_;
    }

    /**
     * setDevice.
     * <p>
     * デバイスIDをセット
     *
     * @param device
     */
    void setDevice(int device){
        this->device_ = device;
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
    int getCommandBytes(){
        return this->commandBytes_;
    }

    /**
     * setCommandBytes.
     * <p>
     * モジュールに送信するコマンドのバイト数をセット
     *
     * @param commandBytes
     */
    void setCommandBytes(int commandBytes){
        this->commandBytes_ = commandBytes;
    }
    // endregion

    // endregion

};


