#include "FlowVisualizer.h"


FlowVisualizer::FlowVisualizer(){
    make_color_wheel();
}

void FlowVisualizer::setcols(int r, int g, int b, int k)
{
    colorwheel[k][0] = r;
    colorwheel[k][1] = g;
    colorwheel[k][2] = b;
}

void FlowVisualizer::make_color_wheel(){
    int RY = 15;
    int YG = 6;
    int GC = 4;
    int CB = 11;
    int BM = 13;
    int MR = 6;
    
    int ncols = RY + YG + GC + CB + BM + MR;
    
    colorwheel = vector<vector<int> >(ncols, vector<int>(3, 0));
    int i;
    int k = 0;
    for (i = 0; i < RY; i++) setcols(255,	       255*i/RY,	 0,	           k++);
    for (i = 0; i < YG; i++) setcols(255-255*i/YG, 255,		     0,	           k++);
    for (i = 0; i < GC; i++) setcols(0,		       255,		     255*i/GC,     k++);
    for (i = 0; i < CB; i++) setcols(0,		       255-255*i/CB, 255,	       k++);
    for (i = 0; i < BM; i++) setcols(255*i/BM,	   0,		     255,	       k++);
    for (i = 0; i < MR; i++) setcols(255,	       0,		     255-255*i/MR, k++);
    return;
}

void FlowVisualizer::flow_to_colors(const cv::Mat& flow){
    cv::Mat flow_image(flow.size(), CV_8UC3, Scalar(0,0,0));
    int ncols = colorwheel.size();
    
    double mag_max = 0, mag_min = 1e4;
    for(int y=0; y<flow.rows; y++){
        for(int x=0; x<flow.cols; x++){
            const Point2f & fxy = flow.at<Point2f>(y,x);
            double mag = sqrt(pow(fxy.x, 2) + pow(fxy.y, 2));
            mag_max = max(mag, mag_max);
            mag_min = min(mag, mag_min);
        }
    }
    cout<<"mag_max:"<<mag_max<<"   mag_min:"<<mag_min<<endl;
    
    double epsilon = 1e-5;
    for(int y=0; y<flow.rows; y++){
        for(int x=0; x<flow.cols; x++){
            const Point2f & fxy = flow.at<Point2f>(y,x);
            double u = fxy.x / (mag_max + epsilon);
            double v = fxy.y / (mag_max + epsilon);
            double rad = sqrt(u*u + v*v);
            double a = atan2(-v, -u)/M_PI;
            
            double fk = (a+1.0) / 2.0*(ncols-1);// [-1,1] => [0,ncols-1]
            int k0 = (int)fk;
            int k1 = (k0 + 1)%ncols;
            int f = fk - k0;
            
            for(int c=0; c<3; c++){
                double col0 = colorwheel[k0][c] / 255.0;
                double col1 = colorwheel[k1][c] / 255.0;
                double col = (1-f)*col0 + f*col1;
                if(rad <= 1){
                    col = 1 - rad * (1-col);
                }else{
                    col = 0.75 * col;   
                }
                //col[idx]  = 1 - rad[idx] * (1-col[idx])
                //col[~idx] = col[~idx] * 0.75   # out of range
                flow_image.at<cv::Vec3b>(y,x)[2-c] = int(255*col);
                
            }
        }
    }
    
    cv::imwrite("OpticalFlow.jpg", flow_image);
}


/*
void FlowVisualizer::visualizeFlow(const cv::Mat& flow){
    // H: 0°～360°，red 0°，green 120°, blue 240°
    // S: 0.0～1.0
    // V: 0.0～1.0
    cv::Mat hsv(flow.size(), CV_8UC3, Scalar(0,0,0));
    
    
    double mag_max = 0, mag_min = 1e4;
    for(int y=0; y<flow.rows; y++){
        for(int x=0; x<flow.cols; x++){
            const Point2f & fxy = flow.at<Point2f>(y,x);
            double mag = sqrt(pow(fxy.x, 2) + pow(fxy.y, 2));
            mag_max = mag > mag_max ? mag : mag_max;
            mag_min = mag < mag_min ? mag : mag_min;
        }
    }
    
    cout<<mag_min<<" "<<mag_max<<endl;
    
    for(int y=0; y<flow.rows; y++){
        for(int x=0; x<flow.cols; x++){
            const Point2f & fxy = flow.at<Point2f>(y,x);
            float ang = atan2(fxy.y, fxy.x);
            float mag = sqrt(pow(fxy.x, 2) + pow(fxy.y,2));
            
            ang = 180 + ang * 180 / M_PI;
            mag = 255 * (mag - mag_min) / (mag_max - mag_min);
            
            hsv.at<cv::Vec3b>(y,x) = cv::Vec3b(ang, mag, 255); //
        }
    }
    
    cv::Mat ret;
    cv::cvtColor(hsv, ret, cv::COLOR_HSV2BGR);
    cv::imwrite("vis1.jpg", ret);
    
    return;
}*/
