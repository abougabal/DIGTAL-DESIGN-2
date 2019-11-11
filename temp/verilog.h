#ifdef VERILOG_H
#define VERILOG_H
#endif
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class verilog
{
public:
	//vector<int> temp;
	vector <string> checks; 
	vector<string> inputs; // have the name of the inputs
	vector <string> outputs; // have the name of the outputs
	vector <string> components_module; // modules name
	vector <string> components_name; // the name of each seperate module with it's connected wired
	vector <string> wires; // have the name of the input
	string module_name; // the name of the whole module
	ifstream openfile;
	void dividinputs();
	void components(string);

	verilog();
	void files(string); // this is the only function we need in take the v file name and parse it
	void print_inputs();
	void print_outputs();
	void print_wires();
	void print_components_name();
	void print_components_module();
	string getmodulename();
};