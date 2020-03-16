#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

ifstream f("DFA1");
ifstream g("DFA2");
ofstream h("last_hope");

int nrSt1, St1[10000], nrLit1, stInit1, nrStFin1, stFin1[10000], nrTranz1;
char Lit1[10000];
map <pair<int, char>, int> myMap1;

int nrSt2, St2[10000], nrLit2, stInit2, nrStFin2, stFin2[10000], stFin2c[10000], nrTranz2, nrStFin2c;
char Lit2[10000];
map <pair<int, char>, int> myMap2;

int nrLit3;
char Lit3[10000];

vector <pair<pair<int, char>, int> > v;

///fiecare dintre datele prezenatate mai jos contin in program o cifra, in nume, ce reprezinta numarul automatului
/*nrSt = numar stari pentru automat
St = vector stari pentru automat
nrLit = numarul de litere din alfabetul automatului
stInit = starea initiala a automatului
nrStFin = numarul de stari finale ale automatului
stFin = vectoruld e stari finale ale automatului
stFinc = automatul complementar celui dat
nrTranz = numarul de tranzitii
Lit = alfabetul automatului
myMap = hash-ul in care retin transpozitiile
//nrStFin2c = nr starilof inale din complementul lui L2
v-retin tranzitiile vizitate pentru verificarea unui automat daca este vid*/

void read()
{
    //citire primul limbaj
    f>>nrSt1;
    for (int i = 0; i < nrSt1; i++)
        f>>St1[i];


    f>>nrLit1;
    for (int i = 0; i < nrLit1; i++)
        f>>Lit1[i];

    f>>stInit1;
    f>>nrStFin1;
    for (int i = 0; i < nrStFin1; i++)
        f>>stFin1[i];

    f>>nrTranz1;
    int x, y;
    char z;
    for (int k = 0; k < nrTranz1; k++)
    {
        f>>x>>z>>y;
        int s1 = -1, s2 = -1; //renumerotez starile primului automat
        for (int i = 0; i < nrSt1 && (s1 == -1 || s2 == -1); i++)
        {
            if (St1[i] == x)
                s1 = i + 1;
            if (St1[i] == y)
                s2 = i + 1;
        }
        char lt = 'A';
        for (int i = 0; i < nrLit1 && lt== 'A'; i++)
            if (Lit1[i] == z)
                lt = 'a' + i;

        myMap1.insert(make_pair(make_pair(s1, lt), s2));//elementele vor fi retinute in hash sub forma key=('stare de start','litera'), value=('destinatie')
    }

    for (int i = 0; i < nrSt1; i++)
        St1[i] = i + 1;
    for (int i = 0; i < nrLit1; i++)
        Lit1[i] = 'a' + i;

    //citire al doilea limbaj
    g>>nrSt2;
    for (int i = 0; i < nrSt2; i++)
        g>>St2[i];

    g>>nrLit2;
    for (int i = 0; i < nrLit2; i++)
        g>>Lit2[i];

    g>>stInit2;
    g>>nrStFin2;
    for (int i = 0; i < nrStFin2; i++)
        g>>stFin2[i];

    g>>nrTranz2;
    int w, v;
    char t;
    for (int i = 1; i <= nrTranz2; i++)
    {
        g>>w>>t>>v;
        int s1 = -1, s2 = -1; //renumerotez starile celui de-al doilea automat
        for (int i = 0; i < nrSt2 && (s1 == -1 || s2 == -1); i++)
        {
            if (St2[i] == w)
                s1 = i + 1;
            if (St2[i] == v)
                s2 = i + 1;
        }
        char lt = 'A';
        for (int i = 0; i < nrLit2 && lt== 'A'; i++)
            if (Lit2[i] == t)
                lt = 'a' + i;
        myMap2.insert(make_pair(make_pair(s1, lt), s2));
    }
    for (int i = 0; i < nrSt2; i++)
        St2[i] = i + 1;
    for (int i = 0; i < nrLit2; i++)
        Lit2[i] = 'a' + i;

    nrStFin2c = nrSt2 - nrStFin2;
}

/**COMPLEMENTUL UNUI AUTOMAT**/
void complement(int fin[10000], int nrFin, int nrS, int st[10000], int newFin[10000])
{
    //transform toate starile finale in stari nefinale, iar pe cele nefinale in stari finale
    int k = 0;
    for (int i = 0; i < nrS; i++)
    {
        int sw = 1;
        for(int j = 0; j < nrFin && sw; j++)
            if(fin[j] == st[i])
                sw = 0;
        if(sw)
            newFin[k++] = st[i];
    }
}

void display_complement(int Fin[10000], int nrF, int nr)
{
    cout<<"Complementul automatului "<<nr<<" este dat de starile finale: ";
    for (int i = 0; i < nrF; i++)
        cout<<Fin[i]<<' ';
    cout<<endl;
}

/**VERIFIC DACA LIMBAJELE SUNT VIDE**/
bool searchVect(vector <pair<pair<int, char>, int> > v, int x, char y, int z)
{
    //caut in v daca am tranzitia (x,y)->z
    vector <pair<pair<int, char>, int> >::iterator it = v.begin();
    for (it = v.begin(); it != v.end(); it++)
        if (it->first.first == x && it->first.second == y && it->second == z)
            return 1;
    return 0;

}

void DFS(int x, int y, map<pair<int, char>, int> mmap, int nrL, int nrS, char lit[10000], int Str[10000])
{
    if (y < nrL)  //verific daca mai am litere
    {
        //caut stare in care duce (x,y)
        int z = -1;
        map<pair<int, char>, int>::iterator it = mmap.begin();
        for (it = mmap.begin(); it != mmap.end() && z == -1; it++)
            if (it->first.first == x && it->first.second == lit[y])
                z = it->second;

        //verific daca exista in vectorul de stari parcurse starea (x,y)->z
        if (z != -1)
        {
            //introduc in vector tranzitia curenta daca aceasta nu a mai existat si fac DFS de la starea nou gasita si prima litera a alfabetului
            if (!searchVect(v, x, lit[y], z))
            {
                v.push_back(make_pair(make_pair(x, lit[y]), z));
                DFS(z, 0, mmap, nrL, nrS, lit, Str);
            }
        }
        else
        {
            //in cazul in care nu exista o nou tranzitie, fac DFS intre starea curenta si urmatoarea litera a alfabetului
            y++;
            DFS(x, y, mmap, nrL, nrS, lit, Str);
        }
    }
}

bool vid(map <pair<int, char>, int> mmap, int nrSF, int nrS, int stI, int nrL, char lit[10000], int Str[10000], int StFn[10000])
{
    DFS(stI, 0, mmap, nrL, nrS, lit, Str);
    vector <pair<pair<int, char>, int> >::iterator it = v.begin();
    for (int i = 0; i < nrSF; i++)
    {
        for (it = v.begin(); it != v.end(); it++)
            if (it->second == StFn[i])
                return false;
    }

    return true;
}

/**INTERSECTIA A DOUA AUTOMATE **/
bool searchState(vector <pair<int, int> >v, int s1, int s2)
{
    //caut perechea generata de starile s1 si s2
    vector <pair<int, int> >::iterator i;
    for (i = v.begin(); i != v.end(); i++)
        if (i->first == s1 && i->first == s2)
            return true;
    return false;
}

bool Intersection()
{
    //creez alfabetul pt automatul 3
    (nrLit1 < nrLit2)?nrLit3 = nrLit1: nrLit3 = nrLit2;
    for (int i = 0; i < nrLit3; i++)
        Lit3[i] = 'a' + i;

    //declar un vector in care voi introduce starile deja parcurse cu transpozitiile aferente
    vector <pair<int, int> > myVector;
    //introduc in coada perechile tranzitiile pe care le voi parcurge de forma (elA1, elA2)->Lit3[i]
    queue <pair<int, int> > myQueue;
    myQueue.push(make_pair(stInit1, stInit2));
    while(!myQueue.empty())
    {
        //retin datele primului elem din coada
        int p1 = myQueue.front().first;
        int p2 = myQueue.front().second;
        //verific daca (p1, p2) cu literele alfabetului dau stari nevide
        map <pair<int, char>, int>::iterator it1=myMap1.begin();
        for (it1 = myMap1.begin(); it1 != myMap1.end(); it1++)
        {
            //verific daca p1 genereaza vreo stare in map1
            if (it1->first.first == p1)
            {
                map <pair<int, char>, int>::iterator it2=myMap2.begin();
                //verific daca p2 genereaza vreo stare in map2
                for (it2 = myMap2.begin(); it2 != myMap2.end(); it2++)
                {
                    if (it2->first.first == p2)
                    {
                        if (!searchState(myVector, p1, p2))
                            myVector.push_back(make_pair(p1, p2));
                        //introduc in coada starile generate de litere automatului3 cu elem curent din coada
                        for (int i = 0; i < nrLit3; i++)
                        {
                            int poz1 = -1, poz2 = -1;
                            map <pair<int, char>, int>::iterator it1c=myMap1.begin();
                            map <pair<int, char>, int>::iterator it2c=myMap2.begin();
                            //caut in map1 starea generata de (p1, Lit3[i])
                            for (it1c = myMap1.begin(); it1c != myMap1.end(); it1c++)
                                if (it1c->first.first == p1 && it1c->first.second == Lit3[i])
                                    poz1 = it1c->second;
                            //caut in map2 starea generata de (p2, Lit3[i])
                            for (it2c == myMap2.begin(); it2c != myMap2.end(); it2c++)
                                if (it2c->first. first == p2 && it2c->first.second == Lit3[i])
                                    poz2 = it2c->second;
                            //daca ambele automate duc intr-o stare utilizand litera curenta a automatului3, atunci introduc starea nou generata in coada
                            if ((poz1 != -1 && poz2 != -1) && (!searchState(myVector, poz1, poz2)))
                                myQueue.push(make_pair(poz1, poz2));

                        }
                    }
                }
            }
        }
        myQueue.pop();
    }

    //verific daca in vector gasesc pe cel putin o pozitie o pereche formata dintr-o stare finala din primul automat si o stare finala din complementul celui de-al doilea automat, in cazul in care nu exista, automatele sunt echivalente
    for (int i = 0; i < myVector.size(); i++)
        for (int j = 0; j < nrStFin1; j++)
            if (myVector[i].first == stFin1[j])
                for (int k = 0; k < nrStFin2c; k++)
                    if (myVector[i].second == stFin2c[k])
                        return false;

    return true;
}

int main()
{
    read();

    ///realizez complementele Automatului 2
    complement(stFin2, nrStFin2c, nrSt2, St2, stFin2c);

    //Verific daca limbajele sunt vide
    int dfs1 = vid(myMap1, nrStFin1, nrSt1, stInit1, nrLit1, Lit1, St1, stFin1);
    v.clear();
    int dfs2 = vid(myMap2, nrStFin2, nrSt2, stInit2, nrLit2, Lit2, St2, stFin2);
    if (dfs1 && dfs2)
    {
        h<<"Ambele automate sunt vide.";
        return -1;
    }
    else if (dfs1 && !dfs2)
    {
        h<<"Automatul 1 este vid.";
        return -1;
    }
    else if (!dfs1 && dfs2)
    {
        h<<"Automatul 2 este vid.";
        return -1;
    }

    //intersectia limbajelor
    h<<"Limbajele sunt nevide."<<endl;
    if (Intersection())
        h<<"Limbajele sunt echivalente.";
    else
    {
        h<<"Limbajele nu sunt echivalente.";
        return -1;
    }

    return 0;
}
