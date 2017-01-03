#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

int directieLin[]={-1,-1,-1,0,0,1,1,1},directieCol[]={-1,0,1,-1,1,-1,0,1};
bool jocTerminat=0;
unsigned int nrMine,deschise=0;

struct matrice
{
    unsigned int linii;
    int val[51][51];
}tablaJoc;

unsigned char afisaj[51][51];

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

void construiesteMatrice()
{
    unsigned int i,j,linie,coloana;
    srand(time(0));
    for (i=1;i<=nrMine;i++)
    {
        linie=rand()%tablaJoc.linii+1;
        coloana=rand()%tablaJoc.linii+1;
        tablaJoc.val[linie][coloana]=-1;
    }
    for (i=1;i<=tablaJoc.linii;i++)
        for (j=1;j<=tablaJoc.linii;j++)
        {
            afisaj[i][j]=254;
            if (tablaJoc.val[i][j]!=-1)
                tablaJoc.val[i][j]=numarMine(i,j,tablaJoc);
        }
}

void deschide(unsigned int linie, unsigned int coloana)
{
    if (tablaJoc.val[linie][coloana]==-1)
    {
        afisaj[linie][coloana]=15;
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
                if (tablaJoc.val[linieNoua][coloanaNoua]!=-1 &&  afisaj[linieNoua][coloanaNoua]==254)
                {
                    ++deschise;
                    afisaj[linieNoua][coloanaNoua]=tablaJoc.val[linieNoua][coloanaNoua]+'0';
                    if (tablaJoc.val[linieNoua][coloanaNoua]==0)
                    {
                        afisaj[linieNoua][coloanaNoua]=' ';
                        deschide(linieNoua,coloanaNoua);
                    }
                }
            }
        }
    }
}

void afisare()
{
    int i,j;
    system("cls");
    for (i=1;i<=tablaJoc.linii;i++)
    {
        for (j=1;j<=tablaJoc.linii;j++)
            cout<<afisaj[i][j]<<" ";
        cout<<endl;
    }
    cout<<deschise;
}

void citire()
{
    cout<<"Nr. linii :\n";cin>>tablaJoc.linii;
    cout<<"Nr. mine , max "<<(tablaJoc.linii-1)*(tablaJoc.linii-1)<<" :\n";
    cin>>nrMine;
    while (nrMine>(tablaJoc.linii-1)*(tablaJoc.linii-1))
    {
        cout<<"Numarul de mine este prea mare. Introduceti din nou \n";
        cin>>nrMine;
    }
}

void joc()
{
    char raspuns;
    unsigned int i,linie,coloana;
    citire();
    construiesteMatrice();
    for (i=1;i<=tablaJoc.linii-nrMine && !jocTerminat && deschise!=tablaJoc.linii-nrMine;)
    {
        afisare();
        cout<<"Pozitia : linie coloana\n";
        cin>>linie>>coloana;
        cout<<"Deschizi/pui steag/scoti steag? d/f/u";
        cin>>raspuns;
        if (raspuns=='d'||raspuns=='D')
        {
            deschide(linie,coloana);
            i++;
        }
        else if (raspuns=='f'||raspuns=='F')
            afisaj[linie][coloana]=239;
        else
            afisaj[linie][coloana]=254;
    }
    if (deschise==tablaJoc.linii-nrMine)
        cout<<"AI CASTIGAT !";
}

int main()
{
    joc();
    return 0;
}
