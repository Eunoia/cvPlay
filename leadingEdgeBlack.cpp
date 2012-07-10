#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion;;
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
using namespace std;
using namespace cv;
//=saturate_cast<uchar>( alpha*( frame.at<Vec3b>(y,x)[c] ) + beta );
bool within(int x,int y,int w){
	//30,34, 10
	w=2;
	if((x-w)>y && y<(x+w))
		return !false;
	return !true;
}
int main(int argc, char *argv[], char *window_name) {
	VideoCapture captRefrnc(0);
	if ( !captRefrnc.isOpened() ) std::cout << 'fail0' << endl;
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
		if(frame.empty()) std::cout << 'fail1\n';
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
// if (c == 27) break;
}
