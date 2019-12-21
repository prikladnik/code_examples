#include "iostream"
#include <fstream>
#include "BinaryFunctions.h"
#include "UnitTest.h"
using namespace std;

bool RunUnitTest()
{
	// проверка сортировки 1
	double arr11[5] = {2, 5, 1, 7, 0};
	BubbleSort(arr11, 5);
	if ( (arr11[0] != 0) || (arr11[1] != 1) || (arr11[2] != 2) || 
		(arr11[3] != 5) || (arr11[4] != 7)) {
		cout<<"Сортировка отработала некорректно\n";
		cout<<"Текущий массив:\n";
		PrintArray(arr11, 5);
		cout<<"Требуемый массив\n";
		cout<<"0 1 2 5 7\n";
		return false;
	}

	// проверка сортировки 2 (максимальный элемент находится слева, минимальный - справа, два повторяющихся элемента)
	double arr12[5] = {5, 5, 4, 3, 1};
	BubbleSort(arr12, 5);
	if ( (arr12[0] != 1) || (arr12[1] != 3) || (arr12[2] != 4) || 
		(arr12[3] != 5) || (arr12[4] != 5)) {
		cout<<"Сортировка отработала некорректно\n";
		cout<<"Текущий массив:\n";
		PrintArray(arr12, 5);
		cout<<"Требуемый массив\n";
		cout<<"1 3 4 5 5\n";
		return false;
	}

	// проверка сортировки 3 (максимальный элемент находится справа, два повторяющихся элемента)
	double arr13[5] = {5, 2, 3, 6, 9};
	BubbleSort(arr13, 5);
	if ( (arr13[0] != 2) || (arr13[1] != 3) || (arr13[2] != 5) || 
		(arr13[3] != 6) || (arr13[4] != 9)) {
		cout<<"Сортировка отработала некорректно\n";
		cout<<"Текущий массив:\n";
		PrintArray(arr13, 5);
		cout<<"Требуемый массив\n";
		cout<<"2 3 5 6 9\n";
		return false;
	}

	// проверка сортировки 4 (все элементы одинаковые)
	double arr14[5] = {2, 2, 2, 2, 2};
	BubbleSort(arr14, 5);
	if ( (arr14[0] != 2) || (arr14[1] != 2) || (arr14[2] != 2) || 
		(arr14[3] != 2) || (arr14[4] != 2)) {
		cout<<"Сортировка отработала некорректно\n";
		cout<<"Текущий массив:\n";
		PrintArray(arr14, 5);
		cout<<"Требуемый массив\n";
		cout<<"2 2 2 2 2\n";
		return false;
	}

	// проверка бинарного поиска 1 
	double key;
	int pos;
	double arr21[6] = {1, 5, 8, 10, 11, 25};
	key = 6;
	pos = BinarySearch(arr21, 6, 8);
	if (pos + 1 != 3)
	{
		cout<<"Ошибка в BinarySearch!\n";
		cout<<"Текущий массив:\n";
		PrintArray(arr21, 6);
		cout<<"Искомый элемент "<<key<<" должен быть на позиции "<<3<<", а найден на позиции "<<pos<<endl;
		return false;
	}

	// проверка бинарного поиска 3 (2 повторяющихся элемента) - работает, если на позиции 5
	double key23;
	int pos23;
	double arr23[6] = {1, 5, 8, 10, 10, 25};
	key23 = 10;
	pos23 = BinarySearch(arr23, 6, 10);
	if (pos23 + 1 != 5)
	{
		cout<<"Ошибка в BinarySearch!\n";
		cout<<"Текущий массив:\n";
		PrintArray(arr23, 6);
		cout<<"Искомый элемент "<<key23<<" должен быть на позиции "<<5<<", а найден на позиции "<<pos23<<endl;
		return false;
	}

	// проверка бинарного поиcка 4
	double key24;
	int pos24;
	double arr24[6] = {0, 2, 7, 7, 10, 5};
	key24 = 0;
	pos24 = BinarySearch(arr24, 6, 0);
	if (pos24 + 1 != 1)
	{
		cout<<"Ошибка в BinarySearch!\n";
		cout<<"Текущий массив:\n";
		PrintArray(arr24, 6);
		cout<<"Искомый элемент "<<key24<<" должен быть на позиции "<<1<<", а найден на позиции "<<pos24<<endl;
		return false;
	}

	// проверка IsCorrectDouble
	double value_out;
	if (IsCorrectDouble("12gg", value_out))
	{
		cout<<"Ошибка в IsCorrectDouble! '12gg' на самом деле не является числом!\n";
		return false;
	}
	if (!IsCorrectDouble("12", value_out))
	{
		cout<<"Ошибка в IsCorrectDouble! '12' на самом деле число!\n";
		return false;
	}
	if (IsCorrectDouble("sdfgtyhjiiiikk", value_out))
	{
		cout<<"Ошибка в IsCorrectDouble! 'sdfgtyhjiiiikk' на самом деле не является числом!\n";
		return false;
	}

	// проверка ReadFromFile 1
	int size;
	double * arr4 = ReadFromFile(size, "TestFiles/in1.txt", false);
	if (size != 5)
	{
		cout<<"Ошибка в ReadFromFile!\n";
		cout<<"Из файла in1.txt должно быть прочитано 5 записей, а прочитано "<<size;
		if (arr4) {
			delete []arr4;
			arr4 = NULL;
		}
		return false;
	} else {
		if ( (arr4[0] != 1) || (arr4[1] != 2) || (arr4[2] != 4) || (arr4[3] != 6) || (arr4[4] != 9))
		{
			cout<<"Ошибка в ReadFromFile!\n";
			cout<<"Текущий массив:\n";
			PrintArray(arr4, 5);
			cout<<"Требуемый массив\n";
			cout<<"1 2 4 6 9\n";
			if (arr4) {
				delete []arr4;
				arr4 = NULL;
			}
			return false;
		}
	}

	// проверка ReadFromFile 2 (чисел меньше, чем указано)
	int size41;
	double * arr41 = ReadFromFile(size41, "TestFiles/in2.txt", false);
	if (size41 != 5)
	{
		cout<<"Ошибка в ReadFromFile!\n";
		cout<<"Из файла in2.txt должно быть прочитано 5 записей, а прочитано "<<size41;
		return false;
	} else {
		if ( (arr41[0] != 0) || (arr41[1] != 1) || (arr41[2] != 2) || (arr41[3] != 4) || (arr41[4] != 6))
		{
			cout<<"Ошибка в ReadFromFile!\n";
			cout<<"Текущий массив:\n";
			PrintArray(arr41, 5);
			cout<<"Требуемый массив\n";
			cout<<"0 1 2 4 6\n";
			return false;
		}
	}
	if (arr41) {
		delete []arr41;
		arr41 = NULL;
	}

	// проверка ReadFromFile 3 (файл пустой)
	int size42;
	double * arr42 = ReadFromFile(size42, "TestFiles/in3.txt", false);
	if (size42 != 0)
	{
		cout<<"Ошибка в ReadFromFile!\n";
		cout<<"Из файла in3.txt должно быть прочитано 0 записей, а прочитано "<<size42;
		return false;
	} else {
		if (arr42 != NULL) 
		{
			cout<<"Ошибка в ReadFromFile! Должен возвращаться пустой массив!\n";
			return false;
		}
	}
	if (arr42) {
		delete []arr42;
		arr42 = NULL;
	}
	
	// проверка на открытие отсутствующего файла
	int size43;
	double * arr43 = ReadFromFile(size43, "TestFiles/in4.txt", false);
	if ((size42 != 0) && (arr43 != NULL))
	{
		cout<<"Ошибка в ReadFromFile! Файл in4.txt отсутствует!\n";
		return false;
	}
	if (arr43) {
		delete []arr43;
		arr43 = NULL;
	}
	
	char * path = "TestFiles/out1.txt";
	SaveToFile(path, arr4, size, true, 2, 2, false);
	if (arr4) {
		delete []arr4;
		arr4 = NULL;
	}
	ifstream ifin (path,ios::in);
	if (!ifin)
		cout<<"Ошибка в SaveToFile! Файл "<<path<<" открыть не удалось!"<<endl;
	else if (ifin.peek() == EOF)
	{
		cout<<"Ошибка в SaveToFile! Файл пуст!\n";
		ifin.close();
	} else {
		char str[255];
		ifin.getline(str, 255);
		if (strcmp(str, "5") != 0)
		{
			cout<<"Ошибка в SaveToFile, размер массива был сохранен некорректно!\n";
			cout<<"Должно быть 5, а сохранилось "<<str<<endl;
			return false;
		}
		ifin.getline(str, 255);
		if (strcmp(str, "1 2 4 6 9 ") != 0)
		{
			cout<<"Ошибка в SaveToFile, массив был сохранен некорректно!\n";
			cout<<"Должно быть 1 2 4 6 9 , а сохранилось "<<str<<endl;
			return false;
		}
		ifin.getline(str, 255);
		if (strcmp(str, "Элемент 2 был найден на позиции 2") != 0)
		{
			cout<<"Ошибка в SaveToFile, результаты поиска были сохранены некорректно!\n";
			cout<<"Должен быть текст 'Элемент 2 был найден на позиции 2', а сохранилось "<<str<<endl;
			return false;
		}
		ifin.close();
	}
	cout<<"Все тесты пройдены успешно!\n";
	return true;
}
