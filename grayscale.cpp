#include "grayscale.hpp"

#define ITU_R_COEFF 0.2126
#define ITU_G_COEFF 0.7152
#define ITU_B_COEFF 0.0722

using namespace cv;

inline uchar calcG(const uchar* bgrPixel){
	
	return (uchar)(ITU_B_COEFF *(double)bgrPixel[0] + ITU_G_COEFF * (double)bgrPixel[1] + ITU_B_COEFF * (double)bgrPixel[2]);
}

void to442_grayscale(Mat &input, Mat &output){

	CV_Assert(input.type() == CV_8UC3); 

	int channels = input.channels();
	int Rows = input.rows;
	int Cols = input.cols;

	output.create(Rows, Cols, CV_8UC1);
	if (input.isContinuous()&& output.isContinuous()){
		Cols *= Rows;
		Rows = 1;
	}

	for(int i = 0; i <Rows; i++){
		uchar *inputRow = input.ptr(i);
		uchar *outputRow = output.ptr(i);

		for (int j = 0; j <Cols; j++){
			//Do iterating here
			outputRow[j] = calcG(&(inputRow[j * channels]));
		}
	}

}

