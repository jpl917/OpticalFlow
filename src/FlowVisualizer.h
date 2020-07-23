#ifndef FLOW_VISUALIZER_H
#define FLOW_VISUALIZER_H

#include <cmath>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include "opencv2/gpu/gpu.hpp"
using namespace std;
using namespace cv;

using namespace cv::gpu;

//#define PI 3.1415926535

class FlowVisualizer{
public:
    FlowVisualizer();
    ~FlowVisualizer(){}
    
    void flow_to_colors(const cv::Mat& flow);
    
    //void visualizeFlow(const cv::Mat& flow);
    
private:
    void make_color_wheel();
    void setcols(int r, int g, int b, int k);
    
private:
    vector<vector<int> > colorwheel;
    cv::Mat flow;
};


#endif 

