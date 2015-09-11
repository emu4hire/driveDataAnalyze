#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<iostream>
#include<cstdlib>
#include<string>

using namespace cv;
using namespace std;

int main( int argc, char ** argv){

	if(argc < 2){
		cerr<<"Input arguments problem"<<endl;
		exit(1);
	}

	string filename = argv[1];
	
	Mat img = imread(filename.c_str());
	Mat gray, dst;
	
	cvtColor(img, gray, CV_BGR2GRAY);
	
	std::vector<KeyPoint> keypoints;

//	FAST(gray, keypoints, 20, true);
//	Canny(gray ,dst, 50, 200, 3);

	Ptr<ORB> detector = ORB::create(500, 1.2, 8, 30, 0, 2, ORB::HARRIS_SCORE, 31);
	detector->detect(img, keypoints);
	cout<<keypoints.size()<<endl;
	
	drawKeypoints( img, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	imshow("Image", dst);
	waitKey(0);

	return 0;
}
