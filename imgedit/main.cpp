#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "./Image.h"
#include "./Effect/Effect.h"
#include "./Effect/LiteralEffects/Blur.h"
#include "./Effect/LiteralEffects/Sobel.h"
#include "./Effect/LiteralEffects/Erosion.h"
#include "./Effect/LiteralEffects/Resize.h"

using namespace std;

bool IsOption(const string& msg);
void ApplyEffect(Image& img, Effect* effect);
vector<int> GrabIntegerOptionParams(const vector<string>& option);
bool EvaluateParamCount(const vector<int>& params, const int min_coun, const int max_count);

int main(int argc, char* argv[]) {
  if (cv::gpu::getCudaEnabledDeviceCount() == 0) {
    cout << "No Device with CUDA support has been found :(" << endl;
    return 0;
  }
  
  if (argc < 3) {
    cout <<
      "The correct argument format is: imgedit <image_name> <effect_name> <effect_options>"
         << endl;
    return 0;
  }
  
  string all_args;
  for (int i = 1; i < argc; ++i) {
    string tmp = argv[i];
    all_args += tmp + " ";
  }
  
  const string BLUR_OPTION_NAME = "blur";
  const string EROSION_OPTION_NAME = "erosion";
  const string SOBEL_OPTION_NAME = "sobel";
  const string RESIZE_OPTION_NAME = "resize";
  const string SAVE_OPTION_NAME = "save";
  const string NO_SHOW_OPTION_NAME = "noshow";

  vector<string> tokens;
  boost::split(tokens, all_args, boost::is_any_of("-"));
  string filename = tokens[0];
  if(filename == "") {
    cout << "First argument has to be a file name." << endl;
    return 0;
  }
  filename = filename.substr(0, filename.size() - 1);
  vector<Effect*> desired_effects;
  bool show_image = true;
  bool noshow = false;
  bool save = false;
  string save_file_name;
  string save_format;

  // main loop 
  for (int i = 1; i < tokens.size(); ++i) {
    string option = tokens[i];
    vector<string> option_tokens;
    boost::split(option_tokens, tokens[i], boost::is_any_of(" "));
    string option_name = option_tokens[0];

    // BLUR
    if (option_name == BLUR_OPTION_NAME) {
      const int MIN_BLUR_PARAM_COUNT = 1;
      const int MAX_BLUR_PARAM_COUNT = 1;
      const string BLUR_ERROR_MESSAGE = "Blur only takes one argument -> strength of blur effect";
      vector<int> blur_params;
      blur_params = GrabIntegerOptionParams(option_tokens);
      if (EvaluateParamCount(blur_params, MIN_BLUR_PARAM_COUNT, MAX_BLUR_PARAM_COUNT)) {
        desired_effects.push_back(new Blur(blur_params[0]));
      } else {
        cout << BLUR_ERROR_MESSAGE << endl;
        return 0;
      }
    }
    // EROSION
    else if (option_name == EROSION_OPTION_NAME) {
      const string EROSION_ERROR_MESSAGE =
	"Wrong number of parameters, erosion takes <erosion_size>";
      vector<int> erosion_params;
      erosion_params = GrabIntegerOptionParams(option_tokens);
      int param_count = erosion_params.size();
      
      if (param_count == 1) {
	desired_effects.push_back(new Erosion(erosion_params[0]));
      } else {
        cout << EROSION_ERROR_MESSAGE << endl;
        return 0;
      }
    }
    // SOBEL
    else if (option_name == SOBEL_OPTION_NAME) {
      const int MIN_SOBEL_PARAM_COUNT = 0;
      const int MAX_SOBEL_PARAM_COUNT = 3;
      const string SOBEL_ERROR_MESSAGE = "Sobel has 3 parameters: <image_depth> <dx> <dy>";
      vector<int> sobel_params;
      sobel_params = GrabIntegerOptionParams(option_tokens);
      int param_count = sobel_params.size();
      if (EvaluateParamCount(sobel_params, MIN_SOBEL_PARAM_COUNT, MAX_SOBEL_PARAM_COUNT)) {
        if (param_count == 1 || param_count == 2) {
          cout << SOBEL_ERROR_MESSAGE << endl;
          return 0;
        }
        
        if (param_count == 0) {
          desired_effects.push_back(new Sobel());
        }
        else if (param_count == 3) {
          desired_effects.push_back(new Sobel(sobel_params[0],
                                              sobel_params[1],
                                              sobel_params[2]));
        } else {
          cout << SOBEL_ERROR_MESSAGE << endl;
          return 0;
        }
      }
    }
    // RESIZE
    else if (option_name == RESIZE_OPTION_NAME) {
      const string RESIZE_ERROR_MESSAGE = "Resize takes 2 parameters: <new_width> <new_height>";
      vector<int> resize_params = GrabIntegerOptionParams(option_tokens);
      int param_count = resize_params.size();
     
      if (param_count != 2) {
        cout << RESIZE_ERROR_MESSAGE << endl;
        return 0;
      }
      desired_effects.push_back(new Resize(resize_params[0], resize_params[1]));
    }
    // SAVE
    else if (option_name == SAVE_OPTION_NAME){
      const string SAVE_ERROR_MESSAGE = "Save option takes one parameter: <save_file_name>";
      if(option_tokens.size() != 3){
	cout << SAVE_ERROR_MESSAGE << endl;
	return 0;
      }
      save_file_name = option_tokens[1];
      save = true;
      vector<string> img_name_tokens;
      boost::split(img_name_tokens, save_file_name, boost::is_any_of("."));
  
      if(img_name_tokens.size() == 1 || 
	 (img_name_tokens.size() > 1 && img_name_tokens[img_name_tokens.size() - 1] == "") ){
	cout << 
	  "You must specify the format by writing a file extention: \"example.jpg\"." << endl;
	return 0;
      }
      save_format = img_name_tokens[img_name_tokens.size() - 1];
    }
    //NO SHOW 
    else if(option_name == NO_SHOW_OPTION_NAME){
      noshow = true;
    } else {
      cout << "Option \"" + option_name + "\" not recognized!" << endl;
      return 0;
    }
  }
  
  // handleing image operation after deciding which effects will be used
  Image img(filename);
  for (vector<Effect*>::iterator iter = desired_effects.begin(); iter != desired_effects.end(); ++iter) {
    Effect* effect = *iter;
    ApplyEffect(img, effect);
  }
  if(save) {
    img.Save(save_file_name, save_format);
    cout << "Image saved." << endl;
  }
  if(!noshow){
    img.Show();
    cvWaitKey();
  }
  return 0;
}

bool IsOption (const string& msg) {
  return msg[0] == '-';
}

void ApplyEffect (Image& img, Effect* effect) {
  img.ApplyEffect(effect);
}

vector<int> GrabIntegerOptionParams (const vector<string>& option) {
  vector<int> temp;
  for (int j = 1; j < option.size()-1; ++j) {
    int tmp = atoi(option[j].c_str());
    temp.push_back(tmp);   
  }
  return temp;
}

bool EvaluateParamCount (const vector<int>& params, const int min_count, const int max_count) {
  return params.size() >= min_count && params.size() <= max_count;
}
