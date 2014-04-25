//============================================================================
// Name        : Math382.cpp
// Author      : Keith Wade, Tyler Brummett, Adam McAfee
// Version     : 0.1
// Copyright   : Your copyright notice is best notice.
// Description : Matrix Manipulation
//============================================================================

#include <iostream>
//#include <string>
#include <string.h>
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <deque>          // std::deque

using namespace std;

class matrix{
	private:
			
	public:
		int a, b;
		double **Matrix;
		
		matrix(){
			Matrix = new double *[3];
			for(int x = 0; x < 3; x++){
				Matrix[x] = new double [3];
			}
			a = b = 3;
		}
		
		matrix(int y){
			Matrix = new double *[y];
			for(int x = 0; x < y; x++){
				Matrix[x] = new double [y];
			}
			a = b = y;
		}
		
		matrix(int a, int b){
			Matrix = new double *[a];
			for(int x = 0; x < a; x++){
				Matrix[x] = new double [b];
			}
			this -> a = a;
			this -> b = b;
		}
		
		matrix(double **m){
			Matrix = m;
		}
		
		void set(int a, int b, double x){
			Matrix[a][b] = x;
		}
		
		double get(int a, int b){
			return Matrix[a][b];
		}
		
		matrix operator*(matrix t){
			if(b != t.a){
				cout << "Invalid multiplication" << endl;
				return NULL;
			}
			
			matrix c(this -> a, t.b);
			
			for(int x = 0; x < c.a; x++){
				for(int y = 0; y < c.b; y++){
					double z = 0;
					for(int final = 0; final <= t.b; final++){
						z += this -> get(x,final) * t.get(final,y);
					}
					c.set(x, y, z);
				}
			}
			return c;
		}
		
		void print(){
			for(int x = 0; x < a; x++){
				cout << "[\t";
				for(int y = 0; y < b; y++){
					cout << Matrix[x][y] << "\t";
				}
				cout << "]\n";
			}
		}
};

matrix create(){
	int x, y;
	cout << "Please enter dimensions:\nx = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
	matrix tempA = matrix(x,y);
	return tempA;
}

int main(){
	stack<matrix> matrices;
	
	string input;
	string delim = ",";
	int past = 0;
	for(int x=0; x>0;x=input.find(delim,past)){

	}
	
	
}







