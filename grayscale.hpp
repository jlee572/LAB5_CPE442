#ifndef GRAYSCALE_HPP_
#define GRAYSCALE_HPP_

#include <opencv2/core.hpp>

void to442_grayscale(cv::Mat &inputMat, cv::Mat &outputMat);

struct threadArgs {
	cv::Mat in;
	cv::Mat out;
};

#endif 	