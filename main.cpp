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

void splitFrame(Mat &currMat){
	//split the image into 2
	Mat topHalfMat, bottomHalfMat;
	int nRows = currMat.rows;
	int nCols = currMat.cols;
	int halfRows = nRows/2;
	
	if ((nRows % 2) == 0){
		//even number of rows
		topHalfMat.create(halfRows,nCols,CV_8UC3);				
		bottomHalfMat.create(halfRows,nCols,CV_8UC3);
	} else {
		//odd number of rows
		topHalfMat.create(halfRows,nCols,CV_8UC3);				
		bottomHalfMat.create(halfRows+1,nCols,CV_8UC3);
	}

	
	for (int i=0; i<halfRows; i++){
		Vec3b *currRow = currMat.ptr<Vec3b>(i);
		Vec3b *topHalfRow = topHalfMat.ptr<Vec3b>(i);
		Vec3b *bottomHalfRow = bottomHalfMat.ptr<Vec3b>(i);

		for (int j=0; j<nCols; j++){
			int jColorCell = j*3;

		// 	topHalfRow[jColorCell] = currRow[jColorCell];
		// 	topHalfRow[jColorCell+1] = currRow[jColorCell+1];	
		// 	topHalfRow[jColorCell+2] = currRow[jColorCell+2];
		// }	
		topHalfRow[j] = currRow[j];
		//topHalfRow[j] = currRow[j];	
		//topHalfRow[j] = currRow[j];
		}

	}

	

	//to442_grayscale(currFrame, grayFrame);
	//to442_sobel(grayFrame, sobelFrame);

	imshow("Top Half",topHalfMat);
	waitKey(1);
}


int main(int argc, char *argv[]){
	Mat currFrame, outputFrame;

	VideoCapture cap("cartoon.mp4");
	//VideoCapture cap(0);

	while(1) {
		cap.read(currFrame);
		splitFrame(currFrame);
		//imshow("Sobel Filter",outputFrame);
		//waitKey(1);
	}
	return -1;
}


