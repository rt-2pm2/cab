#include <stdio.h>
#include <opencv2/core/mat.hpp>
#include "cab.hpp"

int main() {

	cv::Mat E = cv::Mat::eye(10, 10, CV_8U);

	printf("Instantiate the CAB class\n");
	CAB mycab(3);

	return 0;
}
