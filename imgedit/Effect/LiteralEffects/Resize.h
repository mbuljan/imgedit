#pragma once
#include "../../opencv_headers.h"
#include "../Effect.h"

class Resize : public Effect {
 private:
  double x_scale_;
  double y_scale_;
  int width_;
  int height_;

 public:
  Resize(double x_scale, double y_scale);
  Resize(int width, int height);
  void Apply(Image& image) override;
};
