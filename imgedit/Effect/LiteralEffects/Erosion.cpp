 #include "Erosion.h"
using cv::gpu::GpuMat;
using cv::Mat;
using cv::Point;
using cv::Size;


Erosion::Erosion(int erosion_size) : erosion_type_(DEFAULT_EROSION_TYPE){
erosion_size_ = erosion_size;
}

Erosion::Erosion(int erosion_size, int erosion_type){
erosion_size_ = erosion_size;
erosion_type_ = erosion_type;
}

void Erosion::Apply(Image& image){
GpuMat& mat = image.get_mat();
GpuMat tmp = mat.clone();
Mat filter = getStructuringElement( erosion_type_,
                                       Size( 2*erosion_size_ + 1, 2*erosion_size_ + 1 ),
                                       Point( erosion_size_, erosion_size_ ) );
cv::gpu::erode(mat, tmp, filter);
mat = tmp;
}
