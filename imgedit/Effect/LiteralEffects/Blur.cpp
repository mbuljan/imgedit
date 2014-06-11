#include "./Blur.h"
using cv::gpu::GpuMat;
using cv::Size;

class Image;

Blur::Blur() {
  kernel_size_ = 3;
}

Blur::Blur(int kernel_size) {
  kernel_size_ = kernel_size;
}

void Blur::Apply(Image& image) {
  GpuMat& mat = image.get_mat();
  GpuMat tmpMat = mat.clone();
  if (kernel_size_ % 2 == 0) {
    kernel_size_++;
  }
  GaussianBlur(mat, tmpMat, Size(kernel_size_, kernel_size_), 0, 0);
  mat = tmpMat;
}
