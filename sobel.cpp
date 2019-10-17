#include <cmath>
#include "grayscale.hpp"

using namespace cv;
using namespace std;

const int x_matrix[3][3] = {{-1,0,1},
						   {-2,0,2},
						   {-1,0,1}};

const int y_matrix[3][3] = {{-1,-2,-1},
						   {0,0,0},
						   {1,2,1}};

void* to442_sobel(Mat &input, Mat &output){
	CV_Assert(input.type() == CV_8UC1);

	int nRows = input.rows;
	int nCols = input.cols;
	output.create(nRows - 2, nCols - 2, CV_8UC1);

	for(int i = 1; i <  nRows - 1; i++){
		uchar *inputRowM1_p = input.ptr(i-1);
		uchar *inputRow0_p = input.ptr(i);
		uchar *inputRowP1_p = input.ptr(i+1);
		uchar *outputRow_p = output.ptr(i-1);
		for (int j = 1; j < nCols-1; j++){
			int Gx = inputRowM1_p[j-1] * x_matrix[0][0] +
                     inputRow0_p[j-1] * x_matrix[1][0] +
                     inputRowP1_p[j-1] * x_matrix[2][0] +
                     inputRowM1_p[j+1] * x_matrix[0][2] +
                     inputRow0_p[j+1] * x_matrix[1][2] +
                     inputRowP1_p[j+1] * x_matrix[2][2];
            int Gy = inputRowM1_p[j-1] * y_matrix[0][0] +
                     inputRowM1_p[j] * y_matrix[0][1] +
                     inputRowM1_p[j+1] * y_matrix[0][2] +
                     inputRowP1_p[j-1] * y_matrix[2][0] +
                     inputRowP1_p[j] * y_matrix[2][1] +
                     inputRowP1_p[j+1] * y_matrix[2][2];
            int sum = abs(Gx) + abs(Gy);
            outputRow_p[j-1] = (uchar)(sum > 255 ? 255 : sum);
        }
    }

    //return (void *)&output;
}
