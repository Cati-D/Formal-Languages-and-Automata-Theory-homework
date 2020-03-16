#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include "myClass.h"

using namespace std;

Automat::Automat(vector<string> banda1, string stareInitiala1, vector<string> stareFinala1, vector<Tranzitie> tranz1)
{
	banda = banda1;
	stariFinale = stareFinala1;
	tranz = tranz1;
	stareInitiala = stareInitiala1;
}

Automat::~Automat()
{
}

vector<Tranzitie> Automat::getTranzitiiPosibile(string stare1, string bandaCitita, string stackTop)
{
	vector<Tranzitie> t;
	vector<Tranzitie>::iterator it = tranz.begin();

	for (it = tranz.begin(); it != tranz.end(); ++it)
	{
		if(it->dinStare.compare(stare1)) continue; //vedem daca suntem in starea transmisa ca parametru
		if(it->charBanda.compare(bandaCitita) && it->charBanda.compare(epsilon)) continue;//daca nu exista o tranzitie la caracterul curent sau la epsilon
		if(it->charPop.compare(stackTop) && it->charPop.compare(epsilon)) continue;//vedem daca nu exista o tranzitie in varful stivei sau la epsilon

		t.push_back(*it);
	}

	return t;
}

bool Automat::Calculez(Calcul* c)
{
	string stare1 = c->getStare();
	int banda1 = c->getBanda();
	int adancime1 = c->getAdancime();
	stack<string> stackNew = c->getMyStack();

	bool acceptat = false;

	string stackTop = stackNew.size() ? stackNew.top() : epsilon;
	string bandaCitita = banda1 < banda.size() ? banda.at(banda1) : epsilon;

	for (int i = 0; i < adancime1; i++)cout << "\t|";
	cout << "--Starea curenta: " << stare1 << "\t(Banda: " << bandaCitita << "Varful stivei: " << stackTop << ')' << "Dimensiunea: " << stackNew.size() << endl;

	//Verific daca actualele conditii determina un sfarsit valid
	if (!(banda1 < banda.size()) && stackTop.compare(emptyStack) && (find(stariFinale.begin(), stariFinale.end(), stare1) != stariFinale.end()))
		acceptat = true;

	vector<Tranzitie> tranzitiiPosibile = getTranzitiiPosibile(stare1, bandaCitita, stackTop);
	vector<Tranzitie>::iterator it = tranzitiiPosibile.begin();
	for (it = tranzitiiPosibile.begin(); it != tranzitiiPosibile.end(); ++it)
	{
		int bandaUrm = banda1;
		stack<string> stackCopy = stackNew;
		//Cazul in care tranzitia elimina ceva din stiva
		if (it->charPop.compare(epsilon))
			stackCopy.pop();
		//Cazul in care o tranzitie citeste caracterul benzii curente
		if (it->charBanda.compare(epsilon))
			bandaUrm++;
		//Daca tranzitia adauga ceva in stiva
		if (it->charPush.compare(epsilon))
			stackCopy.push(it->charPush);

		for (int i = 0; i < adancime1; i++) cout << "\t|";
		cout << "--Traznizit: " << "[" << it->dinStare << " " << it->charBanda << " " << it->charPop << "]";
		cout << "-->" << "[" << it->inStare << " " << it->charPush << "]";
		cout << endl;

		calculCoada.push(new Calcul(it->dinStare, bandaUrm, adancime1 + 1, stackCopy));
	}

	for (int i = 0; i < adancime1; i++) cout << "\t|";
	cout << (acceptat ? "Acceptat." : "");
	cout << "\n";

	return acceptat;
}

bool Automat::Verificare()
{
	stack<string> myStack;
	bool acceptat = false;
	calculCoada.push(new Calcul(stareInitiala, 0, 0, myStack));
	while (!calculCoada.empty())
	{
		Calcul* c = calculCoada.front();
		calculCoada.pop();
		acceptat = Calculez(c);
		if (acceptat) break;
	}

	return acceptat;
}
