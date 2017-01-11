#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
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

void sunet()
{
    Beep(130.8,200);
    Beep(155.6,200);
    Beep(174.6,200);
    Beep(196,400);
    Beep(174.6,200);
    Beep(196,400);
}

void sunetCastigat()
{
    Beep(370,200);
    Beep(293.7,200);
    Beep(220,200);
    Beep(392,200);
    Beep(329.6,200);
    Beep(246.9,200);
    Beep(440,200);
}

void sunetPierdut()
{
    Beep(196,200);
    Beep(207.7,200);
    Beep(196,200);
    Beep(174.6,200);
    Beep(155.6,200);
    Beep(146.8,200);
    Beep(130.8,200);
}

unsigned int numarMine(unsigned int linie, unsigned int coloana, matrice a)
{
    unsigned int i,linieNoua,coloanaNoua,mine;
    mine=0;
    for (i=0;i<8;i++)
    {
        linieNoua=linie+directieLin[i];
        coloanaNoua=coloana+directieCol[i];
        if (linieNoua>=1 && linieNoua<=a.linii && coloanaNoua>=1 && coloanaNoua<=a.coloane)
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
        coloana=(rand()%tablaJoc.coloane)+1;
        if (linie!=linieStart && coloana!=coloanaStart && tablaJoc.val[linie][coloana]==0)
        {
            tablaJoc.val[linie][coloana]=-1;
            ++i;
        }
    }
    for (i=1;i<=tablaJoc.linii;i++)
        for (j=1;j<=tablaJoc.coloane;j++)
            if (tablaJoc.val[i][j]!=-1)
                tablaJoc.val[i][j]=numarMine(i,j,tablaJoc);
}

void afisareMine()
{
    unsigned int i,j;
    for (i=1;i<=tablaJoc.linii;i++)
        for (j=1;j<=tablaJoc.coloane;j++)
            if (tablaJoc.val[i][j]==-1)
                afisaj[i][j]=15;
}

void afisare()
{
    int i,j;
    system("cls");
    cout<<"  |";
    for (j=1;j<=tablaJoc.coloane;j++)
        cout<<j<<"|";
    cout<<endl;
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"--";
    cout<<"---";
    cout<<endl;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        cout<<i<<"| ";
        for (j=1;j<=tablaJoc.coloane;j++)
            cout<<afisaj[i][j]<<"|";
        cout<<endl;
    }
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"--";
    cout<<"---\n";
}

void deschide(unsigned int linie, unsigned int coloana)
{
    if (tablaJoc.val[linie][coloana]==-1)
    {
        jocTerminat=1;
        afisareMine();
        afisare();
        cout<<"AI PIERDUT !";
        sunetPierdut();
    }
    else
    {
        unsigned int linieNoua,coloanaNoua,i;
        afisaj[linie][coloana]=tablaJoc.val[linie][coloana]+'0';
        ++deschise;
        if (tablaJoc.val[linie][coloana]==0)
        {
            afisaj[linie][coloana]='-';
            for (i=0;i<8;i++)
            {
                linieNoua=linie+directieLin[i];
                coloanaNoua=coloana+directieCol[i];
                if ((linieNoua>=1 && linieNoua<=tablaJoc.linii) && (coloanaNoua>=1 && coloanaNoua<=tablaJoc.coloane))
                {
                    if (tablaJoc.val[linieNoua][coloanaNoua]!=-1 &&  afisaj[linieNoua][coloanaNoua]==254)
                    {
                        ++deschise;
                        afisaj[linieNoua][coloanaNoua]=tablaJoc.val[linieNoua][coloanaNoua]+'0';
                        if (tablaJoc.val[linieNoua][coloanaNoua]==0)
                        {
                            --deschise;
                            deschide(linieNoua,coloanaNoua);
                        }
                    }
                }
            }
        }
    }
}

void citire()
{
    cout<<"Numarul de linii :\n";cin>>tablaJoc.linii;
    while (cin.fail() || tablaJoc.linii>50 || tablaJoc.linii<=2)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Numarul de linii este invalid (trebuie sa apartina intervalului [2,50]). Introduceti din nou."<<endl;
        cin>>tablaJoc.linii;
    }
    cout<<"Numarul de coloane :\n";cin>>tablaJoc.coloane;
    while (cin.fail() || tablaJoc.coloane>50 || tablaJoc.coloane<=2)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Numarul de coloane este invalid (trebuie sa apartina intervalului [2,50]). Introduceti din nou."<<endl;
        cin>>tablaJoc.coloane;
    }
    cout<<"Numarul de mine , max "<<(tablaJoc.linii-1)*(tablaJoc.coloane-1)<<" :\n";
    cin>>nrMine;
    while (cin.fail() || nrMine>(tablaJoc.linii-1)*(tablaJoc.coloane-1))
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Numarul de mine este invalid. Maximul este "<<(tablaJoc.linii-1)*(tablaJoc.coloane-1)<<". Introduceti din nou."<<endl;
        cin>>nrMine;
    }
}

void meniu();

void joc()
{
    bool alegereBuna;
    char raspuns;
    unsigned int i,j,linie,coloana;
    system("cls");
    cout<<"  |";
    for (j=1;j<=tablaJoc.coloane;j++)
        cout<<j<<"|";
    cout<<endl;
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"--";
    cout<<"---";
    cout<<endl;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        cout<<i<<"| ";
        for (j=1;j<=tablaJoc.coloane;j++)
        {
            afisaj[i][j]=254;
            cout<<afisaj[i][j]<<"|";
        }
        cout<<endl;
    }
    for (j=1;j<=tablaJoc.coloane;j++)
            cout<<"--";
    cout<<"---\n";
    sunet();
    cout<<"Ce casuta doresti sa deschizi ?\n";
    cout<<"Linie :";
    cin>>linie;
    while (cin.fail() || linie>tablaJoc.linii || linie<=0)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Linie invalida. Introduceti din nou"<<endl;
        cin>>linie;
    }
    cout<<"Coloana :";
    cin>>coloana;
    while (cin.fail() || coloana>tablaJoc.coloane || coloana<=0)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Coloana invalida. Introduceti din nou"<<endl;
        cin>>coloana;
    }
    construiesteMatrice(linie,coloana);
    deschide(linie,coloana);
    while (!jocTerminat)
    {
        afisare();
        if (deschise==(tablaJoc.linii*tablaJoc.coloane)-nrMine)
        {
            cout<<"AI CASTIGAT !";
            sunetCastigat();
            break;
        }
        alegereBuna=0;
        while (!alegereBuna)
        {

            cout<<"Ce casuta doresti sa alegi ?\n";
            cout<<"Linie :";
            cin>>linie;
            while (cin.fail() || linie>tablaJoc.linii || linie<=0)
            {
                cin.clear();
                cin.ignore(100,'\n');
                cout<<"Linie invalida. Introduceti din nou"<<endl;
                cin>>linie;
            }
            cout<<"Coloana :";
            cin>>coloana;
            while (cin.fail() || coloana>tablaJoc.coloane || coloana<=0)
            {
                cin.clear();
                cin.ignore(100,'\n');
                cout<<"Coloana invalida. Introduceti din nou"<<endl;
                cin>>coloana;
            }
            cout<<"Deschizi/pui steag/scoti steag? d/f/u\n";
            cin>>raspuns;
            if (raspuns=='d'||raspuns=='D')
            {
                if (afisaj[linie][coloana]==239)
                    cout<<"Exista steag pe casuta aleasa. Alegeti alta.\n";
                else if (afisaj[linie][coloana]>='1' && afisaj[linie][coloana]<='9')
                    cout<<"Casuta data este deja deschisa. Alegeti alta.\n";
                else
                {
                    deschide(linie,coloana);
                    i++;
                    alegereBuna=1;
                }
            }
            else if (raspuns=='f'||raspuns=='F')
            {
                if (afisaj[linie][coloana]==254)
                {
                    afisaj[linie][coloana]=239;
                    alegereBuna=1;
                }
            }
            else if (raspuns=='u' || raspuns=='U')
            {

                if (afisaj[linie][coloana]==239)
                {
                    afisaj[linie][coloana]=254;
                    alegereBuna=1;
                }
                else
                    cout<<"Nu exista steag pe casuta selectata.Alegeti alta.\n";
            }
            else
                cout<<"Raspuns invalid.";
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
        jocTerminat=0;
        meniu();
    }
}

void meniu()
{
    char raspuns;
    /*cout<<" ------------------------------------------------------------------------------------------- "<<endl;
    cout<<"|  | \    / | || | \    || / ===  ==== \\              // / === / === | ==\\  / === | ==\\  |"<<endl;
    cout<<"|  ||\\  //|| || ||\\   || ||    ||     \\            //  ||    ||    ||   || ||    ||   || |"<<endl;
    cout<<"|  || \\// || || || \\  || | ===  ====   \\          //   | === | === | ==//  | === | ==//  |"<<endl;
    cout<<"|  ||      || || ||  \\ || ||        ||   \\  //\\  //    ||    ||    ||      ||    ||  \\  |"<<endl;
    cout<<"|  ||      || || ||   \  | \ ===  ====     \\//  \\//     \ === \ === ||      \ === ||   \\ |"<<endl;
    cout<<" ------------------------------------------------------------------------------------------- "<<endl;*/
    cout<<"      -----------------------"<<endl;
    cout<<"     |                       |"<<endl;
    cout<<"     |      MINESWEEPER      |"<<endl;
    cout<<"     |                       |"<<endl;
    cout<<"      -----------------------"<<endl;
    cout<<endl;
    cout<<"     Ce nivel de dificultate doriti ?"<<endl<<endl;
    cout<<"         1)Usor (9x9, 10 mine)"<<endl;
    cout<<"         2)Mediu (16x16, 40 de mine)"<<endl;
    cout<<"         3)Greu (16x30, 99 de mine)"<<endl;
    cout<<"         4)Custom"<<endl;
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
