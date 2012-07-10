////////////////////////////////////////////////////////////////////////
//
// hello-world.cpp
//
// This is a simple, introductory OpenCV program. The program reads an
// image from a file, inverts it, and displays the result. 
//
////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>


int main(int argc, char *argv[]){
	IplImage* img = 0; 
	IplImage* prev_img = 0; 
	int height,width,step,channels;
	uchar *data;
	uchar *pdata;
	int i,j,k,x=0;


	CvCapture* capture = cvCaptureFromCAM(0);

	// create a window
	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
	cvMoveWindow("mainWin", 100, 100);
	cvGrabFrame(capture);
	img=cvRetrieveFrame(capture);           // retrieve the captured frame

	while(1){
		x++;
		if(!cvGrabFrame(capture)){              // capture a frame 
			printf("Could not grab a frame\n\7");
			exit(0);
		}
		prev_img = cvCloneImage(img);
		cvGrabFrame(capture);
		img=cvRetrieveFrame(capture,0);           // retrieve the captured frame

		// get the image data
		height    = img->height;
		width     = img->width;
		step      = img->widthStep;
		channels  = img->nChannels;
		data      = (uchar *)img->imageData;
		pdata     = (uchar *)prev_img->imageData;

		printf("Processing a %dx%d image with %d channels\n",height,width,channels); 


		// invert the image
		for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++){
			//if(i<220 && i>100 && j<500 && j>200){
			// if(data[i*step+j*channels+k]==pdata[i*step+j*channels+k]){
			if(data[i*step+j*channels+k]>180)
				data[i*step+j*channels+k]=0;
			//}
		}
		// show the image
		if(x>2) 
		if(x>2){}
			
		cvShowImage("mainWin", img );
	}
	// wait for a key
	cvWaitKey(0);

	// release the image
	cvReleaseCapture(&capture);

	cvReleaseImage(&img );
	return 0;
}