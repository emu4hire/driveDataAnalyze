#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char ** argv){

	string filepath;
	string output_name;
	int delay=0;

	if(argc > 2){
		filepath= argv[1];
		output_name = argv[2];

	}

	else{
		cerr<<"INPUT ERROR"<<endl;
		cerr<<"Usage pattern: vdmaker [src filepath] [output filepath] [OPTIONS]"<<endl;
		exit(1);
	}

	ifstream img_list;
	string filename;
	filename = filepath + "imgList.txt";
	img_list.open(filename.c_str());

	if(!img_list){
		cerr<<"Error opening input file";
		exit(1);
	}

	Mat img;
	VideoWriter out;
	string writerpath;

	
	in_file >> timestamp;
	temp.str("");
	temp << timestamp;
	time_string = temp.str();
	
	
	img = imread(filepath + "/images" + capture_name + "_IMG_" + time_string 

	writerpath = filepath + capture_name + "_video.avi";
	cerr<<"Opening VideoWriter at"<< writerpath<< endl;
	out.open(writerpath, CV_FOURCC('D', 'I', 'V', 'X') , 5.0, 
		Size( (int) img.cols, (int) img.rows), true);

	while(in_file){
		in_file.getline(dump, 99, '\n');
		in_file >> timestamp;
		temp.str("");
		temp << timestamp;
		time_string = temp.str();
	
		if(timestamp == 0)
			break;
		else{

			//NEED TO INCLUDE /images subdirectory in name, requires parsing out capture name from path.
			img_name = filepath + "/images" + capture_name + "_IMG_" + time_string + ".jpg";
			cerr<<"Writing video from: "<< img_name<<endl;
			img = imread(img_name);
	//		imshow("test", img);
			out.write(img);
		}
		
 
	}
	
	in_file.close();
	out.release();

*/	return 0;	
}

