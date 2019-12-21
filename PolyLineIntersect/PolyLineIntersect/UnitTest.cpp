#include "iostream"
#include <fstream>
#include "PolyLine.h"
#include "PolyLineFunctions.h"
#include "UnitTest.h"
using namespace std;

void FillTest(int num, Poly &mn, Line &ln)
{
	switch(num)
	{
		case 0:
			mn.SetSize(4);
			mn.SetXY(0, 2, 4);
			mn.SetXY(1, -2, 2);
			mn.SetXY(2, -1, -2);
			mn.SetXY(3, 3, -1);
			ln.SetXY(0, -3, 1);
			ln.SetXY(1, 5, 1);
			break;
		case 1:
			mn.SetSize(4);
			mn.SetXY(0, -5, 7);
			mn.SetXY(1, -7, -7);
			mn.SetXY(2, 2, -4);
			mn.SetXY(3, 4, 5);
			ln.SetXY(0, -8, 5);
			ln.SetXY(1, 6, -1);
			break;
		// случай, когда прямая проходит через одну из вершин многоугольника
		case 2:
			mn.SetSize(4);
			mn.SetXY(0, -5, 7);
			mn.SetXY(1, -7, -7);
			mn.SetXY(2, 2, -4);
			mn.SetXY(3, 4, 5);
			ln.SetXY(0, 4, 8);
			ln.SetXY(1, 4, -6);
			break;
		// случай, когда прямая проходит через две вершины многоугольника
        case 3:
			mn.SetSize(4);
			mn.SetXY(0, -5, 7);
			mn.SetXY(1, -7, -7);
			mn.SetXY(2, 2, -4);
			mn.SetXY(3, 4, 5);
			ln.SetXY(0, -5, 7);
			ln.SetXY(1, 2, -4);
			break;
		// случай, когда прямая пересекает сторону и вершину
        case 4:
			mn.SetSize(4);
			mn.SetXY(0, -5, 7);
			mn.SetXY(1, -7, -7);
			mn.SetXY(2, 2, -4);
			mn.SetXY(3, 4, 5);
			ln.SetXY(0, -8, 5);
			ln.SetXY(1, 4, 5);
			break;    
		// случай, когда прямая проходит через сторону
        case 5:
			mn.SetSize(3);
			mn.SetXY(0, 0, 0);
			mn.SetXY(1, 6, 0);
			mn.SetXY(2, 6, 6);
			ln.SetXY(0, -1, -1);
			ln.SetXY(1, 7, 7);
			break;   
		// случай, когда прямая проходит через сторону
        case 6:
            mn.SetSize(4);
			mn.SetXY(0, 0, 0);
			mn.SetXY(1, 0, 1);
			mn.SetXY(2, 1, 1);
			mn.SetXY(3, 1, 0);
			ln.SetXY(0, -1, 1);
			ln.SetXY(1, 6, 1);
			break;    
		// случай, когда вершины многоугольника заданы не последовательно
        case 7:
            mn.SetSize(4);
			mn.SetXY(0, 0, 0);
			mn.SetXY(1, 1, 1);
			mn.SetXY(2, 0, 1);
			mn.SetXY(3, 1, 0);
			ln.SetXY(0, -1, 0.75);
			ln.SetXY(1, 6, 0.75);
			break;   
		// случай, когда вершины многоугольника заданы не последовательно
        case 8:
	        mn.SetSize(4);
			mn.SetXY(0, 2, 4);
			mn.SetXY(1, -1, -2);
			mn.SetXY(2, -2, 2);
			mn.SetXY(3, 3, -1);
			ln.SetXY(0, -1, -2);
			ln.SetXY(1, 2, 4);
			break;  
	}
}

bool RunUnitTest()
{
	// проверка IsCorrectDouble
	double value_out;
	if (IsCorrectDouble("12gg", value_out, false))
	{
		cout<<"Ошибка в IsCorrectDouble! '12gg' на самом деле не является числом!\n";
		return false;
	}
	if (!IsCorrectDouble("12", value_out, false))
	{
		cout<<"Ошибка в IsCorrectDouble! '12' на самом деле число!\n";
		return false;
	}
	if (IsCorrectDouble("sdfgtyhjiiiikk", value_out, false))
	{
		cout<<"Ошибка в IsCorrectDouble! 'sdfgtyhjiiiikk' на самом деле не является числом!\n";
		return false;
	}

	// проверка ReadFromFile 1
	Poly mn1;
	// выделяем память под массив
	mn1.ReadFromFile("TestFiles/test1mn.txt", false);
	if (mn1.GetSize() != 4)
	{
		cout<<"Ошибка в ReadFromFile!\n";
		cout<<"Из файла test1mn.txt должно быть прочитано 4 вершины, а прочитано "<<mn1.GetSize()<<"\n";
		return false;
	} else {
		if ( (mn1.GetPoint(0).x != 3) || (mn1.GetPoint(0).y != 4) || (mn1.GetPoint(1).x != 5) || (mn1.GetPoint(1).y != 6) || (mn1.GetPoint(2).x != 3) || 
			(mn1.GetPoint(2).y != 2) || (mn1.GetPoint(3).x != 7) || (mn1.GetPoint(3).y != 3))
		{
			cout<<"Ошибка в ReadFromFile!\n";
			cout<<"Текущие координаты вершин:\n";
			mn1.Print();
			cout<<"Требуемые координаты вершин\n";
			cout<<"3 4 5 6 3 2 7 3\n";
			return false;
		}
	}


	// проверка ReadFromFile 2 (файл пустой)
	Poly mn2;
	mn2.ReadFromFile("TestFiles/test2mn.txt", false);
	if (mn2.GetSize() != 0)
	{
		cout<<"Ошибка в ReadFromFile!\n";
		cout<<"Из файла test2mn.txt должно быть прочитано 0 записей, а прочитано "<<mn2.GetSize();
		return false;
	} 

	// проверка на открытие отсутствующего файла
	Poly mn3;
	// выделяем память под массив
	if (mn3.ReadFromFile("TestFiles/test3mn.txt", false))
	{
		cout<<"Ошибка в ReadFromFile! Файл test3mn.txt отсутствует!\n";
		return false;
	}

	// проверка FileIsEmpty
	if (!FileIsEmpty("TestFiles/test4.txt", false))
	{
		cout << "Ошибка в FileIsEmpty! Файл пуст!\n";
		return false;
	}

	if (!FileIsEmpty("test/test3mn.txt", false))
	{
		cout << "Ошибка в FileIsEmpty! Файла test/test3mn.txt не существует!\n";
		return false;
	}

	Line ln1;
	Poly mn_div1, mn_div2;
	FillTest(0, mn1, ln1);
	mn_div1.SetSize(0);
	mn_div2.SetSize(0);
	if (!CheckPolyLineIntersect(mn1, ln1, mn_div1, mn_div2, false))
	{
		cout << "Ошибка в CheckPolyLineIntersect! Пересечение должно быть!\n";
		return false;
	} else if ((mn_div1.GetPoint(0).x != 2) || (mn_div1.GetPoint(0).y != 4) ||
			(mn_div1.GetPoint(1).x != -2) || (mn_div1.GetPoint(1).y != 2) ||
			(mn_div1.GetPoint(2).x != -1.75) || (mn_div1.GetPoint(2).y != 1) ||
			(mn_div1.GetPoint(3).x != 2.6) || (mn_div1.GetPoint(3).y != 1) ||
			(mn_div2.GetPoint(0).x != -1.75) || (mn_div2.GetPoint(0).y != 1) ||
			(mn_div2.GetPoint(1).x != -1) || (mn_div2.GetPoint(1).y != -2) ||
			(mn_div2.GetPoint(2).x != 3) || (mn_div2.GetPoint(2).y != -1) ||
			(mn_div2.GetPoint(3).x != 2.6) || (mn_div2.GetPoint(3).y != 1))
	{
		cout << "Ошибка в CheckPolyLineIntersect! Некорректные координаты вычисленных многоугольников!\n";
		cout<<"Найдено:\n";
		mn_div1.Print();
		mn_div2.Print();
		cout<<"А должно быть:\n (2, 4) (-2, 2) (-1.75, 1) (2.6, 1) \n (-1.75, 1) (-1, -2) (3, -1) (2.6, 1)\n";
		return false;		
	}





 	cout<<"Все тесты пройдены успешно!\n";
	return true;
}