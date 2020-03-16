#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
ifstream f("fisier");
ofstream g("f2");
int d=0, k, nrStari, stari[10000], nrLitere, stInit, nrStFin, stFin[10000], nrTranz, nrCuv, n;
char lit[1000], x, cuv[10000][256];
int* r=new int[10000];


struct valori
{
    int v[100];  //retin starile in care poate da o pereche de forma (stare, litera)
    int i;     //retin numarul de astfel de stari
} tranz[10000][26];

int* deltaTilda(int stare, char word[256])
{
    if(strlen(word) == 1)
        if(tranz[stare][word[0]-'a'].i == 0)
            return NULL;
        else
            return tranz[stare][word[0]-'a'].v;  //returnez adresa vectorului ce contine posibilele valori pe care le pot obtine din perechea (stare, word)
    else
    {
        int j;
        k=tranz[stare][word[0]-'a'].i;    //verific daca exista o stare rezultanta
        if(k==0)
            return NULL;
        for(j=0; j<k; j++, d++)
            r[d]=tranz[stare][word[0]-'a'].v[j];  //copiez toate starile posibile geenrate de perechea (stare, litera)
        deltaTilda(r[d-1], word+1); d=0;
    }
}

void verif(int stare, char word[256])
{
    if(deltaTilda(stare, word) == NULL)  //verific daca exista o legatura intre starea curenta si ultima litera a cuvantului dat
    {
        g<<"NU"<<endl;
        return;
    }
    else
    {
        int* w, j=0;
        w=deltaTilda(stare, word);
        while(w[j])
            {
            for(int k=0; k<nrStFin; k++)
                if(w[j] == stFin[k])
                {
                    g<<"DA"<<endl;
                    return;
                }
            j++;
            }
    }
    g<<"NU"<<endl;
    return;
}

int main()
{

    //citirea datelor din fisier
    f>>nrStari;
    for(int i=0; i<nrStari; i++)
        f>>stari[i];

    f>>nrLitere;
    for(int i=0; i <nrLitere; i++)
        f>>lit[i];

    f>>stInit;
    f>>nrStFin;
    for(int i=0; i<nrStFin; i++)
        f>>stFin[i];

    f>>nrTranz;
    int x, z;
    char y;
    for(int k=0; k<nrStari; k++)     //initializez cu 0 toate pozitiile
        for(int j=0; j<nrLitere; j++)
            tranz[k][j].i=0;

    for(int k=0; k<nrStari; k++)
    {
        //retin pe fiecare pozitie starile in care duce fiecare pereche de forma (stare, litera)
        f>>x>>y>>z;
        int j=tranz[x][y-'a'].i;
        tranz[x][y-'a'].v[j]=z;
        tranz[x][y-'a'].i++;
    }

    f>>nrCuv;
    for(int i=0; i<nrCuv; i++)
        f>>cuv[i];

    for(int i=0; i<nrCuv; i++)
    {
        //verific pentru fiecare cuvant
        char c[256];
        strcpy(c, cuv[i]);
        verif(stInit, c);
    }

    return 0;
}
