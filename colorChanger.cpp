/*Ahmad Awad
Color Changer
this is the main CPP file*/

#include "PPM.h"

using namespace std;


int main(int argc, char *argv[])
{
	if(argc != 3 ){
		cerr << "USAGE: ./exe text_file Image.ppm\n";
		exit(1);
	}
	
	string txtname = argv[1];
	string imagename = argv[2];
	string output = "out_" + imagename;
	cout << txtname << " " << imagename << " " << output <<"\n";
	
}

