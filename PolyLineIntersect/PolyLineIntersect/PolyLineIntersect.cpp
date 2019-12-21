#include "iostream"
#include <fstream>
#include "Interface.h"
#include "PolyLineFunctions.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
	PrintInfo();
	Interface();
	cout<<"Спасибо за работу с программой. Всего доброго!\n";
	// вывод системного приглашения нажать любую клавишу
	system("pause");
	return 0;
}