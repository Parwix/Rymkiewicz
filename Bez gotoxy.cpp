
#include <iostream>
#include <conio.h>
using namespace std;

void wstep();
void rysunek();

int main()
{
	wstep();
	rysunek();

	return 0;
}

void wstep()
{
	cout << "Napisz program rysowania znakiem ponizszej figury:\n";
	cout << "    *     * \n";
	cout << "    *     * \n";
	cout << "    *     * \n";
	cout << "    *  *  * \n";
	cout << "    *     * \n";

	cout << endl;

	cout << "Program powinien umozliwiac:\n"
		<< " - Wybor znaku kodu ASII,\n"
		<< " - Wczytanie poczatkowych rozmiarow figury,\n"
		<< " - Zmiane wielkosci figury klawiszami '+' i '-',\n"
		<< " - Przesuwanie figury w czterech kierunkach za pomoca kursorow,\n"
		<< " - Ograniczenie przesuwania i rozmiarow figury do obszaru ekranu.\n";

	_getch();

	return;
}

void rysunek()
{
	int Size;
	char AsciiChar;

	system("cls");

	cout << "Podaj rozmiar: ";
	cin >> Size;
	cout << endl;
	cout << "Wprowadz znak kodu ASCII: ";
	cin >> AsciiChar;
	cout << endl;

	for (int wiersz = 1; wiersz <= Size; wiersz++)
	{
		for (int kolumna = 1; kolumna <= Size; kolumna++)
		{
			if (wiersz == kolumna || kolumna == (Size + 1) - wiersz)
			{
				cout << AsciiChar;
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	_getch();
	return;
}

