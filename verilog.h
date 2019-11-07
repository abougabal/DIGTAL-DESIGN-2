
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
private:
	//vector<int> temp;
	vector <string> checks;
	vector<string> inputs;
	vector <string> outputs;
	vector <string> components_module;
	vector <string> components_name;
	vector <string> wires;
	string module_name;
	ifstream openfile;
	void dividinputs();
	void components(string);
public:
	verilog();
	void files(string);
	void print_inputs();
	void print_outputs();
	void print_wires();
	void print_components_name();
	void print_components_module();
	string getmodulename();
};


