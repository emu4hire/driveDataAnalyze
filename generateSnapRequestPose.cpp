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

	cout<<filepath<<endl;
	cout<<capturename<<endl;

	ifstream in;
	ofstream out;

	string infilename;
	string outfilename;
	
	infilename = filepath + "/analysis" + capturename + "_uniquePose.dat";
	outfilename = filepath + "/analysis"+ capturename + "_snapRequest.dat";
	cout<<"IN:"<<infilename<<endl;
	cout<<"OUT:"<<outfilename<<endl;

	in.open(infilename.c_str());
	out.open(outfilename.c_str(), std::fstream::out);

        if(!in || !out){
                cerr<<"FILE COULD NOT BE OPENED"<<endl;
                exit(1);
        }
	

	char buffer[100];
	double lat, lng;

	do{
		in >> lat;
		in.getline(buffer, 100 ,',');
		in >> lng;
		in.getline(buffer, 100, '\n');

		out<<lat<<","<<lng<<"|";
			
	}while(!(in.eof()));

	out.close();
	in.close();

	return 0;
}
