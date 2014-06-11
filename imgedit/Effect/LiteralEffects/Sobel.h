#pragma once
#include "../../opencv_headers.h"
#include "../Effect.h"

class Sobel : public Effect {
private:
  const int DEST_IMG_DEPTH = CV_8U;
  const int DX = 1;
  const int DY = 1;
  int dest_img_depth_;
  int dx_;
  int dy_;
public:
  Sobel();
  Sobel(int dest_img_depth, int dx, int dy);
  void Apply(Image& image) override;
};
