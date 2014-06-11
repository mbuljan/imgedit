#include "./Resize.h"
using cv::gpu::GpuMat;
using cv::Size;

Resize::Resize(double x_scale, double y_scale) : width_(-1), height_(-1) {
  x_scale_ = x_scale;
  y_scale_ = y_scale;
}

Resize::Resize(int width, int height) {
  width_ = width;
  height_ = height;
}

void Resize::Apply(Image& image) {
  GpuMat& mat = image.get_mat();
  GpuMat tmp = mat.clone();
  if (width_ == -1 && height_ == -1) {
    // slucaj kada su poslani scaleovi u konstruktoru
    width_ = mat.cols * x_scale_ + 1;
    height_ = mat.rows * y_scale_ + 1;
    resize(mat, tmp, Size(width_, height_), x_scale_, y_scale_);
  } else {
    // slucaj kada je poslana nova velicina slike u konstruktoru
    resize(mat, tmp, Size(width_, height_));
  }
  mat = tmp;
}
