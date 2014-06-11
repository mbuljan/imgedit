#include "./Image.h"
using cv::Mat;

Image::Image() {}

Image::Image(const string& imgname) {
  Load(imgname);
}

void Image::Load(const string& filename) {
  Mat tmp = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
  if(tmp.data == NULL){
    std::cout << "Cannot find " + filename << std::endl;
    exit(0);
  }
  Mat dst = tmp.clone();
  cv::cvtColor(tmp, dst, cv::COLOR_BGR2BGRA);
  mat_.upload(dst);
}

void Image::Save(const string& filename, const string& format) {
  const string JPG_FORMAT = "jpg";
  const string JPEG_FORMAT = "jpeg";
  const string PNG_FORMAT = "png";
  const int COMPRESSION_PARAM = 9;

  std::vector<int> compression_params;
  if(format == JPG_FORMAT || format == JPEG_FORMAT){
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
  }
  else if(format == PNG_FORMAT){
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  } else {
    std::cout << "Cannot save, format not supported!" << std::endl;
  }
  compression_params.push_back(COMPRESSION_PARAM);
  Mat tmp;
  mat_.download(tmp);
  cv::imwrite(filename, tmp, compression_params);
}

void Image::ApplyEffect(Effect* effect) {
  effect->Apply(*this);
}

void Image::Show(const string& title) {
  Mat tmp;
  mat_.download(tmp);
  imshow(title, tmp);
}

void Image::Show() {
  Show("");
}
