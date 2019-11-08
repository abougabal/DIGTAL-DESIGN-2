#include <iostream>
#include <string>
#include <vector>
#include "verilog.h"
#include "leffile.h"
using namespace std;
int main()
{
	verilog testing;
	leffile testing_2;
	/*testing.files("input.v.txt");
	testing.print_inputs();
	testing.print_wires();
	testing.print_components_module();
	testing.print_components_name();*/
	testing_2.set_start("simple.lef.txt");
	system("pause");
	return 0;
}