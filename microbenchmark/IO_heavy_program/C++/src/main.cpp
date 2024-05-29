#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std; 

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		cerr << "Error: Number of Inputs is Incorrect. Exiting" << endl;
		exit(1);
	}
/*
	your code here
*/
    ifstream infile(argv[1]);
    ofstream myfile;
	myfile.open(argv[2]);
    int n,x;
    infile >> n;
    infile >> x;
    int count = 0;
	int c = 1;
	int a = 0;
    myfile << " | ";
    while(!infile.eof()) {
        int current;
		int next;
        count++;
        infile >> current;
        myfile << current;
        for ( int i = 1; i < n; i++) {
            if (current < pow(10, i)) {
                myfile << " ";
            }
        }
		next = infile.peek();
		if (next == EOF) {
			myfile << " |";
		}
		else{
			if ( count == 1) {
		 		myfile << " |\n";
				myfile << " | ";
				a = count + x + 1;
			}
        	else if (count == a) {
				c++;
				a = count + x*c +1;
        	    myfile << " |\n";
				myfile << " | ";
        	}
        	else {
        	    myfile << " | ";
        	}
		}
	}
	infile.close();
	myfile.close();
	return 0;
}