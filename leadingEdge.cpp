//This code compares the prior frame to the current frame. If 
//there is a difference, the pixel is blackened. The issue with
//this method that is picked up a motion, and a uniform moving 
//object is not picked up a movement(a white pice of paper 
//stays white). The noise problem is improved with a gausian 
//blur.

#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion;;
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
using namespace std;
using namespace cv;

bool within(int x,int y,int w){
	//remove w to allow callee to change value. 
	w=2;
	if((x-w)>y && y<(x+w))
		return !false;
	return !true;
}
int main(int argc, char *argv[], char *window_name) {
	VideoCapture captRefrnc(0);
	if ( !captRefrnc.isOpened() ) std::cout << 'Not a camera' << endl;
	int delay;
	Mat frame,prior,toDisp;
	double alpha=2,beta=10;
	const char* WIN_UT = "win";
	namedWindow(WIN_UT, CV_WINDOW_AUTOSIZE );
	cvMoveWindow(WIN_UT, 100, 100);
	captRefrnc >> frame;
	prior = frame.clone();
	toDisp = frame.clone();
	while(1){
		captRefrnc >> frame;
		if(frame.empty()) std::cout << 'Camera failed to capture frame\n';
		for( int y = 0; y < frame.rows; y++ ) for( int x = 0; x < frame.cols; x++ ){// for( int c = 0; c < 3; c++ )
		 	if(within(frame.at<Vec3b>(y,x)[0],prior.at<Vec3b>(y,x)[0],2)){
		 		if(within(frame.at<Vec3b>(y,x)[1],prior.at<Vec3b>(y,x)[1],2)){
		 			if(within(frame.at<Vec3b>(y,x)[2],prior.at<Vec3b>(y,x)[2],2)){
				  		toDisp.at<Vec3b>(y,x)[0]=0; toDisp.at<Vec3b>(y,x)[1]=0; toDisp.at<Vec3b>(y,x)[2]=0;
				  	}
				  }
				}
		}
		imshow( WIN_UT, toDisp);
		prior = frame.clone();
		toDisp = frame.clone();
	}
	cvWaitKey(delay);
}
