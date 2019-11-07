#include <iostream>
#include <string>
#include <vector>
#include "verilog.h"
using namespace std;
int main()
{
	verilog testing;
	testing.files("input.v.txt");
	testing.print_inputs();
	testing.print_wires();
	testing.print_components_module();
	testing.print_components_name();
	system("pause");
	return 0;
}