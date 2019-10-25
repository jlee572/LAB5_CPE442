#include "grayscale.hpp"

#define BLUE_COEFF 0.772
#define GREEN_COEFF 0.7152
#define RED_COEFF 0.212

using namespace cv;

uchar greyscale_calc(uchar* color_vals){
	int gray_val = ((double)color_vals[0] * BLUE_COEFF) + ((double)color_vals[1] * RED_COEFF) + ((double)color_vals[2] * BLUE_COEFF);
	if (gray_val > 255){
		return 255;
	} else {
		return gray_val;
	}
	//return (uchar)(((double)color_vals[0] * BLUE_COEFF) + ((double)color_vals[1] * RED_COEFF) + ((double)color_vals[2] * BLUE_COEFF));
}

void to442_grayscale(Mat &inputMat, Mat &outputMat){
	CV_Assert(inputMat.type() == CV_8UC3);

	int numRows = inputMat.rows;
	int numCols = inputMat.cols; 
	outputMat.create(numRows,numCols,CV_8UC1);

	int numChannels = inputMat.channels();

	if (inputMat.isContinuous()&& outputMat.isContinuous()){
			numCols *= numRows;
			numRows = 1;
	}
	int i, j;
	#pragma omp simd collapse(2)
	for (i=0;i<numRows;i++){
		for (j=0;j<numCols;j++){
			outputMat.ptr(i)[j] = greyscale_calc(&(inputMat.ptr(i)[j*numChannels]));
		}
	}
}
