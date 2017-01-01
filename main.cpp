#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

int directieLin[]={-1,-1,-1,0,0,1,1,1},directieCol[]={-1,0,1,-1,1,-1,0,1};
bool jocTerminat=0;

struct matrice
{
    unsigned int linii;
    int val[51][51];
}tablaJoc;

char afisaj[51][51];

unsigned int randomizare(matrice a)
{
    srand(time(0));
    return (rand()%a.linii + 1);
}

unsigned int numarMine(unsigned int linie, unsigned int coloana, matrice a)
{
    unsigned int i,linieNoua,coloanaNoua,mine;
    mine=0;
    for (i=0;i<8;i++)
    {
        linieNoua=linie+directieLin[i];
        coloanaNoua=coloana+directieCol[i];
        if (linieNoua>=1 && linieNoua<=a.linii && coloanaNoua>=1 && coloanaNoua<=a.linii)
            if (a.val[linieNoua][coloanaNoua]==-1)
                ++mine;
    }
    return mine;
}

void construiesteMatrice(unsigned int nrMine)
{
    unsigned int i,j,linie,coloana;
    for (i=1;i<=nrMine;i++)
    {
        linie=randomizare(tablaJoc);
        coloana=randomizare(tablaJoc);
        tablaJoc.val[linie][coloana]=-1;
    }
    for (i=1;i<=tablaJoc.linii;i++)
        for (j=1;j<=tablaJoc.linii;j++)
        {
            afisaj[i][j]=char(254);
            if (tablaJoc.val[i][j]!=-1)
                tablaJoc.val[i][j]=numarMine(i,j,tablaJoc);
        }
}

void deschide(unsigned int linie, unsigned int coloana)
{
    if (tablaJoc.val[linie][coloana]==-1)
    {
        afisaj[linie][coloana]=char(15);
        jocTerminat=1;
        cout<<"AI PIERDUT !";
    }
    else
    {
        unsigned int linieNoua,coloanaNoua,i;
        for (i=0;i<8;i++)
        {
            linieNoua=linie+directieLin[i];
            coloanaNoua=coloana+directieCol[i];
            if (linieNoua>=1 && linieNoua<=tablaJoc.linii && coloanaNoua>=1 && coloanaNoua<=tablaJoc.linii)
            {
                if (tablaJoc.val[linieNoua][coloanaNoua]!=-1)
                {
                    afisaj[linieNoua][coloanaNoua]=tablaJoc.val[linieNoua][coloanaNoua]+'0';
                    if (tablaJoc.val[linieNoua][coloanaNoua]==0)
                        deschide(linieNoua,coloanaNoua);
                }
            }
        }
    }
}

void afisare()
{
    int i,j;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        for (j=1;j<=tablaJoc.linii;j++)
            cout<<afisaj[i][j]<<" ";
        cout<<endl;
    }
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
