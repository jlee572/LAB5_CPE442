#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "grayscale.hpp"
#include "sobel.hpp"

using namespace cv;


int main(int argc, char *argv[]){

	VideoCapture cap("cartoon.mp4");//open video in directory
	while (true) {
		pthread_t thread1, thread2;
		Mat frame, grayscale, edges; //initialize
		cap.read(frame);
	
	//	pthread_create(&thread1, NULL, split_thread

		if (frame.empty())
			break;

		to442_grayscale(frame, grayscale);
		to442_sobel(grayscale, edges);

		imshow("Bunny", edges); //displays image on screen
		waitKey(1); //delay to keep consistency
	}
}

void split_thread(Mat &input){
//pthread mutex lock
//create two mat objects with half the rows, keep colums same dimensions same
//pthread mutex unlock
        int input.rows = nRows;
	int input.Cols = nCols;
        int halfnRows = nRows/2;
	if (nRows % 2 == 0){
		Mat.create(halfnRows, nCols, CV_8UC3);
                Mat.create(halfnRows, nCols, CV_8UC3);

        for(int i = 0; i <Rows; i++){
                uchar *inputRow = input.ptr(i);
                uchar *outputRow = output.ptr(i);

                for (int j = 0; j <Cols; j++){
                        //Do iterating here
                        outputRow[j] = calcG(&(inputRow[j * channels]));

	} else {
        	Mat.create(nRows, nCols, CV_8UC3)
                Mat.create(halfnRows+1, nCols, CV_8UC3);
	}
}


