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

	if(argc < 3){
		cerr<<"Input arguments problem"<<endl;
		exit(1);
	}

	string filename = argv[1];
	Mat img1 = imread(filename.c_str());
	filename = argv[2];
	Mat img2 = imread(filename.c_str());

	Mat gray1, gray2;
	resize(img1, img1, Size(0, 0), 0.25, 0.25, INTER_LINEAR);
	
	
	std::vector<KeyPoint> kp1, kp2;

//	FAST(gray, keypoints, 20, true);
//	Canny(gray ,dst, 50, 200, 3);

	Ptr<ORB> orb = ORB::create(500, 1.2, 8, 30, 0, 2, ORB::HARRIS_SCORE, 31);
	orb->detect(img1, kp1);
	
	orb->detect(img2, kp2);

	drawKeypoints( img1, kp1, img1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints( img2, kp2, img2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	Mat descript1, descript2;
	orb->compute(img1, kp1, descript1);
	orb->compute(img2, kp2, descript2);

	BFMatcher matcher;
	std:vector<DMatch> matches;
	matcher.match( descript1, descript2, matches);
	
	double max_dist = 0;
	double min_dist = 100;

	for( int i=0; i<descript1.rows; i++){
		double dist = matches[i].distance;
		if( dist < min_dist) min_dist = dist;
		if(dist > max_dist) max_dist = dist;
	}

	std::vector<DMatch> good_matches;
	for(int i=0; i<descript1.rows; i++){
		if( matches[i].distance <= max(2*min_dist, 0.02)){
			good_matches.push_back( matches[i]); 
		}
	}

	Mat imgMatch;
	drawMatches(img1, kp1, img2, kp2, good_matches, imgMatch, 
			Scalar::all(-1), Scalar::all(-1), vector<char>(), 
			DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


	imshow("MATCHES", imgMatch);
	waitKey(0);

	return 0;
}
