#pragma once
#include <iostream>
#include "../opencv_headers.h"
#include "../Image.h"


class Image;

class Effect{
 public:
  Effect();
  virtual void Apply(Image& image) = 0;
};
