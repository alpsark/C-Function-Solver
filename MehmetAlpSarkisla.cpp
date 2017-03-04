#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <vector>

using namespace std;
//Global variables
vector<double> coef; //Coefficents of function
double tol; //Tolerance

// Function prototypes
void printarg(int argc,char* argv[]) ;
vector<double> str2num(int argc,char* argv[]) ;
double f (double x) ;
void secant (double &xk,double &xk_1,int &i,bool ishybrid);
void bisection (double &a,double &b,int &i,bool ishybrid);
void hybrid (double &a,double &b); 
//MAIN FUNCTION
int main (int argc,char* argv[]){
	printarg(argc,argv); //Prints the arguments	
	
	double x1,x0,a,b;
	coef= str2num(argc,argv); // Define coefficents
	for(int i=1 ; i<4 ; i++){
		stringstream stream	(argv[argc-i]);
		if (i == 1){
			stream >> tol; //take tolerance
		}
		else if (i == 2){
			stream >> x1; //take initial_guess_1
		}
		else {
			stream >> x0; //take initial_guess_2	x1>x0
		}
	}
	int it=0;
	a=x0;b=x1;
	bisection (a,b,it,false);
	
	a=x0;b=x1;
	it=0;
	secant (a,b,it,false);
	
	a=x0;b=x1;
	hybrid (a,b);
	return 0;
}
// Function definitions

//Function that prints the arguments
void printarg(int argc,char* argv[]){ 
	cout << "f(x) = " ;
	for (int i=1;i < argc;i++){
		if (i == argc-1){
			cout << "Tolerance = " << argv[i] << endl << endl;	
		}
		else if (i == argc-2){
			cout << "X1 = " << argv[i] << endl;
		}
		else if (i == argc-3){
			cout << " = 0" << endl << "X0 = " << argv[i] << endl;
		}
		else {
			if (argv [i][0] != '-' ) {
				cout << "+" ;
			}
			cout <<  argv [i] ;
			cout <<  "(x^" << argc-i-4 << ") ";

		}
		//You should see :
		//  f(x)= a_n (x^n) +a_(n-1) (x^n-1)+ ... +a_1 (x^1)+a_0 (x^0) = 0
		// X0 = initial_guess_1
		// X1 = initial_guess_2
		// Tolerance = Tolerance_val
		//if you did everything correctly
	}
}
//Define coefficents with dynamically allocated memory
vector<double> str2num(int argc,char* argv[]){
		vector<double> a;
		double temp;		
		for (int i = argc-4 ;i > 0 ; i--){
				stringstream stream(argv[i]);
				stream >> temp; 
				a.push_back(temp);//Dynamically allocated memory
		}
		return a;	
		// a(0) = a0 ,a(1) = a1 etc
}

//Function itself f(x)
double f (double x) {
	double sum =0.0;
	for(int i = 0;i < coef.size() ; i++ ){
		sum += pow(x,i) * coef.at(i) ;
	}
	return sum;
}

//Bisection algorithm
void bisection (double &a,double &b,int &i,bool ishybrid){
	double m;
	if (f(a) == 0){ // initial pick 2 is bullseye
			m = a;
			b = m;
	}
	else if (f(b) == 0){// initial pick 1 is bullseye
			m = b;
			a = a;
	}
	else if ( signbit(f(a)) != signbit(f(b)) ){ // if initials are wrong
		while ((b - a) > tol) {
			i++;
			m = (b + a)/2;
			if (f(m) == 0){ // average of initial picks are bullseye 
				a = m;
				b = m;
				break;
			}
			else if( signbit(f(a)) == signbit(f(m)) ){
				a = m;
			}
			else{
				b = m;
			}
			if(ishybrid){
				if(i==2){
					break;
				}
			}
		}
	}
	else{
		cout<<"Initial picks are wrong, bisection method failed."<<endl<<endl;
	}
	if (!ishybrid){
			cout <<"Bisection method " << endl;
			cout << "Number of iterations: " << i <<endl;
			cout << "x: " << m << endl<<endl;
	} 
}
//Secant algorithm
void secant (double &xk,double &xk_1,int &i,bool ishybrid){ //xk=x(k) ,xk_1=x(k-1)
	while (fabs(xk - xk_1) > tol){
			if (f(xk) == 0){		
				break;
			}
			double temp=xk;
			xk=xk - (f(xk) * ((xk-xk_1)/(f(xk)-f(xk_1))));
			xk_1=temp;			
			i++;
			secant(xk,xk_1,i,true); //recursion
	}
	if (!ishybrid){
			cout <<"Secant method " << endl;
			cout << "Number of iterations: " << i <<endl;
			cout << "x: " << xk << endl << endl;
	} 
}
//Hybrid algorithm
void hybrid (double &a,double &b){
	int it=0;
	bisection(a,b,it,true);
	secant(a,b,it,true);
	cout <<"Hybrid method " << endl;
	cout << "Number of iterations: " << it <<endl;
	cout << "x: " << a << endl << endl;
}



