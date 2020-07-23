#include <iostream>
#include <cstdlib>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include "opencv2/gpu/gpu.hpp"

#include "FlowVisualizer.h"
using namespace std;
using namespace cv;
using namespace cv::gpu;

// void drawFlow(const cv::Mat& flow, cv::Mat& flowMap, int step){
//     for(int y=0; y<flowMap.rows; y+=step){
//         for(int x=0; x<flowMap.cols; x+=step){
//             const Point2f & fxy = flow.at<Point2f>(y,x);
//             cv:line(flowMap, Point(x,y), Point(cvRound(x-fxy.x), cvRound(y-fxy.y)), cv::Scalar(0,0,255));
//             cv::circle(flowMap, Point(x,y), 2,  cv::Scalar(0,255,0), -1);
//         }
//     }
//     return;
// }

cv::Mat warpFromFlow(cv::Mat& img1, const cv::Mat& img2, const cv::Mat& flow)
{
    cv::Mat ret(img1.size(), CV_8UC3, Scalar(0,0,0));
    for(int y=0; y<img1.rows; y++){
        for(int x=0; x<img1.cols; x++){
            const Point2f & fxy = flow.at<Point2f>(y,x);            
            int new_x = cvRound(x + fxy.x);
            int new_y = cvRound(y + fxy.y);
            
            ret.at<cv::Vec3b>(y,x) = img2.at<cv::Vec3b>(new_y, new_x);
        }
    }
    return ret;
}


int main()
{
    cv::Mat img1 = cv::imread("../data/car1.jpg");
    cv::Mat img2 = cv::imread("../data/car2.jpg");
    
    cv::Mat img1_gray, img2_gray;
    cv::cvtColor(img1, img1_gray, CV_BGR2GRAY);
    cv::cvtColor(img2, img2_gray, CV_BGR2GRAY);
    
    cv::Mat flow;
    /* 
    * void calcOpticalFlowFarneback( InputArray prev, InputArray next, InputOutputArray flow,
    *                                             double pyr_scale, int levels, int winsize,
    *                                             int iterations, int poly_n, double poly_sigma,
    *                                             int flags );
    */
    cv::calcOpticalFlowFarneback(img1_gray, img2_gray, flow, 0.702, 5, 10, 2, 7, 1.5, cv::OPTFLOW_FARNEBACK_GAUSSIAN);  
    
    
    FlowVisualizer vis;
    vis.flow_to_colors(flow);
    
    
    cv::Mat ret = warpFromFlow(img1, img2, flow);
    cv::imwrite("WarpResult.jpg", ret);
    
    return 0;
}


// opencv gpu version
// void estimateOpticalFlow_gpu()
// {
//     cv::Mat img1 = cv::imread("../data/car1.jpg");
//     cv::Mat img2 = cv::imread("../data/car2.jpg");
//     
//     cv::Mat img1_gray, img2_gray;
//     cv::cvtColor(img1, img1_gray, CV_BGR2GRAY);
//     cv::cvtColor(img2, img2_gray, CV_BGR2GRAY);
//     
//     GpuMat frame0, frame1, flow_u, flow_v;
//     setDevice(0);
//     
//     FarnebackOpticalFlow alg_farn;
// 	OpticalFlowDual_TVL1_GPU alg_tvl1;
// 	BroxOpticalFlow alg_brox(0.197f, 50.0f, 0.8f, 10, 77, 10);
// 
//     frame0.upload(img1_gray);
//     frame1.upload(img2_gray);
//     
//     int type = 0;
//     switch(type){
//         case 0:
//             alg_farn(frame0, frame1, flow_u, flow_v);
//             break;
//         case 1:
//             alg_tvl1(frame0, frame1, flow_u, flow_v);
//             break;
//         case 2:
//             GpuMat d_frame0, d_frame1;
//             frame0.convertTo(d_frame0, CV_32F, 1.0/255);
//             frame1.convertTo(d_frame1, CV_32F, 1.0/255);
//             alg_brox(d_frame0, d_frame1, flow_u, flow_v);
//             break;
//     }
// 
//     
//     //save
//     cv::Mat flows[2];
//     flow_u.download(flows[0]);
//     flow_v.download(flows[1]);
//     
//     cv::Mat imgX(flows[0].size(), CV_8UC1);
//     cv::Mat imgY(flows[0].size(), CV_8UC1);
//     
//     return;
// }
