#include "leffile.h"

leffile::leffile() {

}
string leffile::parsing_lines(string& x) {
	int findsemi = x.find(';');
	int found = x.find(' ');
	string return_str;
	string temp;
	if (found != -1 || findsemi != -1)
	{
		return_str = x.substr(0, found);
		temp = x.substr(found, findsemi);
		x = temp;
	}
	else
		return x;
	return return_str;
}

void leffile::parsying_site(string x, bool flag, site& temp_site, macro& temp_macro) {
	string width, height;
	int find_B = x.find('B');
	if (find_B != std::string::npos) {
		width.assign(x, find_B);
		width = x.substr(0, find_B);
		height = x.substr(find_B + 2);
		if (flag) {
			temp_site.size[0] = width;
			temp_site.size[1] = height;
		}
		else {
			temp_macro.size[0] = width;
			temp_macro.size[1] = height;
		}

	}
}

void leffile::parsying_pin(string read, pin& temp_pin) {
	int found;
	for (int i = 0; i < 4; i++) {
		found = read.find(' ');
		if (found != string::npos) {
			temp_pin.rect[i] = read.substr(0, found);
			read = read.substr(0 + found + 1);

		}
	}
}

void leffile::set_site(string temp, string read) {
	site temp_site;
	macro temp_macro;
	temp_site.site_name = read;
	getline(openfile, read);
	temp = parsing_lines(read);
	while (temp != "END") {
		if (temp == "SYMMETRY") {
			temp_site.symmetry = read;
		}
		else
			if (temp == "CLASS") {
				temp_site.PAD_CORE = read;
			}
			else
				if (temp == "SIZE")
					parsying_site(read, true, temp_site, temp_macro);
		getline(openfile, read);
		temp = parsing_lines(read);
	}
	Site.push_back(temp_site);
}

void leffile::set_layer(string temp, string read) {
	layer temp_layer;
	getline(openfile, read);
	temp = parsing_lines(read);
	while (temp != "END") {
		if (temp == "TYPE") {
			temp_layer.type = read;
		}
		else
			if (temp == "DIRECTION") {
				temp_layer.direction = read;
			}
			else
				if (temp == "PITCH") {
					temp_layer.pitch = read;
				}
				else
					if (temp == "OFFSET") {
						temp_layer.offset = read;
					}
					else
						if (temp == "WIDTH") {
							temp_layer.width = read;
						}
		getline(openfile, read);
		temp = parsing_lines(read);
	}
	Layer.push_back(temp_layer);
}

void leffile::set_pin(string temp, string read) {
	pin temp_pin;
	if (read.find("DIRECTION") != -1)
	{
		temp_pin.pin_name = read.substr(0, read.find("DIRECTION"));
		temp_pin.direction = read.substr(read.find("DIRECTION") + 10);
	}
	getline(openfile, read);
	temp = parsing_lines(read);
	while (temp != "END") {

		if (temp == "LAYER")
		{
			temp_pin.layer_name = read;
		}
		else
			if (temp == "RECT")
			{
				read = read.substr(read.find(' ') + 1);
				parsying_pin(read, temp_pin);
			}
		getline(openfile, read);
		temp = parsing_lines(read);
	}
	Pin.push_back(temp_pin);
}

void leffile::set_macro(string temp, string read) {
	macro temp_macro;
	site temp_site; // doesnot have a value just to make 1 function and be more moduler 
	temp_macro.name = read;
	string temp2;
	getline(openfile, read);
	temp = parsing_lines(read);
	string end_point = "END" + temp_macro.name;

	while (temp2 != end_point) {
		if (temp == "CLASS")
		{
			;
			temp_macro.PAD_CORE = read;
		}
		else
			if (temp == "SITE") {
				temp_macro.site_name = read;
			}
			else
				if (temp == "SIZE") {
					parsying_site(read, false, temp_site, temp_macro);
					;
				}
				else
					if (temp == "ORIGIN") {
						temp_macro.origin[0] = read.substr(0, read.find(' '));
						temp_macro.origin[1] = read.substr(read.find(' ') + 1);
					}
					else
						if (temp == "PIN") {
							set_pin(temp, read);
							Pin_counter++;
						}
		getline(openfile, read);
		temp2 = read;
		temp = parsing_lines(read);
	}
	Macro.push_back(temp_macro);
}

void leffile::set_start(string x) {
	string read;
	string temp, temp2;
	openfile.open(x);
	if (openfile.is_open())
	{
		getline(openfile, read);
		temp2 = read;
		temp = parsing_lines(read);
		while (temp2 != "END LIBRARY") {
			//the header
			while (temp != "SITE" && temp != "LAYER" && temp != "MACRO" && temp2 != "END LIBRARY") {

				if (temp == "VERSION")
					Start.version = read;
				else if (temp == "NAMESCASESENSITIVE")
					Start.case_sensitive = read;
				else
					if (temp == "BUSBITCHARS")
						Start.busbitchars = read;
					else
						if (temp == "DIVIDERCHAR")
							Start.dividerchar = read;
						else
							if (temp == "MANUFACTURINGGRID")
								Start.manufacturinggrid = read;
							else
								Start.units = read;
				getline(openfile, read);
				temp2 = read;
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

			getline(openfile, read);
			temp2 = read;
			temp = parsing_lines(read);
		}
	}
	else
		cout << "Could not open .lef file" << endl;
}