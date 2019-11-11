#ifdef LEFFILE_H
#define LEFFILE_H
#endif
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define MAX 100 
class leffile
{
public:
	ifstream openfile;

	struct start {
		string version;
		string busbitchars;
		string dividerchar;
		string case_sensitive;
		string units;
		string manufacturinggrid;//or float
	};
	struct site {
		string site_name;
		string size[2];//width in size[0] and height in size[1]
		string symmetry;// x or y
		string PAD_CORE;//the class is either pad or core
	};
	struct layer {
		string name;
		string type;//"routing" only
		string direction;//vertical or horizontal
		string pitch;
		string offset;
		string width;
	};
	struct pin {
		string pin_name;
		string direction;//input or output
		string layer_name;
		string rect[4];
	};
	struct macro {
		string name;
		string PAD_CORE;//class
		string origin[2];//origin[0] for x and origin[1] for y
		string size[2];//0 for width and 1 for height
		string site_name;
	};


	vector <site> Site;
	vector <layer> Layer;
	vector <pin> Pin;
	vector<macro> Macro;
	start Start;

	//Counters
	int Site_counter = 0;
	int Layer_counter = 0;
	int Pin_counter = 0;
	int Macro_counter = 0;

	leffile();
	string parsing_lines(string& x); // to parse the lines we get
	void set_start(string x); // reading the first part of the lef file this is the only function we need to use the other are called in this func.
	void set_site(string x, string y); // parsing and reading the site part
	void set_layer(string x, string y); // parsing and reading the layer part
	void set_macro(string x, string y); // parsing and reading the macro part
	void parsying_site(string x, bool y, site&, macro&); //parsing the site
	void set_pin(string x, string y); // setting the pen part and reading it
	void parsying_pin(string x, pin&); // parsying pin vector
};