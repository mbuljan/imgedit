#pragma once
#include <string>
#include "./Effect/Effect.h"
#include "./opencv_headers.h"
using cv::gpu::GpuMat;
using std::string;

class Effect;

class Image{
 private:
  GpuMat mat_;

 public:
  Image();
  explicit Image(const string& imgname);
  //Image(string imgname, int color_convert);

  void ApplyEffect(Effect* effect);
  void Load(const string& filename);
  void Save(const string& filename, const string& format);
  void Show(const string& title);
  void Show();
  GpuMat& get_mat() { return mat_;}
};
