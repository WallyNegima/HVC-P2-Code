class FaceResult : Result{

  // region private params

private:
  long horizontalDirection_;
  long verticalDirection_;
  long inclination_;
  long directionConfidence_;
  long age_;
  long ageConfidence_;
  long sex_;
  long sexConfidence_;
  long horizontalSight_;
  long verticalSight_;
  long eyeCloseLeft_;
  long eyeCloseRight_;
  // 表情 Rx がついているもの
  long noneEx_;
  long joyEx_;
  long surpriseEx_;
  long angryEx_;
  long sadEx_;
  long totalEx_;
  long faceId_;
  long faceScore_;

  // endregion

  // region public params

public:
  long getHorizontalDirection();
  void setHorizontalDirection(long hd);
  long getVerticalDirection();
  void setVerticalDirection(long vd);
  long getInclination();
  void setInclination(long inclination);
  long getDirectionConfidence();
  void setDirectionConfidence(long confidence);
  long getAge();
  void setAge(long age);
  long getAgeConfidence();
  void setAgeConfidence(long confidence);
  long getSex();
  void setSex(long sex);
  long getSexConfidence();
  void setSexConfidence(long confidence);
  long getHorizontalSight();
  void setHorizontalSight(long horizontalSight);
  long getVerticalSight();
  void setVerticalSight(long verticalSight);
  long getEyeCloseLeft();
  void setEyeCloseLeft(long eyeClose);
  long getEyeCloseRight();
  void setEyeCloseRight(long eyeClose);
  long getNoneEX();
  void setNoneEx(long noneEx);
  long getJoyEx();
  void setJoyEx(long joyEx);
  long getSurpriseEx();
  void setSurpriseEx(long surpriseEx);
  long getAngryEx();
  void setAngryEx(long angryEx);
  long getSadEx();
  void setSadEx(long sadEx);
  long getTotalEx();
  void setTotalEx(long totalEx);
  long getFaceId();
  void setFaceId(long faceId);
  long getFaceScore();
  void setFaceScore(long faceScore);

  // endregion
};

// region all accessor

long FaceResult::getHorizontalDirection() {
  return horizontalDirection_;
}

void FaceResult::setHorizontalDirection(long hd) {
  horizontalDirection_ = hd;
}

long FaceResult::getVerticalDirection() {
  return verticalDirection_;
}

void FaceResult::setVerticalDirection(long vd) {
  verticalDirection_ = vd;
}

long FaceResult::getInclination() {
  return inclination_;
}

void FaceResult::setInclination(long inclination) {
  inclination_ = inclination;
}

long FaceResult::getDirectionConfidence() {
  return directionConfidence_;
}

void FaceResult::setDirectionConfidence(long confidence) {
  directionConfidence_ = confidence;
}

long FaceResult::getAge() {
  return age_;
}

void FaceResult::setAge(long age) {
  age_ = age;
}

long FaceResult::getSex() {
  return sex_;
}

void FaceResult::setSex(long sex) {
  sex_ = sex;
}

long FaceResult::getSexConfidence() {
  return sexConfidence_;
}

void FaceResult::setSexConfidence(long confidence) {
  sexConfidence_ = confidence;
}

long FaceResult::getHorizontalSight() {
  return horizontalSight_;
}

void FaceResult::setHorizontalSight(long horizontalSight) {
  horizontalSight_= horizontalSight;
}

long FaceResult::getVerticalSight() {
  return verticalSight_;
}

void FaceResult::setVertcalSight(long verticalSight) {
  verticalSight_ = verticalSight;
}

long FaceResult::getEyeCloseLeft() {
  return eyeCloseLeft_;
}

void FaceResult::setEyeCloseLeft(long eyeClose) {
  eyeCloseLeft_ = eyeClose;
}

long FaceResult::getEyeCloseRight() {
  return eyeCloseRight_;
}

void FaceResult::setEyeCloseRight(long eyeClose) {
  eyeCloseRight_ = eyeClose;
}

long FaceResult::getNoneEX() {
  return noneEx;
}

void FaceResult::setNoneEx(long noneEx) {
  noneEx_ = noneEx;
}

long FaceResult::getJoyEx() {
  return joyEx_;
}

void FaceResult::setJoyEx(long joyEx) {
  joyEx_ = joyEx;
}

long FaceResult::getSurpriseEx() {
  return surpriseEx_;
}

void FaceResult::setSurpriseEx(long surpriseEx) {
  surpriseEx_ = surpriseEx;
}

long FaceResult::getAngryEx() {
  return angryEx_;
}

void FaceResult::setAngryEx(long angryEx) {
  angryEx_ = angryEx;
}

long FaceResult::getSadEx() {
  return sadEx_;
}

void FaceResult::setSadEx(long sadEx) {
  sadEx_ = sadEx;
}

long FaceResult::getTotalEx() {
  return totalEx_;
}

void FaceResult::setTotalEx(long totalEx) {
  totalEx_ = totalEx;
}

long FaceResult::getFaceId() {
  return faceId_;
}

void FaceResult::setFaceId(long faceId) {
  faceId_ = faceId;
}

long FaceResult::getFaceScore() {
  return faceScore_;
}

void FaceResult::setFaceScore(long faceScore) {
  faceScore_ = faceScore;
}

// end region
