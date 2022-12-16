#include "ocv.h"
#include <iostream>
#include <vector>
export module opencv_personal;
using namespace cv;
export std::vector<cv::Mat> images;
export cv::Mat single_image;
export cv::Mat openAndRead() {
	cv::Mat img = cv::imread( "D:/O/A/OpenAndEdit/AZGAAR/flags/image.jpeg" );
	cv::namedWindow( "First Open" ,cv::WINDOW_AUTOSIZE);
	imshow( "First Open", img );
	cv::moveWindow( "First Open", 0, 45 );
	cv::waitKey( 0 );
	cv::destroyAllWindows();
	return img;

}
export void showAnImage(cv::Mat img) {
	//cv::Mat img = cv::imread( "D:/O/A/OpenAndEdit/AZGAAR/flags/image.jpeg" );
	cv::namedWindow( "First Open", cv::WINDOW_AUTOSIZE );
	imshow( "First Open", img );
	cv::moveWindow( "First Open", 0, 45 );
	cv::waitKey( 0 );
	cv::destroyAllWindows();
	return;

}
export std::vector<cv::Mat> splitImage( cv::Mat& image, int M, int N )
{
	// All images should be the same size ...
	int width = image.cols / M;
	int height = image.rows / N;
	// ... except for the Mth column and the Nth row
	int width_last_column = width + (image.cols % width);
	int height_last_row = height + (image.rows % height);

	std::vector<cv::Mat> result;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			// Compute the region to crop from
			cv::Rect roi( width * j,
				height * i,
				(j == (M - 1)) ? width_last_column : width,
				(i == (N - 1)) ? height_last_row : height );

			result.push_back( image( roi ) );
		}
	}

	return result;
}
export void dontUseModulesInTheFuture() {
	single_image = openAndRead();
	images = splitImage( single_image, 24, 12 );
	showAnImage( images[0] );
	showAnImage( images[1] );



}