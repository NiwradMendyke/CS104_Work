#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
	ofstream output(argv[1]);

	int floors = 100;
	int residents = floors / 10;

	output << floors << endl;

	for (int i = 1; i <= floors; i++) {
		output << "MOVEIN " << i << " " << residents << endl;
	}

	for (int i = 1; i <= floors; i++)
		for (int j = 1; j <= residents; j++) {
			output << "OBTAIN " << i << " " << j << " " << j;
			for (int k = 0; k < j; k++)
				output << " " << k;
			output << endl;
		}

	for (int i = 1; i <= floors; i++)
		for (int j = 1; j <= residents; j++)
			output << "OUTPUT " << i << " " << j << endl;

	output.close();
}