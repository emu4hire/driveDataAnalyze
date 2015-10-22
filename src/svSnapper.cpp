#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>

using namespace std;

int main(int argc, char ** argv){
	
	string filepath;
	string capturename;
	string command;

	if(argc < 2){
		cerr<<"NOT ENOUGH INPUT"<<endl;
		exit(1);
	}

	filepath = argv[1];

	size_t found = filepath.find_last_of("/");
	capturename = filepath.substr(found,filepath.length());

	cout<<endl<<endl;
	cout<<"  --Beginning process at directory:"<<filepath<<endl;
	cout<<"  --Generating Unique Pose"<<endl;

	command = "./genUniquePose " +filepath;
	system(command.c_str());

	cout<<"  --Requesting Snap for Pose"<<endl;
	command = "./genSnapRequest " + filepath;
	system(command.c_str());
	
	cout<<"  --WGET SnapRequest"<<endl;
	string temp = filepath + "/analysis" + capturename ;
	command = "wget --input-file=" +  temp + "_snapRequest.dat " + "--output-document=" + temp + "_snapResponse.dat";
	system(command.c_str());

	cout<<"  --Parsing SnapResponse"<<endl;
	command = "./parseResponse " + filepath;
	system(command.c_str());

	cout<<"  --Generating Street View Requests"<<endl;
	command = "./genSVRequest " + filepath;
	system(command.c_str());

	cout<<"  --Making Directories for StreetView Requests"<<endl;
	command = "mkdir -p " + filepath + "/analysis/SVImages";
	system(command.c_str());

	command = "./executeSV " +filepath;
	system(command.c_str());

	command = "mkdir -p " + filepath + "/analysis/SVImages/";
	system(command.c_str());
	command = "./genImgList " + filepath + "/analysis/SVImages/";
	system(command.c_str());

	command = "./correctSV " +filepath + "/analysis/SVImages/";
	system(command.c_str());

	ifstream in;
	command = filepath + "/analysis/SVImages/img_list.txt";
	in.open(command.c_str());

	if(!in){
		cerr<<"ERROR opening " <<command<<endl;
		exit(1);
	}
	int n=0;
	in >> n;
	string s[n];
	
	for(int i=0; i<n;i++){
		in >> s[i];
	}
	
	string k, l, x;
	k = filepath + "/analysis/SVImages/";
	l = filepath + "/analysis" + capturename + "_snappedPose.dat";

	for(int i=0; i<n; i++){
		x = k + s[i];
		cerr<<x<<" "<<l<<endl;
		command = "./rotateSV " + x + " " + l;
		system(command.c_str());
		
	}
		
		
	return 0;
}
