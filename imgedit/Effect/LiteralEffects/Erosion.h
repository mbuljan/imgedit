#pragma once
#include "../../opencv_headers.h"
#include "../Effect.h"


class Erosion : public Effect {
 private:
  const int DEFAULT_EROSION_TYPE = cv::MORPH_RECT;
  int erosion_type_;
  int erosion_size_; 
 public:
  explicit Erosion(int erosion_size);
  Erosion(int erosion_size, int erosion_type);
  
  void Apply(Image& image) override; 
  
};
