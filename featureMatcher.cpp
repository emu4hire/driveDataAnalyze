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

	resize(img1, img1, Size(640, 640), 0, 0, INTER_LINEAR);
	resize(img2, img2, Size(640, 640), 0, 0, INTER_LINEAR);

	Mat gray1, gray2;
	
	std::vector<KeyPoint> kp1, kp2;

	Ptr<ORB> orb = ORB::create(500, 1.2, 8, 30, 0, 2, ORB::HARRIS_SCORE, 31);
	orb->detect(img1, kp1);
	orb->detect(img2, kp2);

	drawKeypoints( img1, kp1, img1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints( img2, kp2, img2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	Mat descript1, descript2;
	orb->compute(img1, kp1, descript1);
	orb->compute(img2, kp2, descript2);
	descript1.convertTo(descript1, CV_32F);
	descript2.convertTo(descript2, CV_32F);

	FlannBasedMatcher matcher ( new flann::KDTreeIndexParams(4), new flann::SearchParams(64));
	std:vector<DMatch> matches;

	matcher.add(descript1);
	matcher.train();
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
	drawMatches(img1, kp1, img2, kp2, matches, imgMatch, 
			Scalar::all(-1), Scalar::all(-1), vector<char>(), 
			DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	if(matches.size() > 0){
		string dst_filepath, dst_filename;
		size_t d = filename.find_last_of('/');
		dst_filepath = filename.substr(0,d);
		dst_filename = filename.substr(d, filename.length());
		d = dst_filepath.find_last_of('/');
		dst_filepath = dst_filepath.substr(0, d);

		dst_filepath = dst_filepath + "/matches";
		string command = "mkdir " + dst_filepath;
		system(command.c_str());
		
		dst_filepath = dst_filepath+dst_filename;
		
		
		imwrite(dst_filepath.c_str(), imgMatch);
	}

	return 0;
}
