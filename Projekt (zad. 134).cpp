#include <iostream>
#include <conio.h>
#include "windows.h"



void gotoxy(int x, int y) // gotoxy -> funkcja której u¿y³em do ustawienia po³o¿enia kursora na ekranie
{
	COORD coord; // przypisanie symboli odpowiednim koordynatom:
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // funkcja deklaruj¹ce po³o¿enie
}

int wherex()
{

	CONSOLE_SCREEN_BUFFER_INFO csbi; // funkcja otrzymuj¹ca informacje o specyfikacji bufora i czyszcz¹ca ekran
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X; // zwrócenie po³o¿enia kursora w osi x
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y; // zwrócenie po³o¿enia kursora w osi y
}
const int GORA = 72, DOL = 80, LEWO = 75, PRAWO = 77; // sta³a deklaracja klawiszy do poruszania siê po ekranie
void Wstep();
void WczytajDane(float &size, char &znak);
void Rysuj(float size, float x, float y, char znak);
void Przesuwanie(float size, float &x, float &y, char znak);

using namespace std;

int main()
{
	float x = 1, y = 1; // okreœlenie pocz¹tkowego po³o¿enia
	float size;
	char znak; // zmienna typu char pozwala na dostêp do znaków ASCII
	system("cls");

	Wstep();
	WczytajDane(size, znak);
	Rysuj(size, x, y, znak);
	_getch();
	Przesuwanie(size, x, y, znak);

	return 0;
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



void WczytajDane(float &size, char &znak) // WPROWADZANIE DANYCH
{
	system("cls");
	int max = 23, min = 5, rozmiar;
	do
	{
		cout << "Podaj rozmiar figury z zakresu (5-23): ";
		cin >> rozmiar;
	} while (rozmiar < min || rozmiar > max); // ograniczenie wpisywanych wartoœci
	size = rozmiar;

	cout << "Podaj znak kodu ASCII: ";
	cin >> znak;

}



void Rysuj(float size, float x, float y, char znak) //RYSOWANIE
{
	float i, j;
	int k;
	
	system("cls");
	
	for (i = x, j = y + size, k = 0; k < (size / 2); i++, j--, k++)
	{
		gotoxy(i, j), cout << znak; // w prawo w górê - punkt zaczepienia
	}

	for (i = x, j = y + 1, k = 0; k < size; j++, k++) // pionowa kreska
	{
		gotoxy(i, j), cout << znak;
	}

	for (i = x + (size / 2), j = y + (size / 2), k = 0; k < (size / 2); i++, j++, k++)
	{
		gotoxy(i, j), cout << znak; // w prawo w dó³
	}
	for (i = x + size, j = y + 1, k = 0; k < size; j++, k++) // pionowa kreska
	{
		gotoxy(i, j), cout << znak;
	}

	gotoxy(15, 25), cout << "strzalki: przesuwanie; +/-: powieksz, pomniejsz; ESC: wyjscie";
}

//PRZESUWANIE I ZMIANA ROZMIARU FIGURY

void Przesuwanie(float size, float &x, float &y, char znak) // przesuwanie figury klawiszami strza³ek
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
			if (y > max - (size - 2))
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
			if (x > 80 - size)
			{
				x--;
				zmiana = 0;
			}
			break;
		}
		case '+': // powiêkszanie figury
		{
			size++; zmiana = 1;
			if (size < 5 || size > max)
			{
				size--; y--;
				zmiana = 0;
			}
			break;
		}

		case '-': // pomniejszanie figury
		{
			size--;
			zmiana = 1;
			if (size < 5 || size > max)
			{
				size++;
				zmiana = 0;
			}
			break;
		}

		}

		if (zmiana)
		{
			Rysuj(size, x, y, znak); zmiana = 0;
		}

	} while (klawisz != 27);

}

//---------------------------------------------------------------------------