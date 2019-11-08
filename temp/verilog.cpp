#include "verilog.h"


verilog::verilog()
{
	inputs.clear();
	outputs.clear();
	wires.clear();
}
void verilog::files(string x)
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
void verilog::dividinputs()
{
	string temp, temp2;
	while (temp != "endmodule")
	{
		openfile >> temp;
		if (temp == "input")
		{
			openfile >> temp;
			inputs.push_back(temp);
		}
		else if (temp == "output")
		{
			openfile >> temp;
			outputs.push_back(temp);
		}
		else if (temp == "wire")
		{
			openfile >> temp;
			wires.push_back(temp);
		}
		else if (temp != "endmodule")
		{
			components(temp);
		}

	}
}
void verilog::print_inputs()
{
	for (int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i] << endl;
	}
}
void verilog::print_outputs()
{
	for (int i = 0; i < outputs.size(); i++)
	{
		cout << outputs[i] << endl;
	}
}
void verilog::print_wires()
{
	for (int i = 0; i < wires.size(); i++)
	{
		cout << wires[i] << endl;
	}
}
void verilog::print_components_module()
{
	for (int i = 0; i < components_module.size(); i++)
	{
		cout << components_module[i] << endl;
	}
}
void verilog::print_components_name()
{
	for (int i = 0; i < components_name.size(); i++)
	{
		cout << components_name[i] << endl;
	}
}
void verilog::components(string temp)
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
string verilog::getmodulename()
{
	return module_name;
}