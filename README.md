# DIGTAL-DESIGN-2
DIGITAL DESIGN miniproject_2
this project was created for a course project in a university 
university: the American university in Cairo (AUC)
course: digital design 2
language of the program: C++
the program includes 3 mains file. Verilog class, leffile class, and the main in which we connect everything together.
our problem was stating: Develop a utility that accepts a Verilog synthesized netlist, the library LEF file and generates a DEF file. The DEF file must contain the components, pins and nets sections. Also, it must define the core area and the rows that will be used for placement. The user provides the following through command line arguments
•The aspect ratio
•Core utilization
•Library LEF
•Verilog netlist
How does our project works:
So, when the project is built it asks the user for 4 inputs. 2 of which are the V and LEF file. 
The program parses the files according and from the information we gathered from that file we then create a DEF file that contains the components, pins and nets section. In this DEF file the placement of the components wasn’t a part of our project, so we left them as (….). all the user had to do is only write the name of the files correctly other wise the program will not be able to open the file and get the necessary information.
Some deficiencies in the project 
Due to building our own parsers we assumed that the file will be written in a certain way so that our classes can parse them correctly. Also, we did not include everything of the DEF and LEF file we only parse small parts of them which was included in the project. For example, we do not support “[]” bus signals and in the Verilog file we do not support for example the inout signal.
A small preview of the files format expected to be inserted are at the end of this file and some test cases were inserted in this project to show the expected inputs and file formats.
Any extra spaces or misplaced ‘(‘ , ‘)’ , ‘;’ can make the parsers stuck in an infinite loop in one of the files and the project will not behave correctly 
.V
module test1 (
x,
x2,
x3,
y
);

input x;
input x2;
input x3;
output y;


wire vdd;
wire gnd;
wire w1;
wire w2;
wire w3;


OR2X2 OR2X2_4 ( .A(x), .B(x2), .Y(w1) );
AND2X2 AND2X2_4 ( .A(x3), .B(w1), .Y(w2) );
NAND2X1 NAND2X1_8 ( .A(w2), .B(w3), .Y(y) );

Endmodule

.LEF
VERSION 5.5 ;
NAMESCASESENSITIVE ON ;
BUSBITCHARS "[]" ;
DIVIDERCHAR "/" ;
UNITS 
DATABASE MICRONS 1000 ;
END UNITS
MANUFACTURINGGRID 0.005 ;
SITE core
SIZE 0.20 BY 2.00 ;
CLASS CORE ;
SYMMETRY Y ;
END core
LAYER metal1
TYPE ROUTING ;
DIRECTION HORIZONTAL ;
PITCH 0.200 ;
OFFSET 0.000 ;
WIDTH 0.100 ;
END metal1
MACRO INVX1
CLASS CORE ;
ORIGIN 0 0 ;
SIZE 0.8 BY 2.0 ;
SITE core ;
PIN ZN DIRECTION OUTPUT ;
PORT
LAYER metal1 ;
RECT 0.05 0.500 0.15 1.500 ;
END
END ZN
PIN A DIRECTION INPUT ;
PORT
LAYER metal1 ;
RECT 0.45 0.500 0.55 1.500 ;
END
END A
END INVX1
END LIBRARY


