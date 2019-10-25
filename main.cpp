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

void filterTop(){
	//need to recast topMat here
	Mat grayMat;
	to442_grayscale(topHalfMat_in,grayMat);
	to442_sobel(grayMat,topHalfMatOut);
}

void filterBottom(){
	//need to recast topMat here
	Mat grayMat;
	to442_grayscale(bottomHalfMat_in,grayMat);
	to442_sobel(grayMat,bottomHalfMatOut);
}

void splitFrame(Mat &currMat){
	//split the image into 2
	int nRows = currMat.rows;
	int nCols = currMat.cols;
	int halfRows = nRows/2;

	if ((nRows % 2) == 0){
		//even number of rows
		topHalfMat_in.create(halfRows,nCols,CV_8UC3);				
		bottomHalfMat_in.create(halfRows,nCols,CV_8UC3);
	} else {
		//odd number of rows
		topHalfMat_in.create(halfRows,nCols,CV_8UC3);				
		bottomHalfMat_in.create(halfRows+1,nCols,CV_8UC3);
	}
	topHalfMatOut.create(topHalfMat_in.rows,topHalfMat_in.cols,CV_8UC3);				
	bottomHalfMatOut.create(topHalfMat_in.rows,topHalfMat_in.cols,CV_8UC3);
	
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
}

void joinFrame(){
        Mat outputMat;
	int nRows = (topHalfMatOut.rows+bottomHalfMatOut.rows);
        int nCols = topHalfMatOut.cols;
        int halfRows = nRows/2;
	outputMat.create(nRows, nCols, CV_8UC1);

	for (int i=0; i<topHalfMatOut.rows; i++){
		uchar *currRowTop = outputMat.ptr<uchar>(i);
		uchar *currRowBottom = outputMat.ptr<uchar>(i+halfRows-1);
		uchar *topHalfRow = topHalfMatOut.ptr<uchar>(i);
                uchar *bottomHalfRow = bottomHalfMatOut.ptr<uchar>(i);

		for(int j = 0; j<nCols; j++){
			currRowTop[j] = topHalfRow[j];
                	currRowBottom[j] = bottomHalfRow[j];
		}
	}

	imshow("Rejoined Sobel Filter", outputMat);

}

	

void* wrapperFunc1(void *foo){
        filterTop();
	//imshow("Sobel Filter Top",topHalfMatOut);
}

void* wrapperFunc2(void *foo){
        filterBottom();
        //imshow("Sobel Filter Bottom",bottomHalfMatOut);
}


int main(int argc, char *argv[]){
	Mat currFrame;

	VideoCapture cap("cartoon.mp4");
        pthread_t thread1, thread2;

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int *foo1;
	int *foo2;
	

	while(1) {
		cap.read(currFrame);
		splitFrame(currFrame);
	        int thread1Ret = pthread_create(&thread1, NULL, wrapperFunc1, foo1);
                int thread2Ret = pthread_create(&thread2, NULL, wrapperFunc2, foo2);

		pthread_join(thread1, NULL);
                pthread_join(thread2, NULL);
		joinFrame();
		waitKey(1);
	}
	
	return -1;
}


