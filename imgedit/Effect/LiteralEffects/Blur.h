#pragma once
#include "../../opencv_headers.h"
#include "../Effect.h"

class Blur : public Effect {
 private:
  int kernel_size_;
 public:
  Blur();
  explicit Blur(int kernel_size);
  void Apply(Image& image) override;
};
