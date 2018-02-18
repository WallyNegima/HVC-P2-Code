class FaceResult : public Result{

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

inline long FaceResult::getHorizontalDirection() {
  return horizontalDirection_;
}

inline void FaceResult::setHorizontalDirection(long hd) {
  horizontalDirection_ = hd;
}

inline long FaceResult::getVerticalDirection() {
  return verticalDirection_;
}

inline void FaceResult::setVerticalDirection(long vd) {
  verticalDirection_ = vd;
}

inline long FaceResult::getInclination() {
  return inclination_;
}

inline void FaceResult::setInclination(long inclination) {
  inclination_ = inclination;
}

inline long FaceResult::getDirectionConfidence() {
  return directionConfidence_;
}

inline void FaceResult::setDirectionConfidence(long confidence) {
  directionConfidence_ = confidence;
}

inline long FaceResult::getAge() {
  return age_;
}

inline void FaceResult::setAge(long age) {
  age_ = age;
}

inline long FaceResult::getSex() {
  return sex_;
}

inline void FaceResult::setSex(long sex) {
  sex_ = sex;
}

inline long FaceResult::getSexConfidence() {
  return sexConfidence_;
}

inline void FaceResult::setSexConfidence(long confidence) {
  sexConfidence_ = confidence;
}

inline long FaceResult::getHorizontalSight() {
  return horizontalSight_;
}

inline void FaceResult::setHorizontalSight(long horizontalSight) {
  horizontalSight_= horizontalSight;
}

inline long FaceResult::getVerticalSight() {
  return verticalSight_;
}

inline void FaceResult::setVerticalSight(long verticalSight) {
  verticalSight_ = verticalSight;
}

inline long FaceResult::getEyeCloseLeft() {
  return eyeCloseLeft_;
}

inline void FaceResult::setEyeCloseLeft(long eyeClose) {
  eyeCloseLeft_ = eyeClose;
}

inline long FaceResult::getEyeCloseRight() {
  return eyeCloseRight_;
}

inline void FaceResult::setEyeCloseRight(long eyeClose) {
  eyeCloseRight_ = eyeClose;
}

inline long FaceResult::getNoneEX() {
  return noneEx_;
}

inline void FaceResult::setNoneEx(long noneEx) {
  noneEx_ = noneEx;
}

inline long FaceResult::getJoyEx() {
  return joyEx_;
}

inline void FaceResult::setJoyEx(long joyEx) {
  joyEx_ = joyEx;
}

inline long FaceResult::getSurpriseEx() {
  return surpriseEx_;
}

inline void FaceResult::setSurpriseEx(long surpriseEx) {
  surpriseEx_ = surpriseEx;
}

inline long FaceResult::getAngryEx() {
  return angryEx_;
}

inline void FaceResult::setAngryEx(long angryEx) {
  angryEx_ = angryEx;
}

inline long FaceResult::getSadEx() {
  return sadEx_;
}

inline void FaceResult::setSadEx(long sadEx) {
  sadEx_ = sadEx;
}

inline long FaceResult::getTotalEx() {
  return totalEx_;
}

inline void FaceResult::setTotalEx(long totalEx) {
  totalEx_ = totalEx;
}

inline long FaceResult::getFaceId() {
  return faceId_;
}

inline void FaceResult::setFaceId(long faceId) {
  faceId_ = faceId;
}

inline long FaceResult::getFaceScore() {
  return faceScore_;
}

inline void FaceResult::setFaceScore(long faceScore) {
  faceScore_ = faceScore;
}

// end region
