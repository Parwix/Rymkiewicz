#include <iostream>
#include <conio.h>
#include "windows.h"

using namespace std;

void Wstep();
void WczytajDane(float &rozmiar, char &znak);
void Rysuj(float rozmiar, float x, float y, char znak);
void Przesuwanie(float rozmiar, float &x, float &y, char znak);
void gotoxy(int x, int y) // gotoxy -> funkcja której u¿y³em do ustawienia po³o¿enia kursora na ekranie
{
	COORD coord; // przypisanie symboli odpowiednim koordynatom:
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // funkcja deklaruj¹ce po³o¿enie pocz¹tkowe
}

int main()
{
	float x = 1, y = 1; // okreœlenie pocz¹tkowego po³o¿enia
	float rozmiar;
	char znak; // zmienna typu char pozwala na dostêp do znaków ASCII
	
	Wstep();
	WczytajDane(rozmiar, znak);
	Rysuj(rozmiar, x, y, znak);
	Przesuwanie(rozmiar, x, y, znak);
	
}

void Wstep()
{
	cout << "Witaj w programie, ktory narysuje figure \n"
		"	*     * \n"
		"	*     * \n"
		"	*     * \n"
		"	*  *  * \n"
		"	* * * * \n"
		"	*     * \n"
		"przy uzyciu znaku ASCII. \n"
		"Program ten umozliwia: \n"
		" -> wybor znaku kodu ASCII \n"
		" -> wczytanie poczatkowego rozmiaru figury \n"
		" -> przesuwanie figury po ekranie klawiszami strzalek \n"
		" -> powiekszanie i pomniejszanie figury przy pomocy przyciskow + i - \n"
		" -> ograniczenie przesuwania figury do rozmiaru ekranu \n"
		" ____________________________________________________________________ \n \n"
		" ABY PRZEJSC DALEJ NACISNIJ DOWOLNY KLAWISZ";

	_getch();
}



void WczytajDane(float &rozmiar, char &znak) // WPROWADZANIE DANYCH
{
	system("cls");
	int max = 23, min = 5;
	do
	{
		cout << "Podaj rozmiar figury z zakresu (5-23): ";
		cin >> rozmiar;
	} while (rozmiar < min || rozmiar > max); // ograniczenie wpisywanych wartoœci
	

	cout << "Podaj znak kodu ASCII: ";
	cin >> znak;

}



void Rysuj(float rozmiar, float x, float y, char znak) //RYSOWANIE
{
	float i = x, j = y;
	
	system("cls");
	int xx = 0;
	int yy = rozmiar;
	
	for (int z = i; z <= (i + rozmiar); z++)
	{
		gotoxy(i , j + xx), cout << znak;
		gotoxy(i + yy, j + xx), cout << znak;
		xx++;
	}

	for (int z = i; z <= (i + rozmiar / 2); z++)
	{
		gotoxy(i + xx - 1, j + yy), cout << znak;
		
		xx--;
		yy--;	

	}
	for (int z = i; z <= (i + rozmiar / 2); z++)
	{
		gotoxy(i + yy + 1, j + xx), cout << znak;

		xx++;
		yy--;
		

	}
	

	
}

//PRZESUWANIE I ZMIANA ROZMIARU FIGURY

const int GORA = 72, DOL = 80, LEWO = 75, PRAWO = 77; // sta³a deklaracja klawiszy do poruszania siê po ekranie

void Przesuwanie(float rozmiar, float &x, float &y, char znak) // przesuwanie figury klawiszami strza³ek
{
	int zmiana = 0, max = 23;
	char klawisz;

	do
	{
		klawisz = _getch();

		switch (klawisz)
		{
		case GORA:
		{
			y--; zmiana = 1;
			if (y < 1)
			{
				y++;
				zmiana = 0;
			}
			break;
		}

		case DOL:
		{
			y++; zmiana = 1;
			if (y > max - (rozmiar - 2))
			{
				y--;
				zmiana = 0;
			}
			break;
		}
		case LEWO:
		{
			x--; zmiana = 1;
			if (x < 1)
			{
				x++;
				zmiana = 0;
			}
			break;
		}
		case PRAWO:
		{
			x++; zmiana = 1;
			if (x > 79 - rozmiar)
			{
				x--;
				zmiana = 0;
			}
			break;
		}
		case '+': // powiêkszanie figury
		{
			rozmiar++; zmiana = 1;
			if (rozmiar < 5 || rozmiar > max)
			{
				rozmiar--; y--;
				zmiana = 0;
			}
			break;
		}

		case '-': // pomniejszanie figury
		{
			rozmiar--;
			zmiana = 1;
			if (rozmiar < 5 || rozmiar > max)
			{
				rozmiar++;
				zmiana = 0;
			}
			break;
		}

		}
		if (zmiana)
		{
			Rysuj(rozmiar, x, y, znak); zmiana = 0;
		}
	} 
	while (klawisz != 27);

}