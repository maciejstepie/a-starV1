// a gwiazdka.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h" // ??? co ?

// Na pocz¹tek zak³adam, ¿e mapa o wymiarach 5x5 znajduje siê w pliku tekstowym
// "mapa.txt"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <windows.h> //Do testów funkcja Sleep()
using namespace std;

// globalne zmienne
const int wymiarMapyX = 5;
const int wymiarMapyY = 5;
const int wymiarMapy = wymiarMapyX * (wymiarMapyY + 1); // nvm ale przy 25 obcina jedn¹ liniê
const int wymiarMapyFixed = wymiarMapyX * wymiarMapyY;

// Mapy
string Mapa[wymiarMapy]; // Tu wczytywane sa dane z pliku
string MapaStart[wymiarMapyX][wymiarMapyY]; // Startowa mapa po uporzadkowaniu
string MapaH[wymiarMapyX][wymiarMapyY]; // Mapa po znalezieniu odleg³oœci
bool MapaSprawdzane[wymiarMapyX][wymiarMapyY] = { false }; // Startowa mapa po uporzadkowaniu
string MapaHValue[wymiarMapyX][wymiarMapyY]; // Mapa po wpisaniu odleglosci,
// funkcja H
int IloscKrokow[wymiarMapyX][wymiarMapyY]; // Ile krokow od celu
bool ByloLewo[wymiarMapyX][wymiarMapyY] = { false };
int IloscSprawdzen[wymiarMapyX][wymiarMapyY];
string MapaDroga[wymiarMapyX][wymiarMapyY]; // Finalna Mapa ze znaleziona opt Droga
string MapaFValue[wymiarMapyX][wymiarMapyY]; // koszty + odleglosc

int pX[wymiarMapyX][wymiarMapyY];
int pY[wymiarMapyX][wymiarMapyY];
// Punkty
int startX = 3;
int startY = 1;

int celX = 0;
int celY = 4;

int terazX = celX;
int terazY = celY;

int slepeUliczki = 0;
int lastKrokow = 0;
int ZnalezionoDrog = 0;
int celKoszt = 99;

int kierunek[4] = { 1, 1, -1, -1 };



string FunkcjaF(int i, int j)
{
    // cout << "? dobrze dziala"<< endl;
    int hh = atoi(MapaH[j][i].c_str());
    int gg = IloscKrokow[j][i];
    // cout <<"|h:" << hh <<"g:" << gg<< "|" ;

    ostringstream ss;
    ss << gg + hh;
    string str = ss.str();

    if (gg > 0)
        return str;
    else
        return "0";
}
void WyswietlD()
{
	int tempX =startX;
	int tempY = startY;
	
	
    for(int i= 0;i< celKoszt ;i++){
    	
    	
    	
	}
}
void WyswietlP()
{
    cout << "Parenty (P)..." << endl;
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j < 5; j++)
        {
            // atoi( MapaH[j][i].c_str() )
            cout << " (" << pY[i][j] << "," << pX[i][j] << ")"; // Wyswietlanie do testow
        }
        cout << endl;
    }
}
void WyswietlS()
{
    cout << endl << "Ilosc sprawdzen (S)..." << endl;
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j < 5; j++)
        {

            cout << " (" << j << "," << i << ")" << IloscSprawdzen[i][j]; // Wyswietlanie do testow
        }
        cout << endl;
    }
}
void WyswietlF()
{
    cout << endl << "Koszty drogi + odleglosc (F)..." << endl;
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j < 5; j++)
        {

            cout << " (" << j << "," << i << ")" << FunkcjaF(i, j); // Wyswietlanie do testow
        }
        cout << endl;
    }
}
void WyswietlG()
{
    cout << endl << "Ilosc Krokow (G)..." << endl;
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " (" << j << "," << i << ")" << IloscKrokow[j][i]; // Wyswietlanie do testow
        }
        cout << endl;
    }
}

void WyswietlH()
{
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " (" << j << "," << i << ")" << MapaH[j][i]; // Wyswietlanie do testow
        }
        cout << endl;
    }
}
void OgarnijMape()
{
    cout << "Wczytano mape... " << endl;
    int z = 0; // Potrzebna zmienna
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j <= 4; j++)
        {
            MapaStart[j][i] = Mapa[z];
            MapaH[j][i] = Mapa[z]; // Kopia do funkcji H
             cout << " (" << j << "," << i << ")" << MapaStart[j][i]; //
            // Wyswietlanie do testow
            z++;
        }
        cout << endl;
    }
}

void WczytywanieMapy()
{

    ifstream myfile("mapa.txt");

    if (myfile.is_open())
    { // Jezeli udalo sie otworzyc
        char temp; // Przechowuje chwilowo char
        int i = 0;
        while (!myfile.eof())
        {

            myfile.get(temp); // reading single character from file to array

            if (temp != '\n' && i < wymiarMapyFixed)
            {
                if (temp != '\0')
                {
                    if (temp != ' ')
                    {
                        Mapa[i] = temp;

                        // if(i % 5 == 0 && i !=0)cout<<endl; // formatowanie do testow
                        // cout<<Mapa[i];
                        i++;
                    }
                }
            }
        }
        myfile.close();
    }
    else
    {
        cout << "B³ad pliku!" << endl;
    }
}

void FunkcjaH()
{
    // int a = 10;
    // char *intStr = itoa(a);
    // string str = string(intStr);
    std::string s3;
    cout << "Wyznaczanie odleglosci od celu z kazdego punktu (H)..." << endl;
    for (int i = 4; i >= 0; i--)
    {
        for (int j = 0; j < 5; j++)
        {
            // std::string s = std::to_string(abs((int)celX -
            // atoi(MapaStart[j][i].c_str())));
            // std::string s = std::to_string(abs((int)celX - j));
            // std::string s2 = std::to_string(abs((int)celY - i));

            s3 = (abs((int)celY - i) + abs((int)celX - j)) + 48;
            // if (MapaStart[j][i] == "x") cout << "dupa";
            if (MapaStart[j][i] != "x")
                MapaH[j][i] = s3;
        }
    }
}
void WyznaczKierunek()
{

    if (slepeUliczki == 0 || slepeUliczki == 2)
    {

        terazY += kierunek[slepeUliczki];
    }

    else
    {
        terazX += kierunek[slepeUliczki];
    }
}
void Parent(int x, int y)
{

    if (slepeUliczki == 0 || slepeUliczki == 2)
    {

        pX[x][y] = x;
        pY[x][y] = y - kierunek[slepeUliczki];
    }

    else
    {
        pX[x][y] = x - kierunek[slepeUliczki];
        pY[x][y] = y;
    }
}

bool GIT(int XX, int YY){
	if ( (XX > 4 || YY < 0))
	return true;
	else
	return false;
	
}
void SprawdzaKroki()
{

    if (lastKrokow < IloscKrokow[terazX][terazY])
        IloscKrokow[terazX][terazY] = lastKrokow;
    int iTemp;
    int tempZnal = 0;
    int najZnal = 54;

    int XX = terazX;
    int YY = terazY;

    // Sprawdzenie kosztów czy nie mog¹ byæ mniejsze
    for (iTemp = 0; iTemp < 4; iTemp++)
    {
        // Sleep(1);

        if (iTemp == 0 || iTemp == 2)
        {

            YY += kierunek[iTemp];
				
            if (  XX > 4 || YY < 0 )
            {
                cout << "PM-(0,2) "; // do testow
                YY -= kierunek[iTemp];
                continue;
            }
            if (IloscKrokow[XX][YY] > 0)
            {
                tempZnal = IloscKrokow[XX][YY];
                if (tempZnal <= najZnal){
                	najZnal = tempZnal;
                	Parent(terazX, YY);
				}
                    
            }

            YY -= kierunek[iTemp];
        }

        else
        {
            XX += kierunek[iTemp];
            if ( XX > 4 || YY < 0 )
            {
                cout << "PM-(1,3) "; // do testow
                XX -= kierunek[iTemp];
                continue;
            }
            if (IloscKrokow[XX][YY] > 0)
            {
                tempZnal = IloscKrokow[XX][YY];
                if (tempZnal <= najZnal){
                	najZnal = tempZnal;
                	Parent(XX, terazY);
				}
                    
            }
            XX -= kierunek[iTemp];
        }

        cout << najZnal << "|";
    }
    // Wyswietla najmniejsza znaleziona wokol liczbe krokow
    cout << "*" << najZnal << "*";
    cout << " -" << IloscKrokow[terazX][terazY] << "-";

    if (IloscKrokow[terazX][terazY] > najZnal)
    {
        lastKrokow = najZnal + 1;

        IloscKrokow[terazX][terazY] = lastKrokow;
    }
    else
    {

        lastKrokow += 1;
        IloscKrokow[terazX][terazY] = lastKrokow;
    }
}

void Powrot()
{

    if (slepeUliczki == 0 || slepeUliczki == 2)
        terazY -= kierunek[slepeUliczki];
    else
        terazX -= kierunek[slepeUliczki];

    if (slepeUliczki == 3)
    {
        slepeUliczki = 0;
        cout << "| Przeszukuje od nowa wokol...";
    }

    else
        slepeUliczki += 1;
}
void PowrotSprawdzane()
{

    cout << " |Bylo sprawdzane";

    if (slepeUliczki == 0 || slepeUliczki == 2)
        terazY -= kierunek[slepeUliczki];
    else
        terazX -= kierunek[slepeUliczki];

    slepeUliczki += 1;
}

void CzyByloSprawdzane()
{

    if (MapaSprawdzane[terazX][terazY] != true)
    {
        MapaSprawdzane[terazX][terazY] = true;
        cout << " |Znaleziono przejscie... ";
        // Parent();
        if (slepeUliczki == 2 && MapaSprawdzane[terazX][terazY - 1] != true)
        {

            slepeUliczki = 1;
            SprawdzaKroki();
            return;
        }
        if (slepeUliczki > 0)
            slepeUliczki = 0;

        SprawdzaKroki();
    }
    else
    {
        if ((startX == terazX) && (startY == terazY))

            SprawdzaKroki();
        else
            PowrotSprawdzane();
    }
}
void NiePrzeszkoda()
{

    // Jezeli nie jest sciana to...
    if (MapaH[terazX][terazY].compare("x"))
    {

        CzyByloSprawdzane();
    }

    // Jezeli nie to...
    else
    {
        cout << " |Sciana: " << terazX << terazY;
        // IloscKrokow[terazX][terazY] = 99;
        Powrot();
    }
}
void FunkcjaG()
{

    lastKrokow = 0;
    terazX = celX;
    terazY = celY;

    MapaSprawdzane[terazX][terazY] = true;
    // Dopoki nie znajdzie startu bedzie przeszukiwac
    for (int i = 0; i < 4 * 25; i++)
    {

        // Jezeli sprawdzone zosta³y wszystkie kierunki to..
        if (slepeUliczki == 4)
        {
            slepeUliczki = 0;
            lastKrokow = 0;
            terazX = celX;
            terazY = celY;
        }
        // Jezeli znalaziono cel, pêtla siê koñczy
        if ((startX == terazX) && (startY == terazY))
        {
            cout << endl << " |Wyznaczono koszty jednej z drog!";
            celKoszt = IloscKrokow[startX][startY];
            break;
        }
        if (IloscKrokow[startX][startY] < lastKrokow)
        {
            cout << endl << "  Krotszej trasy juz nie bedzie!" << endl;
            break;
        }

        WyznaczKierunek(); // Wyznaczamy nastepny kierunek przeszukiwania
        cout << endl
             << " |Sprawdzam: "
             << "(" << terazX << "," << terazY << ")";
        if (IloscSprawdzen[terazX][terazY] > 3)
        {
            cout << "Looped!";
            SprawdzaKroki();
            continue;
        }
        IloscSprawdzen[terazX][terazY] += 1;

        // Jezeli jest w granicach mapy to...
        if ((terazX >= 0 && terazX <= 4) && (terazY >= 0 && terazY <= 4))
        {

            NiePrzeszkoda();
        }
        // Jezeli nie to...
        else
        {
            cout << " |Poza mapa: " << terazX << terazY;
            Powrot();
        }

    } // Koniec petli for
}

void PobierzCel()
{
    cout << " Podaj lokalizcje celu w formacie: x y" << endl;
    cin >> celX >> celY;
    MapaStart[celX][celY] = 67; // Litera C
    cout << " Wybrales Cel X: " << celX << " Y: " << celY << endl;
}
void PobierzStart()
{

    cout << " Podaj lokalizcje startu w formacie: x y" << endl;
    cin >> startX >> startY;
    MapaStart[startX][startY] = 83; // Litera S

    cout << " Wybrales Start X: " << startX << " Y: " << startY << endl;
}
int main(int argc, char** argv)
{
    WczytywanieMapy(); // Jak nazwa wskazuje
    OgarnijMape(); // Nadaj jej postac 2 wymiarowej tablicy
     PobierzCel(); //Prosi o wskazanie startu i celu
    // PobierzStart();
    FunkcjaH();
    //WyswietlH(); // Sprawdza co sie wsadzilo do arraya
    IloscKrokow[startX][startY] = 99; // ???? nie pamietam po co to tu ale dziala XDDD
    FunkcjaG();
    cout << endl << endl << " |Sprawdzam jescze raz mape dla pewnosci...";
    FunkcjaG();
    cout << endl << " Wyswietlam ilosc przeszukan...";
    // WyswietlS();
    WyswietlG();

    cout << endl << " Koszt najkrotszej trasy to: " << celKoszt << endl;
    // ??? po oc te f  ?
    // WyswietlF();
    // Wkoncu wyznaczy droge i zakonczy dzialanie tego programu;
    //WyswietlP();
    //WyswietlD();
    system("pause");
    return 0;
}
