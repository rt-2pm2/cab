#include <stdio.h>
#include <opencv2/core/mat.hpp>
#include "cab.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
int main() {

	cv::Mat E = 2 * cv::Mat::eye(10, 10, CV_8U);

	std::cout << E << std::endl;
	printf("Instantiate the CAB class\n");
	CAB mycab(3);

	printf("Insert element into the CAB\n");
	mycab.insertData(E);

	DataStorage* pDS = mycab.reserveRecordRD();

	cv::Mat E_ = pDS->getData();
	std::cout << E_ << std::endl;
	cv::imshow("Fetched data", E_);
	cv::waitKey(0);

	return 0;
}
