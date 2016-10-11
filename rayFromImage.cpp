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
 
	for(int s = 0; s < POSE_RESOLUTION_X; ++s ) {
		for(int t = 0; t < POSE_RESOLUTION_Y; ++t) {

			
			std::vector<Point2f> origin_pose;
  			origin_pose.push_back(Point(s,t)); 
  			std::vector<Point2f> transformed_pose;

  			perspectiveTransform(origin_pose, transformed_pose, pose);
		
			

			for(int x = 0; x < IMAGE_RESOLUTION_X; ++x) {
				for(int y = 0; y < IMAGE_RESOLUTION_Y; ++y) {

					std::vector<Point2f> origin_point;
  					origin_point.push_back(Point(x,y)); 
  					std::vector<Point2f> transformed_point;

  					perspectiveTransform(origin_point, transformed_point, H);

  					std::pair <Point2f, int> poseAndPixel = std::make_pair(transformed_pose, image.at<uchar>(Point(x, y)));

  					currfield->lightfield.push_back(transformed_point, poseAndPixel);

				

				}
			}

		}
	}

}
