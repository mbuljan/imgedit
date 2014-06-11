#include "./Sobel.h"
using cv::gpu::GpuMat;
using cv::Size;
//using namespace cv::gpu;

class Image;

Sobel::Sobel() : dest_img_depth_(DEST_IMG_DEPTH),
                 dx_(DX),
                 dy_(DY) {}

Sobel::Sobel(int dest_img_depth, int dx, int dy) {
  dest_img_depth_ = dest_img_depth;
  dx_ = dx;
  dy_ = dy;
}

void Sobel::Apply(Image& image) {
  GpuMat& mat = image.get_mat();
  GpuMat tmp_mat = mat.clone();
  cv::gpu::Sobel(mat, tmp_mat, dest_img_depth_, dx_, dy_);
  mat = tmp_mat;
}
