#include "verilog.h"


verilog::verilog()
{
	inputs.clear();
	outputs.clear();
	wires.clear();
}
void verilog::files(string x) // the only needed function takes the name of the v file and parse it accordingly
{
	string temp;
	openfile.open(x);
	if (openfile.is_open())
	{
		openfile >> temp;
		openfile >> temp;
		module_name = temp;
		while (temp != ");")
		{
			//getline(openfile,temp,',');
			openfile >> temp;
			if (temp != "(")
			{
				checks.push_back(temp);
			}
		}
		dividinputs();
	}

	else
	{
		cout << "error in opening the file" << endl;
	}
}
void verilog::dividinputs() // divide our signals into wires, inputs ,and outputs,
{
	string temp, temp2;
	while (temp != "endmodule")
	{
		openfile >> temp;
		if (temp == "input") // storing the name of the inputs
		{
			getline(openfile, temp);
			inputs.push_back(temp);
		}
		else if (temp == "output") // stroing the name of the output
		{
			getline(openfile, temp);
			outputs.push_back(temp);
		}
		else if (temp == "wire") // storing the names of the wires
		{
			getline(openfile, temp);
			wires.push_back(temp);
		}
		else if (temp != "endmodule")
		{
			components(temp); // seperating the components name and module and connected wires
		}

	}
}
void verilog::print_inputs() // to print the input vector
{
	for (int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i] << endl;
	}
}
void verilog::print_outputs() // to print the output vector
{
	for (int i = 0; i < outputs.size(); i++)
	{
		cout << outputs[i] << endl;
	}
}
void verilog::print_wires() // to print the wire vector
{
	for (int i = 0; i < wires.size(); i++)
	{
		cout << wires[i] << endl;
	}
}
void verilog::print_components_module() // print modules
{
	for (int i = 0; i < components_module.size(); i++)
	{
		cout << components_module[i] << endl;
	}
}
void verilog::print_components_name() // print modules names with it's connected wires
{
	for (int i = 0; i < components_name.size(); i++)
	{
		cout << components_name[i] << endl;
	}
}
void verilog::components(string temp) // parse and read the modules in the v file
{
	components_module.push_back(temp);
	while (temp != ");")
	{
		openfile >> temp;
		if ((temp != "(") && (temp != ");"))
		{
			components_name.push_back(temp);
		}
	}
}
string verilog::getmodulename() // to return the module name
{
	return module_name;
}