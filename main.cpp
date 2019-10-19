#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "grayscale.hpp"
#include "sobel.hpp"

using namespace cv;

//Global vars
Mat topHalfMat_in, bottomHalfMat_in;
Mat topHalfMatOut, bottomHalfMatOut;

int filterTop(void* &topMat){
	//need to recast topMat here
	Mat grayMat;
	to442_grayscale(topMat,grayMat);
	to442_sobel(grayMat,topHalfMatOut);
}

int filterBottom(void* &inputMat){
	//need to recast topMat here
	Mat grayMat;
	to442_grayscale(inputMat,grayMat);
	to442_sobel(grayMat,bottomHalfMatOut);
}

void splitFrame(Mat &currMat){
	//split the image into 2
	int nRows = currMat.rows;
	int nCols = currMat.cols;
	int halfRows = nRows/2;
	//printf("Number of rows: %u\n",nRows);
	//printf("Half number of rows: %u\n",halfRows);
	
	if ((nRows % 2) == 0){
		//even number of rows
		topHalfMat_in.create(halfRows,nCols,CV_8UC3);				
		bottomHalfMat_in.create(halfRows,nCols,CV_8UC3);
	} else {
		//odd number of rows
		topHalfMat_in.create(halfRows,nCols,CV_8UC3);				
		bottomHalfMat_in.create(halfRows+1,nCols,CV_8UC3);
	}

	//assign the appropriate pixels from currFrame to each half Mat
	for (int i=0; i<halfRows; i++){
		//printf("i = %d\n", i);
		Vec3b *currRowTop = currMat.ptr<Vec3b>(i);
		Vec3b *currRowBottom = currMat.ptr<Vec3b>(i+halfRows-1);
		Vec3b *topHalfRow = topHalfMat_in.ptr<Vec3b>(i);
		Vec3b *bottomHalfRow = bottomHalfMat_in.ptr<Vec3b>(i);

		for (int j=0; j<nCols; j++){
			topHalfRow[j] = currRowTop[j];
			bottomHalfRow[j] = currRowBottom[j];
		}
	}
	pthread_t thread1, thread2;

	// threadArgs thread1Args = {topHalfMat_in, topHalfMat_out};
	// threadArgs thread2Args = {bottomHalfMat_in, bottomHalfMat_out};

	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	//int thread1Ret = pthread_create(&thread1, NULL, to442_grayscale, (void *)topHalfMat_in);
	
	int thread1Ret = pthread_create(&thread1, &attr, filterTop, (void *)topHalfMat_in);
	int thread2Ret = pthread_create(&thread2, &attr, filterBottom, (void *)bottomHalfMat_in);
}


int main(int argc, char *argv[]){
	Mat currFrame, outputFrame;

	VideoCapture cap("cartoon.mp4");
	//VideoCapture cap(0);

	while(1) {
		cap.read(currFrame);
		splitFrame(currFrame);
		imshow("Sobel Filter",topHalfMatOut);
		waitKey(1);
	}
	return -1;
}


