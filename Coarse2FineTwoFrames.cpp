#include <iostream>
#include <string>
#include "project.h"
#include "Image.h"
#include "OpticalFlow.h"
#include "FlowVisualizer.h"
using namespace std;

void Coarse2FineTwoFrames(const DImage& Im1,const DImage& Im2, DImage& warpI2)
{
	// get the parameters
    double alpha = 0.012;
    double ratio = 0.75;
    int minWidth = 20;
    int nOuterFPIterations = 7;
    int nInnerFPIterations = 1;
    int nSORIterations = 30;

	DImage vx,vy;
	OpticalFlow::Coarse2FineFlow(vx,vy,warpI2,Im1,Im2,alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations);
    
    //visualize optical flow
    int w = vx.width();
    int h = vx.height();
    int c = vx.nchannels();
    cout<<w<<" "<<h<<" "<<c<<endl;
    
    cv::Mat flow(h, w, CV_32FC2, cv::Scalar(0,0));
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            flow.at<cv::Point2f>(i,j) = cv::Point2f(vx.pData[i*w+j], vy.pData[i*w+j]);
        }
    }
    
    FlowVisualizer vis;
    vis.flow_to_colors(flow);
}

int main()
{
    std::string filename1 = "../data/mouth1.jpg";
    std::string filename2 = "../data/mouth2.jpg";
    
    int pos0 = filename1.rfind('/');
    int pos1 = filename1.rfind('.');
    std::string savename = filename1.substr(pos0+1, pos1-pos0-1)+"_warp.jpg";
    
	DImage Im1,Im2;
	Im1.imread(filename1.c_str());
	Im2.imread(filename2.c_str());
    
    DImage warpI2;
    Coarse2FineTwoFrames(Im1, Im2, warpI2);
    
    warpI2.imwrite(savename.c_str());
    
    return 0;
}


