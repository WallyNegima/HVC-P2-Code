#include <iostream>

/**
検出結果を格納するクラス
*/
class Result{

    // region private params

private:
	long posX;
	long posY;
	long size;
	long confidence;

    // endregion

    // region public params
public :
	long getPosX();
    void setPosX(long posX);
    long getPosY();
    void setPosY(long posY);
    long getSize();
    void setSize(long size);
    long getConfidence();
    void setConfidence(long confidence);

    // endregion

};

// region posX getter setter

/**
 * getPosX.
 * <p>
 * 検出結果のX座標を取得
 * @return posX
 */
inline long Result::getPosX(){
	return this->posX;
}

/**
 * setPosX.
 * <p>
 * 取得した検出結果をセット
 * @param posX
 */
inline void Result::setPoxX(long posX){
	this->posX = posX;
}

// endregion

// region poxY getter setter

/**
 * getPosY.
 * <p>
 * 検出結果のY座標を取得
 * @return posY
 */
inline long Result::getPosY(){
	return this->posY;
}

/**
 * setPosY.
 * <p>
 * 検出結果のY座標をセット
 * @param posY
 */
inline void Result::setPosY(long posY){
	this->posY = posY;
}

// endregion

// region size getter setter

/**
 * getSize.
 * <p>
 * 検出結果のサイズを取得
 * バイト数ではない
 * 正方形で検出されるため, その一辺のピクセル数
 * @return
 */
inline long Result::getSize(){
	return this->size;
}

/**
 * setSize.
 * <p>
 * 検出結果のサイズをセット
 * @param size
 */
inline void Result::setSize(long size){
	this->size = size;
}

// endregion

// region confidence getter setter

/**
 * getConfidence.
 * <p>
 * 検出した物体の信頼度を取得
 * @return confidence
 */
inline long Result::getConfidence(){
	return this->confidence;
}

/**
 * setConfidence.
 * <p>
 * 検出した物体の信頼度をオブジェクトにセット
 * @param confidence
 */
inline void Result::setConfidence(long confidence){
    this->confidence = confidence;
}

// endregion