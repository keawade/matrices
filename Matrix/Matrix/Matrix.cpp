//============================================================================
// Name        : Math382.cpp
// Author      : Keith Wade, Tyler Brummett, Adam McAfee
// Version     : 0.1
// Copyright   : Your copyright notice is best notice.
// Description : Matrix Manipulation
//============================================================================

#include "stdafx.h"
#include <iostream>
//#include <string>
#include <string>
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <deque>          // std::deque
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>;
#include <windows.h>

using namespace std;

class matrix{
private:

public:
	int a, b;
	double **Matrix;

	matrix(){
		Matrix = new double *[3];
		for (int x = 0; x < 3; x++){
			Matrix[x] = new double[3];
		}
		a = b = 3;
	}

	matrix(int y){
		Matrix = new double *[y];
		for (int x = 0; x < y; x++){
			Matrix[x] = new double[y];
		}
		a = b = y;
	}

	matrix(int a, int b){
		Matrix = new double *[a];
		for (int x = 0; x < a; x++){
			Matrix[x] = new double[b];
		}
		this->a = a;
		this->b = b;
	}

	matrix(double **m, int x, int y){
		Matrix = m;
		a = x;
		b = y;
	}

	void set(int a, int b, double x){
		Matrix[a][b] = x;
	}

	double get(int a, int b){
		return Matrix[a][b];
	}

	matrix operator*(matrix t){
		if (b != t.a){
			cout << "Invalid multiplication" << endl;
			return NULL;
		}

		matrix c(this->a, t.b);

		for (int x = 0; x < c.a; x++){
			for (int y = 0; y < c.b; y++){
				double z = 0;
				for (int final = 0; final <= t.b; final++){
					z += this->get(x, final) * t.get(final, y);
				}
				c.set(x, y, z);
			}
		}
		return c;
	}

	matrix operator+(matrix t){
		if (t.a != a || t.b != b){
			cout << "Matrix provided are not the same size" << endl;
			return matrix();
		}
		matrix m(a, b);
		for (int x = 0; x < a; x++){
			for (int y = 0; y < b; y++){
				m.Matrix[x][y] = Matrix[x][y] + t.Matrix[x][y];
			}
		}
		return m;
	}

	matrix operator-(matrix t){
		if (t.a != a || t.b != b){
			cout << "Matrix provided are not the same size" << endl;
			return matrix();
		}
		matrix m(a, b);
		for (int x = 0; x < a; x++){
			for (int y = 0; y < b; y++){
				m.Matrix[x][y] = Matrix[x][y] - t.Matrix[x][y];
			}
		}
		return m;
	}

	void rref(){
		int lead = 0;
		int rowCount = a;
		int columnCount = b;
		for (int r = 0; r < rowCount; r++){
			if (lead > columnCount){
				return;
			}
			int i = r;
			while (Matrix[i][lead] == 0){
				i = i + 1;
				if (i >= rowCount) {
					i = r;
					lead = lead + 1;
					if (lead > columnCount){
						return;
					}
				}
			}
			//swap rows i and r;
			for (int col = 0; col <= columnCount; ++col){
				double temp = Matrix[i][col];
				Matrix[i][col] = Matrix[r][col];
				Matrix[r][col] = temp;
			}

			if (Matrix[r, lead] != 0){
				//divide row r by M[r, lead]
				double temp = Matrix[r][lead];
				for (int _a = 0; _a < columnCount; _a++){
					Matrix[r][_a] /= temp;
				}

			}
			for (int i = 0; i < rowCount; i++){
				if (i != r){
					double temp = Matrix[i][lead]; //save the lead number
					for (int col = 0; col < columnCount; ++col){
						Matrix[i][col] -= temp * Matrix[r][col];
					}
				}
			}
		}
	}

	void print(){
		for (int x = 0; x < a; x++){
			cout << "[\t";
			for (int y = 0; y < b; y++){
				cout << Matrix[x][y] << "\t";
			}
			cout << "]\n";
		}
	}
};

vector<matrix> matrices;

void doCommand(string command){
	if (command == "peek"){
		matrices[matrices.size()-1].print();
	}
	else if (command == "pop"){
		matrices.pop_back();
	}
	else if (command.find("push") != std::string::npos){//are we pushing?
		vector<vector<double>> m;
		command = command.substr(command.find("[")+1, command.find_last_of("]")-1);//getting only the martix
		
		std::stringstream ss(command);
		std::string item;
		char delim = ',';
		int x = -1;
		while (std::getline(ss, item, delim)) {
			if (item.find("[")!= string::npos){//start a new array?				
				m.push_back(vector<double>());
				item = item.substr(1, item.size()); //remove the end of the array
				x++;
			}

			if (item.find("]") != string::npos){//is end of array?
				item = item.substr(0,command.find("]")-1); //remove the end of the array
			}

			double i = atoi(item.c_str());
			m[x].push_back(i);
			
		}

		double** temp;
		int size = m.size();
		temp = new double*[size];
		for (unsigned i = 0; (i < size); i++)
		{
			int s = m[i].size();
			temp[i] = new double[s];
			for (unsigned j = 0; (j < m[0].size()); j++)
			{
				temp[i][j] = m[i][j];
			}
		}
		
		matrices.push_back(matrix(temp,m.size(),m[0].size()));

		
	}
	else if (command.find("*") != std::string::npos){//multiplying
		
		std::stringstream ss(command);
		std::string item;
		char delim = '*';
		
		std::getline(ss, item, delim);
		double i = atoi(item.c_str());
		
		std::getline(ss, item, delim);
		double j = atoi(item.c_str());
		
		matrices.push_back(matrices[i] * matrices[j]);

	}
	else if (command.find("-") != std::string::npos){//subtracting
		std::stringstream ss(command);
		std::string item;
		char delim = '-';

		std::getline(ss, item, delim);
		double i = atoi(item.c_str());

		std::getline(ss, item, delim);
		double j = atoi(item.c_str());
		
		matrices.push_back(matrices[i] - matrices[j]);
	}
	else if (command.find("+") != std::string::npos){//adding
		std::stringstream ss(command);
		std::string item;
		char delim = '+';

		std::getline(ss, item, delim);
		double i = atoi(item.c_str());

		std::getline(ss, item, delim);
		double j = atoi(item.c_str());

		matrices.push_back(matrices[i] + matrices[j]);
	}
	else if (command.find("rref") != std::string::npos){
		command = command.substr(4, command.size());
		double j = atoi(command.c_str());
		matrices[j].rref();

	}
}

int main(int argc, char **args){
	string line;
	ifstream commands;

	if (argc != 2){
		commands.open("commands.txt");
	} else {
		commands.open(args[1]);
	}

	if (commands.is_open()){ //check that opening worked
		while ( getline(commands, line)){
			doCommand(line); // function to do the command put in
		}
		commands.close(); //close the file we are reading
	} else {
		cout << "File could not be opened." << endl << "Either the files doesnt exist or you have bad permissions";

	}

	return 0;
}