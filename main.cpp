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
    unsigned int linii,coloane;
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

void construiesteMatrice(unsigned int linieStart, unsigned int coloanaStart)
{
    unsigned int i,j,linie,coloana;
    srand(time(0));
    for (i=1;i<=nrMine;)
    {
        linie=(rand()%tablaJoc.linii)+1;
        coloana=(rand()%tablaJoc.linii)+1;
        if (linie!=linieStart && coloana!=coloanaStart && tablaJoc.val[linie][coloana]==0)
        {
            tablaJoc.val[linie][coloana]=-1;
            ++i;
        }
    }
    for (i=1;i<=tablaJoc.linii;i++)
        for (j=1;j<=tablaJoc.linii;j++)
            if (tablaJoc.val[i][j]!=-1)
                tablaJoc.val[i][j]=numarMine(i,j,tablaJoc);
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
        afisaj[linie][coloana]=tablaJoc.val[linie][coloana]+'0';
        ++deschise;
        if (tablaJoc.val[linie][coloana]==0)
        {
            afisaj[linie][coloana]=' ';
            for (i=0;i<8;i++)
            {
                linieNoua=linie+directieLin[i];
                coloanaNoua=coloana+directieCol[i];
                if ((linieNoua>=1 && linieNoua<=tablaJoc.linii) && (coloanaNoua>=1 && coloanaNoua<=tablaJoc.linii))
                {
                    if (tablaJoc.val[linieNoua][coloanaNoua]!=-1 &&  afisaj[linieNoua][coloanaNoua]==254)
                    {
                        ++deschise;
                        afisaj[linieNoua][coloanaNoua]=tablaJoc.val[linieNoua][coloanaNoua]+'0';
                        if (tablaJoc.val[linieNoua][coloanaNoua]==0)
                        {
                            --deschise;
                            //afisaj[linieNoua][coloanaNoua]=' ';
                            deschide(linieNoua,coloanaNoua);
                        }
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
    cout<<"  |";
    for (i=1;i<=tablaJoc.linii;i++)
        cout<<i<<" | ";
    cout<<endl;
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"----";
    cout<<"--";
    cout<<endl;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        cout<<i<<"| ";
        for (j=1;j<=tablaJoc.coloane;j++)
            cout<<afisaj[i][j]<<" | ";
        cout<<endl;
    }
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"----";
    cout<<"--\n";
}

void citire()
{
    cout<<"Numarul de linii :\n";cin>>tablaJoc.linii;
    cout<<"Numarul de coloane :\n";cin>>tablaJoc.coloane;
    while (tablaJoc.linii>50 || tablaJoc.coloane>50)
    {
        cout<<"Numarul de linii sau de coloane nu are voie sa depaseasca 50. Reintroduceti.\n";
        cout<<"Numarul de linii :\n";cin>>tablaJoc.linii;
        cout<<"Numarul de coloane :\n";cin>>tablaJoc.coloane;
    }
    cout<<"Numarul de mine , max "<<(tablaJoc.linii-1)*(tablaJoc.coloane-1)<<" :\n";
    cin>>nrMine;
    while (nrMine>(tablaJoc.linii-1)*(tablaJoc.coloane-1))
    {
        cout<<"Numarul de mine este prea mare. Introduceti din nou \n";
        cin>>nrMine;
    }
}

void meniu();

void joc()
{
    bool alegereBuna;
    char raspuns,linie,coloana;
    unsigned int i,j,valoareLinie,valoareColoana;
    system("cls");
    cout<<"  |";
    for (i=1;i<=tablaJoc.linii;i++)
        cout<<i<<" | ";
    cout<<endl;
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"----";
    cout<<"--";
    cout<<endl;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        cout<<i<<"| ";
        for (j=1;j<=tablaJoc.coloane;j++)
        {
            afisaj[i][j]=254;
            cout<<afisaj[i][j]<<" | ";
        }
        cout<<endl;
    }
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"----";
    cout<<"--\n";
    cout<<"Ce casuta doresti sa deschizi ?";
    cin>>linie>>coloana;
    valoareLinie=linie-'0';
    valoareColoana=coloana-'0';
    while (valoareLinie>tablaJoc.linii || valoareColoana>tablaJoc.coloane || valoareLinie<=0 || valoareColoana<=0)
            {
                cout<<"Pozitia introdusa este in afara matricei. Alegeti alta.\n";
                cin>>linie>>coloana;
                valoareLinie=linie-'0';
                valoareColoana=coloana-'0';
            }
    construiesteMatrice(valoareLinie,valoareColoana);
    deschide(valoareLinie,valoareColoana);
    while (!jocTerminat)
    {
        afisare();
        if (deschise==(tablaJoc.linii*tablaJoc.coloane)-nrMine)
        {
            cout<<"AI CASTIGAT !";
            break;
        }
        alegereBuna=0;
        while (!alegereBuna)
        {

            cout<<"Pozitia : linie coloana\n";
            cin>>linie>>coloana;
            valoareLinie=linie-'0';
            valoareColoana=coloana-'0';
            while (valoareLinie>tablaJoc.linii || valoareColoana>tablaJoc.coloane || valoareLinie<=0 || valoareColoana<=0)
            {
                cout<<"Pozitia introdusa este in afara matricei. Alegeti alta.\n";
                cin>>linie>>coloana;
                valoareLinie=linie-'0';
                valoareColoana=coloana-'0';
            }
            cout<<"Deschizi/pui steag/scoti steag? d/f/u\n";
            cin>>raspuns;
            if (raspuns=='d'||raspuns=='D')
            {
                if (afisaj[valoareLinie][valoareColoana]==239)
                    cout<<"Exista steag pe casuta aleasa. Alegeti alta.\n";
                else if (afisaj[valoareLinie][valoareColoana]>='1' && afisaj[valoareLinie][valoareColoana]<='9')
                    cout<<"Casuta data este deja deschisa. Alegeti alta.\n";
                else
                {
                    deschide(valoareLinie,valoareColoana);
                    i++;
                    alegereBuna=1;
                }
            }
            else if (raspuns=='f'||raspuns=='F')
            {
                if (afisaj[valoareLinie][valoareColoana]==255)
                {
                    afisaj[valoareLinie][valoareColoana]=239;
                    alegereBuna=1;
                }
            }
            else
            {

                if (afisaj[valoareLinie][valoareColoana]==239)
                {
                    afisaj[valoareLinie][valoareColoana]=254;
                    alegereBuna=1;
                }
                else
                    cout<<"Nu exista steag pe casuta selectata.Alegeti alta.\n";
            }
        }
    }
    cout<<"\nDoriti sa jucati din nou ? d/n\n";
    cin>>raspuns;
    while (raspuns !='d' && raspuns!='n')
    {
        cout<<"Raspunsul nu este corect. Introduceti din nou"<<endl;
        cin>>raspuns;
    }
    if (raspuns=='d')
    {
        system("cls");
        meniu();
    }
}

void meniu()
{
    char raspuns;
    cout<<" ------------------------------------------------------------------------------------------- "<<endl;
    cout<<"|  | \    / | || | \    || / ===  ==== \\              // / === / === | ==\\  / === | ==\\  |"<<endl;
    cout<<"|  ||\\  //|| || ||\\   || ||    ||     \\            //  ||    ||    ||   || ||    ||   || |"<<endl;
    cout<<"|  || \\// || || || \\  || | ===  ====   \\          //   | === | === | ==//  | === | ==//  |"<<endl;
    cout<<"|  ||      || || ||  \\ || ||        ||   \\  //\\  //    ||    ||    ||      ||    ||  \\  |"<<endl;
    cout<<"|  ||      || || ||   \  | \ ===  ====     \\//  \\//     \ === \ === ||      \ === ||   \\ |"<<endl;
    cout<<" ------------------------------------------------------------------------------------------- "<<endl;
    cout<<endl;
    cout<<"Ce nivel de dificultate doriti ?"<<endl<<endl;
    cout<<"     1)Beginner (9x9, 10 mine)"<<endl;
    cout<<"     2)Intermediate (16x16, 40 de mine)"<<endl;
    cout<<"     3)Advanced (16x30, 99 de mine)"<<endl;
    cout<<"     4)Custom"<<endl;
    cin>>raspuns;
    while (raspuns<'1'||raspuns>'4')
    {
        cout<<"Raspunsul nu este valid. Introduceti din nou.";
        cin>>raspuns;
    }
    switch (raspuns)
    {
        case '1': {
                    tablaJoc.linii=9;
                    tablaJoc.coloane=9;
                    nrMine=10;
                    break;
                  }
        case '2':{
                    tablaJoc.linii=16;
                    tablaJoc.coloane=16;
                    nrMine=40;
                    break;
                  }
        case '3':{
                    tablaJoc.linii=16;
                    tablaJoc.coloane=30;
                    nrMine=99;
                    break;
                  }
        case '4':{
                    citire();
                    break;
                  }
    }
    joc();
}

int main()
{
    meniu();
    return 0;
}
