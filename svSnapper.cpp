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
	command = "mkdir " + filepath + "/analysis/SVCenter";
	system(command.c_str());

	ifstream in;

	string inName = filepath + "/analysis/" + capturename + "_svRequests.dat";
	string outName = filepath + "/analysis/SVCenter/afternoon_Center";	
	in.open(inName.c_str());

	int i = 0;
	char buffer[200];
	string buffy_the_vampire_slayer;
	string incr;
	stringstream intstream;

	do{
		in.getline(buffer, 200, '\n');
		buffy_the_vampire_slayer = buffer;

		intstream.str("");
		intstream << i;
		incr = intstream.str();

		command = "wget \"" + buffy_the_vampire_slayer + "\" --output-document=" + outName + "_" + incr + ".jpg";
		cerr<<"BUFFY:"<<buffy_the_vampire_slayer<<endl;
		cerr<<command<<endl;
		system(command.c_str());
	
		i++;

	}while(in);
	in.close();
	
	return 0;
}
