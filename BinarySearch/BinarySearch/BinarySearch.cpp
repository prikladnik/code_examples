#include "iostream"
#include <fstream>
#include "BinaryFunctions.h"
#include "UnitTest.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	PrintInfo();
	char choice;
	// объявляем тип для хранения выбранного пункта меню
	enum menuItemType {tExit, tInputFromConsole, tInputFromFile, tPrint, tSearch, tSaveToFile, tUnitTest, tNone};
	menuItemType menuItem = tNone;	
	// True - если массив и искомое число заполнено
	bool arrayIsFilled=false, searchIsDone=false;
	// обнуляем массив
	double * arr = NULL;
	// и его размер
	int size = 0;
	double key; // объявлем искомый элемент
	int pos; // и позицию для искомого элемента
	while (!(menuItem == tExit)) {
		// вывод меню
		cout<<"\nМеню:\n";
		cout<<"1. Ввести массив чисел с клавиатуры\n";
		cout<<"2. Прочитать массив чисел из файла\n";
		cout<<"3. Вывести массив на экран\n";
		cout<<"4. Найти элемент\n";
		cout<<"5. Сохранить результат работы в файл\n";
		cout<<"6. Выполнить модульные тесты\n";
		cout<<"0. Выход из программы\n";
		cout<<"Введите пункт меню: ";
		cin.clear();
        cin.sync();
		cin>>choice;
		if ((choice>='0') && (choice <='6'))
			menuItem = (menuItemType)(choice - 48);
		else
			menuItem = tNone;
		char path[250]; // объявляем переменную для ввода пути к файлу
		switch (menuItem) {
			case tInputFromConsole:
				// вызываем заполнение массива чисел
				// удаляем старый массив
				if (arr) {
					delete []arr;
					arr = NULL;
				}
				size = 0;
				arr = FillArray(size);
				arrayIsFilled = true;
				searchIsDone=false;
				break;
			case tInputFromFile:
				// вводим путь к файлу
				cout<<"Введите путь к файлу: ";
				_flushall();
				cin.getline(path, 250);				 
				if (arr) {
					delete []arr;
					arr = NULL;
				}
				size = 0;
				arr = ReadFromFile(size, path);
				// проверяем: не было ли ошибок
				if (arr!=NULL)
				{
					cout<<"Массив был успешно считан!\n";
					PrintArray(arr, size);
				}
				arrayIsFilled = arr!=NULL;
				searchIsDone=false;
				break;
			case tPrint:
				if (!arrayIsFilled)
					cout<<"Вначале нужно заполнить массив!\n";
				else
					PrintArray(arr, size);
				break;
			case tSearch:
				if (!arrayIsFilled)
					cout<<"Вначале нужно заполнить массив!\n";
				else {
					cout<<"Отсортированный массив\n";
					PrintArray(arr, size);
					cout<<"Введите искомый элемент: ";
					key = InputDouble();
					pos = BinarySearch(arr, size, key) + 1;
					if (pos>0)
						cout<<"Элемент находится на "<<pos<<" позиции.\n";
					else
						cout<<"Элемент не найден!\n";
					searchIsDone=true;
				}
				break;
			case tSaveToFile:
				// вводим путь к файлу
				cout<<"Введите имя файла для сохранения: ";
				_flushall();
				cin.getline(path, 250);
				SaveToFile(path, arr, size, searchIsDone, key, pos);
				break;
			case tUnitTest:
				if (!RunUnitTest())
					system("pause");
				break;
		}
	}
	// очищаем память после использования
	if (arr) {
		delete []arr;
		arr = NULL;
	}
	cout<<"Спасибо за работу с программой. Всего доброго!\n";
	// вывод системного приглашения нажать любую клавишу
	system("pause");
	return 0;
}
