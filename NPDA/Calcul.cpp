#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include "myClass.h"

using namespace std;

Calcul::Calcul(string stare1, int banda1, int adancime1, stack<string> myStack1)
{
	stare = stare1;
	banda = banda1;
	adancime = adancime1;
	myStack = myStack1;
}

Calcul::~Calcul()
{
	cout << "Destructor Calcul." << endl;
}

string Calcul::getStare()
{
	return stare;
}

int Calcul::getBanda()
{
	return banda;
}

int Calcul::getAdancime()
{
	return adancime;
}

stack<string> Calcul::getMyStack()
{
	return myStack;
}
