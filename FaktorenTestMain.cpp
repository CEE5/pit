// PIT.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Faktoren.h"

#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	//test
	Faktoren test;
	double s,t;
	short p;
	cout << "spg: "<<endl;
	cin >> s;
	cout << endl<< "tmp: "<<endl;
	cin >>t;
	cout << endl << "p: "<<endl;
	cin >> p;
	test.setProzess(p);
	test.setSpannung(s);
	test.setTemp(t);

	test.ausgabeFaktoren();

	cout << test.getProzess() << endl;
	cout << test.getSpannung() << endl;
	cout << test.getTemp() <<endl <<endl;

	cout << test.berechneSpannungFaktor( test.spannung) << endl; 
	cout << test.berechneTempFaktor( test.temp) << endl;
	cout << test.berechneProzessFaktor( test.prozess) << endl;

	test.ausgabeFaktoren();
	system("pause");

	return 0;
}

