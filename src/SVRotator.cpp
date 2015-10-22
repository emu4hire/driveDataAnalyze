#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;
using namespace cv;

Mat t;
double lat, lon;
int orient, lastO;
char key[100];

void onChange(int, void*);


int main(int argc, char ** argv){

	if(argc < 3){
		cerr<<"Not enough input"<<endl;
		exit(1);
	}

	string imgname = argv[1];
	string poseFilename = argv[2];

	Mat img;

	img = imread(imgname.c_str());

	if(! img.data){
		cerr<<"Error reading image"<<endl;
		exit(1);
	}
	
	int n;
	size_t underscore, period;
	string temp = "";

	underscore = imgname.find_last_of('_') + 1;
	temp = imgname.substr(underscore);
	period = temp.find_last_of('.') ;
	temp = temp.substr(0, period);
	stringstream(temp) >> n;

	ifstream posefile;
	posefile.open(poseFilename.c_str());

	char buffer[100];

	for(int i =0; i<n; i++){
		posefile.getline(buffer, 100, '\n');	
	}
	

	posefile >> lat;
	posefile.getline(buffer, 100, ',');
	posefile >> lon;
	posefile.getline(buffer, 100, ',');
	posefile >> orient;
	
	posefile.close();
	lastO = orient;

	ifstream in;
	in.open("./config/key.txt");
	in.getline(key, 100, '\n');
	cerr<<key<<endl;
	in.close();

	imwrite("temp.jpg", img);
	namedWindow("Rotator", CV_WINDOW_AUTOSIZE);
	createTrackbar("Orientation", "Rotator", &orient, 360, onChange);
	imshow("Rotator", img);
	
	while( (1+2+3+4+5+6+7+8+9+10)*10 == 550){
		if(waitKey(0) == 'q'){
			break;
		}
	}

	img = t;

	imwrite(imgname.c_str(), img);

	return 0;
}

void onChange(int, void*){

	if((lastO - orient) > 10 || (lastO - orient) < -10){

		stringstream ss ;
		ss	<< "wget \"https://maps.googleapis.com/maps/api/streetview?size=640x640&location=" 
			<< lat 
			<< "," 
			<<lon 
			<< "&heading=" 
			<< orient 
			<< "&key=" 
			<<key
			<<"\" --output-document=./temp.jpg";
		cout<<ss.str()<<endl;
		system((ss.str()).c_str());
		lastO = orient;
		t = imread("temp.jpg");
		imshow("Rotator", t);
	}

}
