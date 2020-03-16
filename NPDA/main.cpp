#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>
#include "myClass.h"

using namespace std;

ifstream f("npda.in");

const string epsilon = "e";
const string emptyStack = "$";

void getUrmatorulCuvantDinLista(vector<string>* Vector)
{
	string linie;
	if (f)
	{
		while (getline(f, linie))
			(*Vector).push_back(linie);
	}
	else cout << "Nu s a deschis";

}

void getTranzitie(vector<Tranzitie>* tranz)
{
	vector<string> tranzPrim;
	if (f)
	{
		getUrmatorulCuvantDinLista(&tranzPrim);
		while (f)
		{
			Tranzitie t;
			t.dinStare = tranzPrim.at(0);
			t.charBanda = tranzPrim.at(1);
			t.charPop = tranzPrim.at(2);
			t.inStare = tranzPrim.at(3);
			t.charPush = tranzPrim.at(4);

			(*tranz).push_back(t);
			tranzPrim.clear();
			getUrmatorulCuvantDinLista(&tranzPrim);
		}
	}
	else cout << "Nu s a deschis2.";

}
/*
vector<Tranzitie> Automat::getTranzitiiPosibile(vector<Tranzitie> tranz, string stare1, string bandaCitita, string stackTop)
{
	vector<Tranzitie> t;
	vector<Tranzitie>::iterator it = tranz.begin();

	for (it = tranz.begin(); it != tranz.end(); ++it)
	{
		if (it->dinStare.compare(stare1)) continue; //vedem daca suntem in starea transmisa ca parametru
		if (it->charBanda.compare(bandaCitita) && it->charBanda.compare(epsilon)) continue;//daca nu exista o tranzitie la caracterul curent sau la epsilon
		if (it->charPop.compare(stackTop) && it->charPop.compare(epsilon)) continue;//vedem daca nu exista o tranzitie in varful stivei sau la epsilon

			t.push_back(*it);
	}

	return t;
}*/

int main()
{
	vector<string> stari, stariFinale, stariInitiale;
	vector<string> bandaAl, stackAl;
	vector<string> bandaInitiala;
	vector<Tranzitie> tranz;

	//string linie;
	if (f)
		cout << "Bine" << "************" << endl;
	else cout << "Nu" << "+++++";

	//Pe prima linie avem starile
	getUrmatorulCuvantDinLista(&stari);
	//Pe al doilea rand avem alfabetul benzii
	getUrmatorulCuvantDinLista(&bandaAl);
	//Pe al treile rand avem alfabetul stivei
	getUrmatorulCuvantDinLista(&stackAl);
	//Pe al patrulea rand avem starea initiala
	//getUrmatorulCuvantDinLista(&stariInitiale);
	string stareaInitiala;
	f >> stareaInitiala;
	//Pe al cincilea rand avem starile finale
	getUrmatorulCuvantDinLista(&stariFinale);
	//Pe al saselea rand avem limbajul
	getUrmatorulCuvantDinLista(&bandaInitiala);
	//Dupa a sasea linie avem tranzitiile
	getTranzitie(&tranz);

	//Stiva
	Automat* aut = new Automat(bandaInitiala, stareaInitiala, stariFinale, tranz);

	bool acceptat = false;
	acceptat = aut->Verificare();

	if (acceptat)
		cout << "Limbaj acceptat.";
	else cout << "Limbaj respins.";

	return 0;
}

