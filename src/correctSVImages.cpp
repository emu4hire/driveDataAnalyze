#include<iostream>
#include <fstream>
#include<cstdlib>
#include<string>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main (int argc, char ** argv){

	if(argc<2){
		cerr<<"Not enough input"<<endl;
		exit(1);
	}

	string filepath= argv[1];
	string listname= filepath + "img_list.txt";
	ifstream in;
	
	
	in.open(listname.c_str());

	if(!in){
		cerr<<"FILE Opening Problem"<<endl;
		exit(1);
	}

	string s;
	int n;
	vector <string> filenames;

	in>>n;
	while(in){
		in >> s;
		filenames.push_back(s);
	}

	in.close();

	Mat img, compare;

	string fullImgName;
	vector <string> toWrite;
	
	compare = imread("./config/no_imagery.jpg");

	for(int i=0; i< filenames.size()-1; i++){
		fullImgName = filepath+filenames[i];
		img = imread(fullImgName.c_str());
		if(!img.data){
			cerr<<"ERROR READING IMAGE"<<endl;
			continue;
		}
		
		//IF No imagery, delete.
		Scalar ssum = sum(img - compare);
		if((ssum[0] == 0) && (ssum[1] == 0) && (ssum[2]== 0)){
			string command = "rm -f " + fullImgName;
			cerr<<"Deleting " <<filenames[i]<<endl;
			system(command.c_str());
		}
	
		else{
			toWrite.push_back(filenames[i]);
			
		}
		

	

		//IF no line, generate new wget with 90 degree rotation

		//IF tilted left, generate new wget with 30 + degree rotation
	
		//If tilted right, generate new wget with 30 - degree rotation

		//otherwise good, ignore for future sweeps

	}

	ofstream out;
	out.open(listname.c_str());
	out<< toWrite.size();
	for(int i=0; i<toWrite.size(); i++){
		out << endl<<toWrite[i];
	}

	out.close();
	
	//write new file for nth sweep.

	
}
