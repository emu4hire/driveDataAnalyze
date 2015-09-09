#include<iostream>
#include<fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char ** argv){

	if(argc < 2){
		cerr<<"Not enough input"<<endl;
		exit(1);
	}

	string filepath= argv[1];

	ifstream in;
	in.open(filepath.c_str());

	if(!in){
		cerr<<"FILE INPUT BAD"<<endl;
		exit(1);
	}

	string s;
	vector <string> filenames;

	while(in){
		in>>s;
		cout<<s<<endl;
	}	

	
	
	return 0;
}
