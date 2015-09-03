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
	string capture_name;
	int delay=0;

	if(argc > 1){
		int num = 1;
		
		filepath = argv[num];
		num++;
		while(num < argc){
			String input = argv[num];	

			if( input == "-d" || input == "-D"){
				num ++;
				stringstream(argv[num]) >> delay;
			}
			num++;
		}
	}

	else{
		cerr<<"NO INPUT SCRUB"<<endl;
		exit(1);
	}


	size_t found = filepath.find_last_of("/");
	capture_name = filepath.substr(found, filepath.length());

	cout<<filepath<<endl<<capture_name<<endl;

	std::fstream in_file;
	std::string filename;

	filename = filepath + capture_name + "_ACCEL.log";

	in_file.open(filename.c_str());

	if(!in_file){
		cerr<<"FILE FUCKUP"<<endl;
		exit(1);
	}

	int timestamp;
	string time_string;
	char dump[100];
	stringstream temp;
	string img_name;

	Mat img;
	VideoWriter out;
	string writerpath;

	
	in_file >> timestamp;
	temp.str("");
	temp << timestamp;
	time_string = temp.str();
	
	
	img = imread(filepath + "/images" + capture_name + "_IMG_" + time_string +".jpg");

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

	return 0;	
}
