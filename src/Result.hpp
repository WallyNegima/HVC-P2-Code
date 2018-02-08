/*
検出結果を格納するクラス
*/
class Result{

    // region params

    private:
	long posX;
	long posY;
	long size;
	long confidence;
    public :
    // accesser
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

//X座標のゲッター
inline long Result::getPosX(){
	return posX;
}

//X座標のセッター
inline void Result::setPoxX(long posX){
	this.posX = posX;
}

// endregion

// region poxY getter setter

//Y座標のゲッター
inline long Result::getPosY(){
	return posY;
}

//Y座標のセッター
inline void Result::setPosY(long posY){
	this.posY = posY;
}

// endregion

// region size getter setter

//サイズのゲッター
inline long Result::getSize(){
	return size;
}

//サイズのセッター
inline void Result::setSize(long size){
	this.size = size;
}

// endregion

// region confidence getter setter

//信頼度のゲッター
inline void Result::getConfidence(){
	return confidence;
}

//信頼度のセッター
inline void Result::setConfidence(long confidence{
    this.confidence = confidence;
}

// endregion