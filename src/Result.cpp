#include <iostream.h>

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


// endregion
};

//methods
// region posX getter setter

//X座標のゲッター
public long Result::getPosX(){
	return posX;
}

//X座標のセッター
public void Result::setPoxX(long posX){
	this.posX = posX;
}

// endregion

// region poxY getter setter

//Y座標のゲッター
public long Result::getPosY(){
	return posY;
}

//Y座標のセッター
public void Result::setPosY(long posY){
	this.posY = posY;
}

// endregion

// region size getter setter

//サイズのゲッター
public long Result::getSize(){
	return size;
}

//サイズのセッター
public void Result::setSize(long size){
	this.size = size;
}

// endregion

// region confidence getter setter

//信頼度のゲッター
public void Result::getConfidence(){
	return confidence;
}

//信頼度のセッター
public void Result::setConfidence(long confidence{
		this.confidence = confidence;
		}

		// endregion
