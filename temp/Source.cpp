#include"leffile.h"
#include"verilog.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<time.h>
#include<stdlib.h>
using namespace std;


leffile lef;
verilog v;
ofstream write;
vector <string> comp_temp;
void print_nets()
{
	int temp_wire=0;
	string temp_string_wire;
	write << "NETS " << v.wires.size() << " ;" << endl;
	for (int i = 0; i < v.wires.size(); i++)
	{
		temp_string_wire = v.wires[i].substr(0, v.wires[i].find(';'));
		write << "- " << temp_string_wire;
		
		temp_wire = 0;
		
		for (int j = 0; j < v.components_name.size(); j++)
		{
			
			if (v.components_name[j].find(temp_string_wire) != string::npos)
			{
				write << " (" << comp_temp[temp_wire] << " " << v.components_name[j].substr(1, v.components_name[j].find('(')-1) << ")";
			}
			if ((v.components_name[j].find(',') == string::npos)&&((v.components_name[j].find('(') != string::npos)))
				temp_wire++;
			
		}
		for (int k = 0; k < v.inputs.size(); k++)
		{
			if (temp_string_wire == v.inputs[k].substr(0, v.inputs[k].find(";")))
				write << " (" << "PIN " << temp_string_wire << " )";
		}
		for (int k = 0; k < v.outputs.size(); k++)
		{
			if (temp_string_wire == v.outputs[k].substr(0, v.inputs[k].find(";")))
				write << " (" << "PIN " << temp_string_wire << ")";
		}
		write <<";" << endl;
	}
	write << " END nets" << endl;
}
void write_header() {
	write << "VERSION " << lef.Start.version << " ;" << endl;
	write << "DIVIDERCHARS " << lef.Start.dividerchar << " ;" << endl;
	write << "DESIGN " << v.module_name << " ;" << endl;
	write << "UNITS " << lef.Start.units << " ;" << endl;
	//write << "DIEAREA " << lef.Start.version << " ;" << endl;
}
void getcomponentname()
{
	for (int i = 0; i < v.components_name.size(); i++)
	{
		if (v.components_name[i].find('.')==string::npos)
			comp_temp.push_back(v.components_name[i]);
	}
	for (int i = 0; i < comp_temp.size(); i++)
	{
		cout << comp_temp[i] << endl;
	}
}


void write_component() {
	srand(time(NULL));
	int random = rand() % 1;
	string orient;

	write << "COMPONENTS " << v.components_module.size() << " ;" << endl;
	for (int i = 0; i < v.components_module.size(); i++) {
		if (lef.Site[i].symmetry[0] == 'X')
			if (random == 1) orient = " N";
			else orient = " FS";
		else
			if (random == 1) orient = " FN";
			else orient = " S";

		write << " - " << comp_temp[i] << " " << v.components_module[i] << endl;
		write << "  + FIXED ( " << "..." << " ) " << orient << " ;" << endl;//issue here
	}
	write << "END COMPONENTS" << endl;
}

void write_pins() {

	write << "PINS " << v.inputs.size()+v.outputs.size() << " ;" << endl;
	for (int i = 0; i < v.inputs.size(); i++) {
		write << " - " << v.inputs[i] << " + NET " << v.components_name[i] << endl;
		write << " + DIRECTION " << "INPUT" << endl;
		write << " + FIEXED" << endl;
		write << " + LAYER " << lef.Pin[i].layer_name << " ( " << lef.Pin[i].rect[0] << " " << lef.Pin[i].rect[1];
		write << " ) ( " << lef.Pin[i].rect[2] << " " << lef.Pin[i].rect[3] << " ) ;" << endl;
	}
	write << "END PINS" << endl;
}


int main() {

	write.open("deffile.txt");// to open deffile text to make the DEF
	v.files("input.v.txt"); // parsing the v file
	lef.set_start("simple.lef.txt");
//	v.print_inputs();
	//v.print_components_name();
	getcomponentname();
	write_header();//missing only the diearea
	write_component();//mising the fixed location of each cell
	write_pins();//done
	print_nets();
	//write_nets();//can't work on anything here since it's mainly based on your part

	write << "END DESIGN" << endl;
	write.close();
	return 0;
}