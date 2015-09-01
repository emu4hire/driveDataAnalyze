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
	cerr<<"Opening VideoWriter at ~/Documents/test.avi"<<endl;
	out.open(NAME+ "_video.avi", CV_FOURCC('D', 'I', 'V', 'X') , 1.0, 
		Size( (int) img.rows, (int) img.cols), true);

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
			img_name = NAME + "/images/towork_IMG_" + time_string + ".jpg";
			cerr<<img_name<<endl;
			img = imread(img_name);
	//		imshow("test", img);
			out.write(img);
		}
		
 
	}
	
	in_file.close();
	out.release();

	return 0;	
}
