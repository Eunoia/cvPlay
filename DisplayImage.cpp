#include <iostream> // for standard I/O
#include <cmath> // for math
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
	w=1;
	if((x-w)>y && y<(x+w))
		return !false;
	return !true;
}
int main(int argc, char *argv[], char *window_name) {
	//Mat history[1000];
	VideoCapture captRefrnc(0);
	if ( !captRefrnc.isOpened() ) return -1;
	Mat frame,prior,toDisp,unMol,bg;
	const char* WIN_UT = "win";
	namedWindow(WIN_UT, CV_WINDOW_AUTOSIZE );
	cvMoveWindow(WIN_UT, 100, 100);
	const char* filename = "bg.png";
	bg = imread(filename,0);
	captRefrnc >> frame;
	unMol = frame.clone();
	cvtColor(frame, frame, CV_BGR2GRAY);
	// for( int y = 0; y < frame.rows; y++ ) for( int x = 0; x < frame.cols; x++ )
	// 	frame.at<Vec3b>(y,x)[0] = (int)frame.at<Vec3b>(y,x)[0]/2;
	GaussianBlur(frame,frame,cv::Size(115,15),10.5);

	prior = frame.clone();
	toDisp = frame.clone();

	while(1){
		captRefrnc >> frame;
		cvtColor(frame, frame, CV_BGR2GRAY);
		unMol = frame.clone();

		// for( int y = 0; y < frame.rows; y++ ) for( int x = 0; x < frame.cols; x++ )
		// 	frame.at<Vec3b>(y,x)[0] = (int)frame.at<Vec3b>(y,x)[0]/10;
		GaussianBlur(frame,frame,cv::Size(115,15),10.5);
		//Sobel(frame,frame,CV_8U,1,0,3,0.4,128);
		threshold(frame, frame,
                   130, 255, cv::THRESH_BINARY);
		// for( int y = 0; y < frame.rows; y++ ) for( int x = 0; x < frame.cols; x++ )
		//  	if(frame.at<Vec3b>(y,x)[0]==prior.at<Vec3b>(y,x)[0])
		//   		toDisp.at<Vec3b>(y,x)[0]=255;
		//   	else
		//  		toDisp.at<Vec3b>(y,x)[0]=unMol.at<Vec3b>(y,x)[0];
		for( int y = 0; y < frame.rows; y++ ) for( int x = 0; x < frame.cols; x++ ){
			if(frame.at<Vec3b>(y,x)[0]==0)
				frame.at<Vec3b>(y,x)[0]=unMol.at<Vec3b>(y,x)[0];
			else
				frame.at<Vec3b>(y,x)[0]=bg.at<Vec3b>(y,x)[0];
		}
		imshow( WIN_UT, frame);
		prior = frame.clone();
		toDisp = frame.clone();
		//history[x]= frame;
	}
	cvWaitKey(0);
}
