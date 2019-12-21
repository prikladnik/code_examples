#include "iostream"
#include "Interface.h"
#include "PolyLine.h"
#include "UnitTest.h"
using namespace std;

void Interface()
{
	Poly mn, mn_div1, mn_div2;
	Line ln;	
	char choice;
	// объявляем тип для хранения выбранного пункта меню
	enum menuItemType {tExit, tInputPoly, tShowPoly, tInputLine, tShowLine, tCheckIntersect, tInputFromFile, tSaveToFile, tUnitTest, tNone};
	menuItemType menuItem = tNone;	
	// True - если соответствующий отрезок заполнен
	bool PolyIsFilled=false, LineIsFilled=false;
	while (!(menuItem == tExit)) {
		// вывод меню
		cout<<"\nМеню:\n";
		// возможно будет два файла с результатами: в одном исходный многоугольник, а в другом два полученных
		cout<<"1. Ввести кол-во вершин и координаты точек многоугольника\n";
		cout<<"2. Вывести координаты вершин многоугольника\n";
		cout<<"3. Ввести координаты прямой\n";
		cout<<"4. Вывести координаты прямой\n";
		cout<<"5. Проверить пересечение\n";
		cout<<"6. Прочитать данные из файла\n";
		cout<<"7. Сохранить данные в файл\n";
		cout<<"8. Выполнить функциональные тесты\n";
		cout<<"0. Выход из программы\n";
		cout<<"Введите пункт меню: ";
		cin.clear();
        cin.sync();
		cin>>choice;
		if ((choice>='0') && (choice <='8'))
			menuItem = (menuItemType)(choice - 48);
		else
			menuItem = tNone;
		switch (menuItem) {
			case tInputPoly:
				mn.ProcessInput();
				mn.Print();
				PolyIsFilled = true;
				break;
			case tShowPoly:
				cout<<"Многоугольник ";
				if (PolyIsFilled)
					mn.Print();
				else
					cout<<"не введен!\n";
				break;
			case tInputLine:
				ln.ProcessInput();
				ln.Print();
				LineIsFilled = true;
				break;
			case tShowLine:
				cout<<"Прямая ";
				if (LineIsFilled)
					ln.Print();
				else
					cout<<"не введена!\n";
				break;
			case tCheckIntersect:
				/*cout<<"Многоугольник ";
				if (PolyIsFilled)
					mn.Print();
				else {
					cout<<"не введен!\n";
					break;
				}
				cout<<"Прямая ";
				if (LineIsFilled)
					ln.Print();
				else {
					cout<<"не введена!\n";
					break;
				}*/
				// удаляем вершины из многоугольников, для размещения результата разделения основного многоугольника 
				//mn_div1.SetSize(0);
				//mn_div2.SetSize(0);
				FillTest(6, mn, ln);
				if (CheckPolyLineIntersect(mn, ln, mn_div1, mn_div2, true))
				{
					cout<<"Разделенные многоугольники:\n";
					mn_div1.Print();
					mn_div2.Print();
				}
				break;
			case tInputFromFile:
				if (mn.ReadFromFile("mn.txt", true))
					PolyIsFilled = true;
				if (ln.ReadFromFile("ln.txt", true))
					LineIsFilled = true;
				break;
			case tSaveToFile:
				mn.SaveToFile("mn.txt", true);
				ln.SaveToFile("ln.txt", true);
				mn_div1.SaveToFile("mn_div1.txt", true);
				mn_div2.SaveToFile("mn_div2.txt", true);
				break;
			case tUnitTest:
				if (!RunUnitTest())
					system("pause");

		}
	}
}