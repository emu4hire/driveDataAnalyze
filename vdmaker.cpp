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

	string NAME;
	int delay=0;

	if(argc > 1){
		int num = 1;
		
		NAME = argv[num];
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

	cout<<NAME<<" ";

	std::fstream in_file;
	std::string filename;

	filename = NAME +"_ACCEL.log";

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

	
	in_file >> timestamp;
	temp.str("");
	temp << timestamp;
	time_string = temp.str();
	
	
	img = imread(NAME+ "_IMG_" + time_string +".jpg");
	out.open("~/Documents/test.avi", CV_FOURCC('D', 'I', 'V', 'X') , 1.0, 
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
			img_name = NAME + "_IMG_" + time_string + ".jpg";
			cerr<<"Opening image "<<img_name<<endl;
			img = imread(img_name);
			out.write(img);
		}
		
 
	}
	
	in_file.close();

	return 0;	
}
