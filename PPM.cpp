#include "PPM.h"
using namespace std;


PPM::PPM() {
	magicid = "P6";
	nrows = 0;
	ncols = 0;
	maxvalue = 255;
}

PPM::~PPM() { }
// open and read the file 
void PPM::read (const string & fname)
{
	ifstream in;
	in.open(fname.c_str());
	if (in.fail()) 
	{//  if could not open file 
		cerr <<"could not open file\n";   
                exit (1); 
	}  
	RGB Data;
	int i = 0, k ;
	// read formated header file of ppm image
	in >> magicid >> ncols >> nrows >> maxvalue;

	while (in.get() != '\n') { ++k;/* skip */ }
	int npixels = nrows*ncols;
	unsigned char * buf = (unsigned char*) malloc(3*npixels);
	// read the binary pixels data using read
	in.read((char *)buf, 3*npixels);

	unsigned char *bp = buf; 
	while (i < npixels){

		Data.R = *bp++;
		Data.G = *bp++;
		Data.B = *bp++;
		img.push_back (Data);
		i++;
	}    
	in.close();  
}

void PPM::write(const string & fname) 
{
	// open fname: check status
	FILE *fp = fopen(fname.c_str(), "wb");    
	if (!fp) 
	{
		std::cout << "Unable to create file. " << fname << endl;
		return ;
	}

	// write header
	if (!fputs(magicid.c_str(), fp)) 
	{
		std::cout << "Unable to write magic id to file. " << fname << endl;
		return ;
	}
	fputs("\n",fp);
	fprintf(fp, "%d %d\n", ncols, nrows);
	fprintf(fp, "%d\n", maxvalue);

	for (vector<RGB>::iterator it = img.begin(); it != img.end();++it)
	{        
		fprintf(fp,"%c%c%c",(*it).R,(*it).G,(*it).B);		
	}
	fclose(fp);
	return ;
}

void PPM::write(const string & fname, const string & addon) 
{
	// new_fname: image.ppm -> image_addon.ppm
	// call write(new_fname);
	write(addon);
}

void PPM::process(const string &fname)
{
	// for each pixel {
	//   find  closest qcolor 
	//   set pixel color to closest qcolor
	// }
	read_qcolors(fname);

	int x,y,z;
	double s;
	// double distance[10];
	int t =0;
	for (vector <RGB>:: iterator it = img.begin(); it != img.end();++it)
	{
		double dis[10];
		int i =0;
		for (vector <RGB>:: iterator tx = qcolors.begin(); tx != qcolors.end(); ++tx){

			x = ((*it).R - (*tx).R) * ((*it).R- (*tx).R);
			y = ((*it).G - (*tx).G) * ((*it).G- (*tx).G);
			z = ((*it).B - (*tx).B) * ((*it).B- (*tx).B);
			s = x+y+z;

			dis [i] = sqrt(s);
			i++;
		}
		// find the min distance
                double min = dis[0];
		t = 0;
		for ( int r= 0;r < i;r++)
		{ if (min > dis[r])
			{
				min = dis[r];
				t= r; // save the posiont     
			}
		}

		(*it).R = qcolors[t].R;
		(*it).G = qcolors[t].G;
		(*it).B = qcolors[t].B;
	}
}

void PPM::read_qcolors(const string &fname)
{
	//this code should take the numbers from txt file into struct 
	ifstream in;
	in.open(fname.c_str());
	if (in.fail()) 
	{//  if could not open file 
		cerr <<"could not open file\n";   
		exit (1); }
	RGB qc;
	int x,y,z;
	char buffer[30];
	int index = 0;
	while (in >> x) {
		in >> y >> z;
		in.getline (buffer,30);
		qc.R =(unsigned char ) x;
		qc.G = (unsigned char) y;
		qc.B = (unsigned char ) z;
		qc.index = index++;
		qcolors.push_back(qc);
	}

in.close();
}
