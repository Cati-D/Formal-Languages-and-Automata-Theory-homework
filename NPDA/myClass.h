#ifndef MYCLASS_H_INCLUDED
#define MYCLASS_H_INCLUDED

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#pragma once
class Tranzitie
{
public:
	string dinStare;
	string inStare;
	string charBanda;
	string charPop;
	string charPush;

	Tranzitie() {}
	~Tranzitie() {}
};

class Calcul
{
	string stare;
	int adancime;
	int banda;
	stack<string> myStack;
public:
	string getStare();
	int getAdancime();
	int getBanda();
	stack<string> getMyStack();
	Calcul(string stare1, int banda1, int adancime1, stack<string> myStack1);
	~Calcul();
};

class Automat
{
	const string epsilon = "e";
	const string emptyStack = "$";
	vector<string> banda;
	vector<string> stariFinale;
	vector<Tranzitie> tranz;
	string stareInitiala;
	queue<Calcul*> calculCoada;
	bool Calculez(Calcul* c);
	vector<Tranzitie> getTranzitiiPosibile(string stare1, string bandaCitita, string stackTop);
public:
	Automat(vector<string> banda1, string stareInitiala1, vector<string> stareFinala1, vector<Tranzitie> tranz1);
	~Automat();
	bool Verificare();
};




#endif // MYCLASS_H_INCLUDED
