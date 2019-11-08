#include <iostream>
#include <string>
#include <vector>
//#include "verilog.h"
#include "leffile.h"
using namespace std;
int main()
{
	//verilog testing;
	leffile testing_2;
	/*testing.files("input.v.txt");
	testing.print_inputs();
	testing.print_wires();
	testing.print_components_module();
	testing.print_components_name();*/
	testing_2.set_start("simple.lef.txt");
	for (int i = 0; i < testing_2.Site.size(); i++)
		cout << testing_2.Site[i].PAD_CORE << "l " << testing_2.Site[i].site_name << " l2" <<
		testing_2.Site[i].size[0] << " l3" << testing_2.Site[i].symmetry << endl;
	system("pause");
	return 0;
}