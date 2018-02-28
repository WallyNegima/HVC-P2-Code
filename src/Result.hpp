#pragma once

/**
検出結果を格納するクラス
*/
class Result{

    // region private params

private:
	long posX_;
	long posY_;
	long size_;
	long confidence_;

    // endregion

    // region public params
public :
  Result();
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
	return this->posX_;
}

/**
 * setPosX.
 * <p>
 * 取得した検出結果をセット
 * @param posX
 */
inline void Result::setPosX(long posX){
	this->posX_ = posX;
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
	return this->posY_;
}

/**
 * setPosY.
 * <p>
 * 検出結果のY座標をセット
 * @param posY
 */
inline void Result::setPosY(long posY){
	this->posY_ = posY;
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
	return this->size_;
}

/**
 * setSize.
 * <p>
 * 検出結果のサイズをセット
 * @param size
 */
inline void Result::setSize(long size){
	this->size_ = size;
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
	return this->confidence_;
}

/**
 * setConfidence.
 * <p>
 * 検出した物体の信頼度をオブジェクトにセット
 * @param confidence
 */
inline void Result::setConfidence(long confidence){
    this->confidence_ = confidence;
}

// endregion



