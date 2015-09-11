#include<fstream>
#include<iostream>
#include<string>
#include<cstdlib>
#include<sstream>

using namespace std;

int main(int argc, char ** argv){

	if(argc < 2){
		cerr<<"Not enough arguments"<<endl;
		exit(1);
	}
	
	string filepath = argv[1];
        size_t found = filepath.find_last_of("/");
        string capturename = filepath.substr(found,filepath.length());
	
	ifstream in;

        string inName = filepath + "/analysis/" + capturename + "_svRequests.dat";
        string outName = filepath + "/analysis/SVImages/"+capturename;
        in.open(inName.c_str());

        int i = 0;
        char buffer[200];
        string buffy_the_vampire_slayer;
        string incr;
        stringstream intstream;
	string command;

        do{
                in.getline(buffer, 200, '\n');
                buffy_the_vampire_slayer = buffer;
                if(buffy_the_vampire_slayer == "")
                        continue;

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

}
