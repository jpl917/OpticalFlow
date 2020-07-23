# Optical Flow
We implement two optical flow estimation methods based on OpenCV, including:

1. several functions from OpenCV 
2. open-source optical flow algorithms from [http://people.csail.mit.edu/celiu/OpticalFlow/](http://people.csail.mit.edu/celiu/OpticalFlow/).


## Install and run
```
mkdir build && cd build
cmake ..
make -j4
./Coarse2FineTwoFrames
```


## results
<p align="center">
<img src="imgs/car1.jpg" alt="Sample"  width="210" height="160"><img src="imgs/car1_warp.jpg" alt="Sample"  width="210" height="160"><img src="imgs/car2.jpg" alt="Sample"  width="210" height="160">
<p align="center">
<img src="imgs/mouth1.jpg" alt="Sample"  width="210" height="210"><img src="imgs/mouth1_warp.jpg" alt="Sample"  width="210" height="210"><img src="imgs/mouth2.jpg" alt="Sample"  width="210" height="210">
<p align="center">
<em>From left to right: img1, the warp result from img2 to img1, img2</em>

