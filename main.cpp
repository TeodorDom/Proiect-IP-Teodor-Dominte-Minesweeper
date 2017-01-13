#define COL_MAX 26
#define LIN_MAX 41

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
    int val[LIN_MAX][COL_MAX];
}tablaJoc;

unsigned char afisaj[LIN_MAX][COL_MAX];

void meniuRo();

void meniuEn();

void meniuLimba();

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
        if ((linie!=linieStart || coloana!=coloanaStart) && tablaJoc.val[linie][coloana]==0)
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
    if (tablaJoc.linii>9)
        cout<<" ";
    cout<<" |";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9 && j<=9)
            cout<<" ";
        cout<<j<<"|";
    }
    cout<<endl;
    if (tablaJoc.linii>9 && tablaJoc.coloane<=9)
        cout<<"-";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9)
            cout<<"-";
        cout<<"-+";
    }
    if (tablaJoc.coloane<=9)
        cout<<"-+";
    else
        cout<<"--+";
    cout<<endl;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        if (tablaJoc.linii>9 && i<=9)
            cout<<" ";
        cout<<i<<"|";
        for (j=1;j<=tablaJoc.coloane;j++)
        {
            if (tablaJoc.coloane>9)
                cout<<" ";
            cout<<afisaj[i][j]<<"|";
        }
        cout<<endl;
    }
    if (tablaJoc.linii>9 && tablaJoc.coloane<=9)
        cout<<"-";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9)
            cout<<"-";
        cout<<"--";
    }
    if (tablaJoc.coloane<=9)
        cout<<"-+\n";
    else
        cout<<"--+\n";
}

void deschide(unsigned int linie, unsigned int coloana, unsigned char limba)
{
    if (tablaJoc.val[linie][coloana]==-1)
    {
        jocTerminat=1;
        afisareMine();
        afisare();
        if (limba=='e')
            cout<<"YOU LOST !"<<endl;
        else
            cout<<"AI PIERDUT !"<< endl;
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
                            deschide(linieNoua,coloanaNoua,limba);
                        }
                    }
                }
            }
        }
    }
}

void citireRo()
{
    cout<<"Numarul de linii :\n";cin>>tablaJoc.linii;
    while (cin.fail() || tablaJoc.linii>40 || tablaJoc.linii<=2)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Numarul de linii este invalid (trebuie sa apartina intervalului [3,40]). Introduceti din nou."<<endl;
        cin>>tablaJoc.linii;
    }
    cout<<"Numarul de coloane :\n";cin>>tablaJoc.coloane;
    while (cin.fail() || tablaJoc.coloane>25 || tablaJoc.coloane<=2)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Numarul de coloane este invalid (trebuie sa apartina intervalului [3,25]). Introduceti din nou."<<endl;
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

void citireEn()
{
    cout<<"Number of lines :\n";cin>>tablaJoc.linii;
    while (cin.fail() || tablaJoc.linii>40 || tablaJoc.linii<=2)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"The number of lines you chose is not valid (it has to be between 3 and 40). Please try again."<<endl;
        cin>>tablaJoc.linii;
    }
    cout<<"Number of columns :\n";cin>>tablaJoc.coloane;
    while (cin.fail() || tablaJoc.coloane>25 || tablaJoc.coloane<=2)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"The number of columns you chose is not valid (it has to be between 3 and 25). Please try again."<<endl;
        cin>>tablaJoc.coloane;
    }
    cout<<"Number of mines , maximum "<<(tablaJoc.linii-1)*(tablaJoc.coloane-1)<<" :\n";
    cin>>nrMine;
    while (cin.fail() || nrMine>(tablaJoc.linii-1)*(tablaJoc.coloane-1))
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"The number of mines you chose is not valid. The maximum is "<<(tablaJoc.linii-1)*(tablaJoc.coloane-1)<<". Please try again."<<endl;
        cin>>nrMine;
    }
}

void jocRo()
{
    unsigned int mine;
    bool alegereBuna;
    char raspuns;
    unsigned int i,j,linie,coloana;
    system("cls");
    mine=nrMine;
    if (tablaJoc.linii>9)
        cout<<" ";
    cout<<" |";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9 && j<=9)
            cout<<" ";
        cout<<j<<"|";
    }
    cout<<endl;
    if (tablaJoc.linii>9 && tablaJoc.coloane<=9)
        cout<<"-";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9)
            cout<<"-";
        cout<<"-+";
    }
    if (tablaJoc.coloane<=9)
        cout<<"-+";
    else
        cout<<"--+";
    cout<<endl;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        if (tablaJoc.linii>9 && i<=9)
            cout<<" ";
        cout<<i<<"|";
        for (j=1;j<=tablaJoc.coloane;j++)
        {
            afisaj[i][j]=254;
            if (tablaJoc.coloane>9)
                cout<<" ";
            cout<<afisaj[i][j]<<"|";
        }
        cout<<endl;
    }
    if (tablaJoc.linii>9 && tablaJoc.coloane<=9)
        cout<<"-";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9)
            cout<<"-";
        cout<<"--";
    }
    if (tablaJoc.coloane<=9)
        cout<<"-+\n";
    else
        cout<<"--+\n";
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
    deschide(linie,coloana,'r');
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
        cout<<"Au mai ramas "<<mine<<" mine."<<endl<<endl;
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
            if (afisaj[linie][coloana]!=254 && afisaj[linie][coloana]!=239)
                cout<<"Casuta aleasa este deja deschisa. Introduceti din nou.\n";
            else
            {
                if (raspuns=='d'||raspuns=='d')
                {
                        deschide(linie,coloana,'r');
                        i++;
                        alegereBuna=1;
                }
                else if (raspuns=='f'||raspuns=='F')
                {
                    if (mine!=0)
                    {
                        --mine;
                        afisaj[linie][coloana]=239;
                        alegereBuna=1;
                    }
                    else
                        cout<<"Numarul de mine este 0, deci nu mai puteti pune flaguri.\n";
                }
                else if (raspuns=='u' || raspuns=='U')
                {

                    if (afisaj[linie][coloana]==239)
                    {
                        ++mine;
                        afisaj[linie][coloana]=254;
                        alegereBuna=1;
                    }
                    else
                        cout<<"Exista un steag pe casuta selectata. Introduceti din nou.\n";
                }
                else
                    cout<<"Raspunsul este invalid. Introduceti din nou. \n";
            }
        }
    }
    cout<<"\nDoriti sa jucati din nou ? d/n\n";
    cin>>raspuns;
    while (raspuns !='d' && raspuns!='n')
    {
        cout<<"Raspunsul nu este corect. Introduceti din nou"<<endl;
        cin.ignore(100,'\n');
        cin>>raspuns;
    }
    if (raspuns=='d')
    {
        system("cls");
        jocTerminat=0;
        meniuRo();
    }
}

void jocEn()
{
    unsigned int mine;
    bool alegereBuna;
    char raspuns;
    unsigned int i,j,linie,coloana;
    system("cls");
    mine=nrMine;
    if (tablaJoc.linii>9)
        cout<<" ";
    cout<<" |";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9 && j<=9)
            cout<<" ";
        cout<<j<<"|";
    }
    cout<<endl;
    if (tablaJoc.linii>9 && tablaJoc.coloane<=9)
        cout<<"-";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9)
            cout<<"-";
        cout<<"-+";
    }
    if (tablaJoc.coloane<=9)
        cout<<"-+";
    else
        cout<<"--+";
    cout<<endl;
    for (i=1;i<=tablaJoc.linii;i++)
    {
        if (tablaJoc.linii>9 && i<=9)
            cout<<" ";
        cout<<i<<"|";
        for (j=1;j<=tablaJoc.coloane;j++)
        {
            afisaj[i][j]=254;
            if (tablaJoc.coloane>9)
                cout<<" ";
            cout<<afisaj[i][j]<<"|";
        }
        cout<<endl;
    }
    if (tablaJoc.linii>9 && tablaJoc.coloane<=9)
        cout<<"-";
    for (j=1;j<=tablaJoc.coloane;j++)
    {
        if (tablaJoc.coloane>9)
            cout<<"-";
        cout<<"--";
    }
    if (tablaJoc.coloane<=9)
        cout<<"-+\n";
    else
        cout<<"--+\n";
    sunet();
    cout<<"What square would you like to open ?\n";
    cout<<"Line :";
    cin>>linie;
    while (cin.fail() || linie>tablaJoc.linii || linie<=0)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"The line you entered isn't valid. Please try again.\n"<<endl;
        cin>>linie;
    }
    cout<<"Column :";
    cin>>coloana;
    while (cin.fail() || coloana>tablaJoc.coloane || coloana<=0)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"The column you entered isn't valid. Please try again.\n"<<endl;
        cin>>coloana;
    }
    construiesteMatrice(linie,coloana);
    deschide(linie,coloana,'e');
    while (!jocTerminat)
    {
        afisare();
        if (deschise==(tablaJoc.linii*tablaJoc.coloane)-nrMine)
        {
            cout<<"YOU WON !";
            sunetCastigat();
            break;
        }
        alegereBuna=0;
        cout<<"There are "<<mine<<" mines left."<<endl<<endl;;
        while (!alegereBuna)
        {

            cout<<"What square would you like to choose ?\n";
            cout<<"Line :";
            cin>>linie;
            while (cin.fail() || linie>tablaJoc.linii || linie<=0)
            {
                cin.clear();
                cin.ignore(100,'\n');
                cout<<"The line you entered isn't valid. Please try again.\n"<<endl;
                cin>>linie;
            }
            cout<<"Column :";
            cin>>coloana;
            while (cin.fail() || coloana>tablaJoc.coloane || coloana<=0)
            {
                cin.clear();
                cin.ignore(100,'\n');
                cout<<"The column you entered isn't valid. Please try again.\n"<<endl;
                cin>>coloana;
            }
            cout<<"Would you like to open/flag/unflag the square ? o/f/u\n";
            cin>>raspuns;
            if (afisaj[linie][coloana]!=254 && afisaj[linie][coloana]!=239)
                cout<<"The square you chose is already open . Please try again.\n";
            else
            {
                if (raspuns=='o'||raspuns=='O')
                {
                        deschide(linie,coloana,'e');
                        i++;
                        alegereBuna=1;
                }
                else if (raspuns=='f'||raspuns=='F')
                {
                    if (mine!=0)
                    {
                        --mine;
                        afisaj[linie][coloana]=239;
                        alegereBuna=1;
                    }
                    else
                        cout<<"There are no mines left to flag.\n";
                }
                else if (raspuns=='u' || raspuns=='U')
                {

                    if (afisaj[linie][coloana]==239)
                    {
                        ++mine;
                        afisaj[linie][coloana]=254;
                        alegereBuna=1;
                    }
                    else
                        cout<<"There is no flag on the chosen square. Please try again.\n";
                }
                else
                    cout<<"Your answer is not valid. Please try again. \n";
            }
        }
    }
    cout<<"\nWould you like to play again ? y/n\n";
    cin>>raspuns;
    while (raspuns !='y' && raspuns!='n')
    {
        cout<<"Your answer is not valid. Please try again. \n"<<endl;
        cin.ignore(100,'\n');
        cin>>raspuns;
    }
    if (raspuns=='y')
    {
        system("cls");
        jocTerminat=0;
        meniuEn();
    }
}

void meniuRo()
{
    unsigned int raspuns;
    cout<<"  __  __  _                                                   "<<endl;
    cout<<" |  \\/  |(_) _ _   ___  _____ __ __ ___  ___  _ __  ___  _ _  "<<endl;
    cout<<" | |\\/| || || ' \\ / -_)(_-<\\ V  V // -_)/ -_)| '_ \\/ -_)| '_| "<<endl;
    cout<<" |_|  |_||_||_||_|\\___|/__/ \\_/\\_/ \\___|\\___|| .__/\\___||_|   "<<endl;
    cout<<"                                             |_|              "<<endl;
    cout<<endl;
    cout<<"     Ce nivel de dificultate doriti ?"<<endl<<endl;
    cout<<"         1)Usor (9x9, 10 mine)"<<endl;
    cout<<"         2)Mediu (16x16, 40 de mine)"<<endl;
    cout<<"         3)Greu (30x16, 99 de mine)"<<endl;
    cout<<"         4)Custom"<<endl;
    cout<<endl<<endl;
    cout<<"         0)Schimbare limba"<<endl;
    cin>>raspuns;
    while (cin.fail()||raspuns<0||raspuns>4)
    {
        cout<<"Raspunsul nu este valid. Introduceti din nou.";
        cin.clear();
        cin.ignore(100,'\n');
        cin>>raspuns;
    }
    switch (raspuns)
    {
        case 1: {
                    tablaJoc.linii=9;
                    tablaJoc.coloane=9;
                    nrMine=10;
                    break;
                  }
        case 2:{
                    tablaJoc.linii=16;
                    tablaJoc.coloane=16;
                    nrMine=40;
                    break;
                 }
        case 3:{
                    tablaJoc.linii=30;
                    tablaJoc.coloane=16;
                    nrMine=99;
                    break;
                 }
        case 4:{
                    citireRo();
                    break;
                 }
        case 0:{
                    meniuLimba();
                    break;
                 }
    }
    jocRo();
}

void meniuEn()
{
    unsigned int raspuns;
    cout<<"  __  __  _                                                   "<<endl;
    cout<<" |  \\/  |(_) _ _   ___  _____ __ __ ___  ___  _ __  ___  _ _  "<<endl;
    cout<<" | |\\/| || || ' \\ / -_)(_-<\\ V  V // -_)/ -_)| '_ \\/ -_)| '_| "<<endl;
    cout<<" |_|  |_||_||_||_|\\___|/__/ \\_/\\_/ \\___|\\___|| .__/\\___||_|   "<<endl;
    cout<<"                                             |_|              "<<endl;
    cout<<endl;
    cout<<"     What difficulty level would you like ?"<<endl<<endl;
    cout<<"         1)Beginner (9x9, 10 mines)"<<endl;
    cout<<"         2)Intermediate (16x16, 40 mines)"<<endl;
    cout<<"         3)Advanced (30x16, 99 mines)"<<endl;
    cout<<"         4)Custom"<<endl;
    cout<<endl<<endl;
    cout<<"         0)Change the language"<<endl;
    cin>>raspuns;
    while (cin.fail()||raspuns<0||raspuns>4)
    {
        cout<<"Your answer is not valid. Please try again.\n";
        cin.clear();
        cin.ignore(100,'\n');
        cin>>raspuns;
    }
    switch (raspuns)
    {
        case 1: {
                    tablaJoc.linii=9;
                    tablaJoc.coloane=9;
                    nrMine=10;
                    break;
                }
        case 2:{
                    tablaJoc.linii=16;
                    tablaJoc.coloane=16;
                    nrMine=40;
                    break;
                }
        case 3:{
                    tablaJoc.linii=30;
                    tablaJoc.coloane=16;
                    nrMine=99;
                    break;
                }
        case 4:{
                    citireEn();
                    break;
                }
        case 0:{
                    meniuLimba();
                    break;
               }
    }
    jocEn();

}

void meniuLimba()
{
    unsigned int raspuns;
    system("cls");
    cout<<"  __  __  _                                                   "<<endl;
    cout<<" |  \\/  |(_) _ _   ___  _____ __ __ ___  ___  _ __  ___  _ _  "<<endl;
    cout<<" | |\\/| || || ' \\ / -_)(_-<\\ V  V // -_)/ -_)| '_ \\/ -_)| '_| "<<endl;
    cout<<" |_|  |_||_||_||_|\\___|/__/ \\_/\\_/ \\___|\\___|| .__/\\___||_|   "<<endl;
    cout<<"                                             |_|              "<<endl;
    cout<<endl;
    cout<<"         Alegeti limba / Choose your language :\n";
    cout<<"             1)Romana\n";
    cout<<"             2)English\n";
    cin>>raspuns;
    while (cin.fail()||raspuns<1||raspuns>2)
    {
        cout<<"Your answer is not valid. Please try again.\n";
        cin.clear();
        cin.ignore(100,'\n');
        cin>>raspuns;
    }
    switch(raspuns)
    {
        case 1: {
                    system("cls");
                    meniuRo();
                    break;
                  }
        case 2: {
                    system("cls");
                    meniuEn();
                    break;
                  }
    }
}

int main()
{
    meniuLimba();
    return 0;
}
