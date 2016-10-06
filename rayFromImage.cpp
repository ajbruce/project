#include <stdlib>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "lightfield.h"
#include "calculateHomography.cpp"
#include "poseFromHomography.cpp"

using namespace cv;

/**
 *now we have the pose and the homography of the image, and we
 *have the dimensions of the image so we can put the data
 *from the image into our lightfield structure.
 *
 *
 *
 *
 **/
int rayFromImage(Lightfield * currfield, Mat * image, Mat * H, Mat * pose) {

	int s;
	int t;
	int x;
	int y;
 
	for(s = 0; s < POSE_RESOLUTION_X; ++s ) {
		for(t = 0; t < POSE_RESOLUTION_Y; ++t) {

			Point2f& posePt;
			Point2f& posePt_result;

			

			vector<Point> posePt;
	   		posePt.push_back(Point(s, t));
			warpPerspective()
			

			for(x = 0; x < IMAGE_RESOLUTION_X; ++x) {
				for(y = 0; y < IMAGE_RESOLUTION_Y; ++y) {

					const Point2f& _lu
					const Point2f& _lu_result

					cv::Mat& _transform_matrix)

					cv::Point2f source_points[1];
					cv::Point2f dest_points[1];


					source_points[0] = _lu;
					source_points[1] = _ru;
					source_points[2] = _rd;
					source_points[3] = _ld;

					dest_points[0] = _lu_result;
					dest_points[1] = _ru_result;
					dest_points[2] = _rd_result;
					dest_points[3] = _ld_result;

					cv::Mat dst;
					_transform_matrix = cv::getPerspectiveTransform(source_points, dest_points);
					cv::warpPerspective(_image, dst, H);

				}
			}

		}
	}

}
