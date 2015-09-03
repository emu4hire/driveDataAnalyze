#include <iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

int main(int argc, char ** argv){
	
	string filepath;
	string capturename;
	
	if(argc < 2){
		cerr<<"Bad input. Please input a fully qualified filename of a DriveData folder"<<endl;
		exit(1);
	}

	else{
		filepath = argv[1];;
	}

	size_t found = filepath.find_last_of("/");
        capturename = filepath.substr(found, filepath.length());

	ifstream in_response;
	ifstream in_orient;
	ofstream out;

	string infilename_response;
	string infilename_orient;
	string outfilename;
	
	infilename_response = filepath + "/analysis" + capturename + "_snapResponse.dat";
	infilename_orient = filepath +"/analysis" + capturename + "_uniquePose.dat";
	outfilename = filepath + "/analysis"+ capturename + "_snappedPose.dat";

	cout<<"    --IN_REPONSE:"<<infilename_response<<endl;
	cout<<"    --IN_ORIENT:"<<infilename_orient<<endl;
	cout<<"    --OUT:"<<outfilename<<endl;

	in_response.open(infilename_response.c_str());
	in_orient.open(infilename_orient.c_str());
	out.open(outfilename.c_str(), std::fstream::out);

        if(!in_response|| !in_orient || !out){
                cerr<<"FILE COULD NOT BE OPENED"<<endl;
                exit(1);
        }
	

	char buffer[500];
	double lat,lng;
	int orient[9999]; //This is really really bad but I'm too tired to restructure this right now.
	int i =0;

	do{
		in_orient.getline(buffer, 100 ,',');
		in_orient.getline(buffer, 100 ,',');
		in_orient>> orient[i];
		in_orient.getline(buffer, 100, '\n');
		in_orient.ignore();
		i++;
	}while(!(in_orient.eof()));

	int k = i;
	i = 0;
	
	in_response.getline(buffer, 100 ,'\n');
	in_response.getline(buffer, 100 ,'\n');

	do{
		in_response.getline(buffer, 100 ,'\n');
		in_response.getline(buffer, 100 ,'\n');
		in_response.getline(buffer, 100, ':');
		in_response >> lat;
		in_response.getline(buffer, 100 ,'\n');
		in_response.getline(buffer, 100, ':');
		in_response >> lng;
		in_response.getline(buffer, 100 ,'\n');
		in_response.getline(buffer, 100 ,'\n');
		in_response.getline(buffer, 500 ,'}');
		in_response.getline(buffer, 100 ,'\n');

		out<<lat<<" , "<<lng<<" , "<<orient[i]<<endl;
		i++;
	}while(i<k);

	out.close();
	in_response.close();
	in_orient.close();

	return 0;
}
