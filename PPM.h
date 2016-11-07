#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <bitset>
#include <cstdio>
#include <fstream>
#include <math.h>
using namespace std;

typedef unsigned char uchar;
typedef enum { run_process1, run_process2 } pmode_t;

struct RGB { 
  // constructor/destructor 
  // operator< overload
bool operator < (const RGB& rhs) const
{ 
    if ( this->R != rhs.R) return this->R < rhs.R;  
    if ( this->G != rhs.G) return this->G < rhs.G;
    return this->B < rhs.B;	
}

  uchar R, G, B;
int index;
};

class PPM {
  public:
    PPM();
    ~PPM();

	void read(const string &);
    void write(const string &);
	void write(const string &, const string &);
	void process(const string &);
  private:
	string magicid;
    int nrows, ncols;
	int maxvalue;
	vector<RGB> img;
	vector<RGB> qcolors;

	void read_qcolors(const string &);
	
};
