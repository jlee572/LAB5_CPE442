#include <cmath>
#include "grayscale.hpp"

using namespace cv;
using namespace std;

const int Kernelx[3][3] = {{-1, 0, 1},
				{-2, 0, 2},
				{-1, 0, 1}};

const int Kernely[3][3] = {{-1, -2, -2},
				{ 0,  0,  0},
				{ 1,  2,  1}};

void to442_sobel(Mat &input, Mat &output){
	CV_Assert(input.type() == CV_8UC1);

	int Rows = input.rows;
	int Cols = input.cols;
	output.create(Rows - 2, Cols - 2, CV_8UC1);

	for(int i = 1; i < Rows - 1; i++){
		uchar *inputRowM1_p = input.ptr(i-1);
		uchar *inputRow0_p = input.ptr(i);
		uchar *inputRowP1_p = input.ptr(i+1);
		uchar *outputRow_p = output.ptr(i-1);
		for (int j = 1; j < Cols-1; j++){
			 int vGradient = inputRowM1_p[j - 1] * Kernelx[0][0] +
                            inputRowM1_p[j + 1] * Kernelx[0][2] +
                            inputRow0_p[j - 1] * Kernelx[1][0] +
                            inputRow0_p[j + 1] * Kernelx[1][2] +
                            inputRowP1_p[j - 1] * Kernelx[2][0] +
                            inputRowP1_p[j + 1] * Kernelx[2][2];
            		int hGradient = inputRowM1_p[j - 1] * Kernely[0][0] +
                            inputRowM1_p[j    ] * Kernely[0][1] +
                            inputRowM1_p[j + 1] * Kernely[0][2] +
                            inputRowP1_p[j - 1] * Kernely[2][0] +
                            inputRowP1_p[j    ] * Kernely[2][1] +
                            inputRowP1_p[j + 1] * Kernely[2][2];

            int sum = abs(vGradient) + abs(hGradient);
            outputRow_p[j - 1] = (uchar)(sum > 255 ? 255 : sum);
        }
    }
}
