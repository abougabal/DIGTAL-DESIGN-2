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
void print_nets() // to get the nets and compare them to the wires they are connected to
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
void write_header() // printing the start of the def file
{
	write << "VERSION " << lef.Start.version << " ;" << endl;
	write << "DIVIDERCHARS " << lef.Start.dividerchar << " ;" << endl;
	write << "DESIGN " << v.module_name << " ;" << endl;
	write << "UNITS " << lef.Start.units << " ;" << endl;
	write << "DIEAREA" << "(0 0) ;" << endl;
}
void getcomponentname() // to get the names of the modules alone
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


void write_component() // writing the component section in the def file
{
	srand(time(NULL));
	int random = rand() % 1;
	string orient;

	write << "COMPONENTS " << v.components_module.size() << " ;" << endl;
	for (int i = 0; i < v.components_module.size(); i++) {
		if (lef.Site.size() > i ) {
			if (lef.Site[i].symmetry[0] == 'X')
				if (random == 1) orient = " N";
				else orient = " FS";
			else
				if (random == 1) orient = " FN";
				else orient = " S";
		}
		write << " - " << comp_temp[i] << " " << v.components_module[i] << endl;
		write << "  + FIXED ( " << "..." << " ) " << orient << " ;" << endl;//issue here
	}
	write << "END COMPONENTS" << endl;
}

void write_pins() // writing the pin section in the def file
{

	write << "PINS " << v.inputs.size()+v.outputs.size() << " ;" << endl;
	for (int i = 0; i < v.inputs.size(); i++) {
		write << " - " << v.inputs[i] << " + NET " << v.components_name[i] << endl;
		write << " + DIRECTION " << "INPUT" << endl;
		write << " + FIXED" << endl;
		write << " + LAYER " << lef.Pin[i].layer_name << " ( " << lef.Pin[i].rect[0] << " " << lef.Pin[i].rect[1];
		write << " ) ( " << lef.Pin[i].rect[2] << " " << lef.Pin[i].rect[3] << " ) ;" << endl;
	}
	for (int i = 0; i < v.outputs.size(); i++) {
		write << " - " << v.outputs[i] << " + NET " << v.components_name[i] << endl;
		write << " + DIRECTION " << "OUTPUT" << endl;
		write << " + FIXED" << endl;
		write << " + LAYER " << lef.Pin[i].layer_name << " ( " << lef.Pin[i].rect[0] << " " << lef.Pin[i].rect[1];
		write << " ) ( " << lef.Pin[i].rect[2] << " " << lef.Pin[i].rect[3] << " ) ;" << endl;
	}
	write << "END PINS" << endl;
}


int main() {
	int aspectratio, coreuti;
	string file1, file2; // to take the file names
//	cout << "enter aspect ratio" << endl;
	//cin >> aspectratio;
	//cout << " enter core utilization" << endl;
	//cin >> coreuti;
	//cout << "enter the name of the v file including the .txt" << endl;
	//cin >> file1;
	//cout << "enter the name of the lef file including the .txt" << endl;
	//cin >> file2;

	write.open("deffile.txt");// to open deffile text to make the DEF
	v.files("input.v.txt"); // parsing the v file
	lef.set_start("simple.lef.txt");
	for (int i = 0; i < lef.Macro.size(); i++)
		cout <<lef.Macro[i].name << endl;
	getcomponentname(); // to get the names of the modules and printing them on the screen
	write_header();//missing only the diearea
	write_component();//mising the fixed location of each cell
	write_pins();//done
	print_nets();
	write << "END DESIGN" << endl;
	write.close();
	return 0;
}