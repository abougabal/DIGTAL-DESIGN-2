#include "leffile.h"

leffile::leffile() {

}
string leffile::parsing_lines(string& x) {
//	char space = ' ';
	//char semi = ';';
	int findsemi = x.find(';');
	int found = x.find(' ');
	string return_str;
	string temp;
	if (found != 0)
	{
		return_str.assign(x, found);
	//	temp.assign(x, x.begin() + found, findsemi);
		temp = x.substr(found, findsemi);
		x = temp;
	}
	else
		return x;
	return return_str;
}

void leffile::parsying_site(string x, bool flag, site & temo_site) {
	string width, height;
	int find_B = x.find('B');
	if (find_B != std::string::npos) {
		width.assign(x, find_B);
		width = x.substr(0, find_B);
		height = x.substr(find_B + 2);
	//height.assign(x, x.begin() + find_B + 2, x.end() - 1);
	//	height = x.substr(x + find_B + 2, x.end() - 1);
		if (flag) {
			//Site[Site_counter].size[0] = width;
			//Site[Site_counter].size[1] = height;
		}
		else {
			Macro[Macro_counter].size[0] = width;
			Macro[Macro_counter].size[1] = height;
		}

	}
}

void leffile::parsying_pin(string read) {
	int found;
	for (int i = 0; i < 4; i++) {
		found = read.find(' ');
		if (found != string::npos) {
			Pin[Pin_counter].rect[i].assign(read, found);
			read.erase(read.begin(), found);
		}
	}
}

void leffile::set_site(string temp, string read) {
	//Site[Site_counter].site_name = read;
	site temp_site;
	temp_site.site_name = read;
	getline(cin, read);
	temp = parsing_lines(read);
	while (temp != "END") {
		if (temp == "SYMMETRY") {
			//Site[Site_counter].symmetry = read;
			temp_site.symmetry = read;
		}
		else
			if (temp == "CLASS") {
				//Site[Site_counter].PAD_CORE = read;
				temp_site.PAD_CORE = read;
			}
			else
				if (temp == "SIZE")
					parsying_site(read, true,temp_site);
		getline(cin, read);
		temp = parsing_lines(read);
	}
}

void leffile::set_layer(string temp, string read) {
	Layer[Layer_counter].name = read;
	getline(cin, read);
	temp = parsing_lines(read);
	while (temp != "END") {
		if (temp == "TYPE")
			Layer[Layer_counter].type = read;
		else
			if (temp == "DIRECTION")
				Layer[Layer_counter].direction = read;
			else
				if (temp == "PITCH")
					Layer[Layer_counter].pitch = read;
				else
					if (temp == "OFFSET")
						Layer[Layer_counter].offset = read;
					else
						if (temp == "WIDTH")
							Layer[Layer_counter].width = read;
		getline(cin, read);
		temp = parsing_lines(read);
	}
}

void leffile::set_pin(string temp, string read) {
	Pin[Pin_counter].pin_name = read;
	getline(cin, read);
	temp = parsing_lines(read);
	while (temp != "END") {
		if (temp == "LAYER")
			Pin[Pin_counter].layer_name = read;
		else
			if (temp == "RECT")
				parsying_pin(read);
	}
}

void leffile::set_macro(string temp, string read) {
	Macro[Macro_counter].name = read;
	getline(cin, read);
	temp = parsing_lines(read);
	string end_point = "END" + Macro[Macro_counter].name;
	while (temp != end_point) {
		if (temp == "CLASS")
			Macro[Macro_counter].PAD_CORE = read;
		else
			if (temp == "SITE")
				Macro[Macro_counter].site_name = read;
			else
				if (temp == "SIZE")
					parsying_site(read, false);
				else
					if (temp == "ORIGIN") {
						Macro[Macro_counter].origin[0] = read[0];
						Macro[Macro_counter].origin[1] = read[2];
					}
					else
						if (temp == "PIN") {
							set_pin(temp, read);
							Pin_counter++;
						}
		getline(cin, read);
		temp = parsing_lines(read);
	}
}

void leffile::set_start(string x) {
	string read;
	string temp;
	//start Start;
	openfile.open(x);
	if (openfile.is_open())
	{
		getline(openfile, read);
		temp = parsing_lines(read);
		while (temp != "END LIBRARY") {
			//the header
			while (temp != "SITE" && temp != "LAYER" && temp != "MACRO") {

				if (temp == "VERSION")
					Start.version = read;
				else
					if (temp == "BUSBITCHARS")
						Start.busbitchars = read;
					else
						if (temp == "DIVIDERCHAR")
							Start.dividerchar = read;
						else
							if (temp == "MANUFACTURINGGRID")
								Start.manufacturinggrid = read;
							else Start.units = read;
				getline(cin, read);
				temp = parsing_lines(read);
			}

			//the site
			if (temp == "SITE") {
				set_site(temp, read);
				Site_counter++;
			}

			//the layer
			if (temp == "LAYER") {
				set_layer(temp, read);
				Layer_counter++;
			}

			//the macro
			if (temp == "MACRO") {
				set_macro(temp, read);
				Macro_counter++;
			}

			getline(cin, read);
			temp = parsing_lines(read);
		}
	}
	else
		cout << "Could not open .lef file" << endl;
}