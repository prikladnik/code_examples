#include "iostream"
#include <fstream>
#include "BinaryFunctions.h"
using namespace std;

void PrintInfo()
{
  cout<<"--------------\n";
  cout<<"Intersection.cpp\n";
  cout<<"Лабораторная работа №2. Вариант 5.\n";
  cout<<"Использование массивов.\n";
  cout<<"Напишите программу двоичного поиска заданного значения в упорядоченном массиве.\n"; 
  cout<<"Программа должна возвращать индекс искомого элемента в массиве или каким-либо образом \n";
  cout<<"информировать об отсутствии искомого элемента в массиве.\n";
  cout<<"Студентка группы 414, Голубева Валерия Андреевна, 2014 год.\n";
  cout<<"--------------\n\n";
}

// бинарный поиск
int BinarySearch(double arr[], int size, double key)
{
	int l=0;
	int u=size-1;
	while (l<=u)
	{
		int m=(l+u)/2;
		if(arr[m]==key) return m;
		if(arr[m]<key) l=m+1;
		if(arr[m]>key) u=m-1;
	}
	return -1;
}

// пузырьковая сортировка
void BubbleSort(double arr[], int size) 
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size-i-1; j++)
			if (arr[j]>arr[j+1])
				swap (arr[j],arr[j+1]);
	}
}

// проверяет - является ли строка value_in вещественным числом
bool IsCorrectDouble(char* value_in, double &value_out)
{
	// указатель на возможное место начала ошибочной последовательности символов в строке
	char * end_ptr = NULL;
	// попытка преобразования строки в число
	value_out = strtod(value_in, &end_ptr);
	// если указатель не NULL, значит строка содержит посторонние символы
	if (*end_ptr)
		return false;
	else
		return true;
}

// обеспечение корректного ввода вещественного числа с клавиатуры
double InputDouble()
{
	double value_out;
	// строка для хранения введенного пользователем "числа"
	char value_in[255];
	bool isCorrect = false;
	// цикл - пока пользователь не введет корректное вещественное число
	while (!isCorrect)
	{
		cin>>value_in;
		isCorrect = (IsCorrectDouble(value_in, value_out));
		if (!isCorrect)
			cout<<"Пожалуйста, введите корректное число!\n";
	}
	return value_out;
}

// печать массива на экране
void PrintArray(double arr[], int size)
{
	for (int i=0; i<size; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}

// считывание массива из файла
double* ReadFromFile(int &size, char *path, bool showMessage)
{
	double * arr = NULL;
	size = 0;
	ifstream ifin (path,ios::in); // открытие для чтения
	if (!ifin) //если при открытии файла были ошибки, то !ifin вернет значение отличное от 0
	{
		if (showMessage) cout<<"Файл "<<path<<" открыть не удалось!"<<endl;
	}
    // сравниваем символ, который находится в начале файла и будет прочитан в качестве размера с символом конца файла
	// если файл пуст - то это будет символ конца файла
	else if (ifin.peek() == EOF) 
	{
		if (showMessage) cout<<"Файл пуст!\n";
		ifin.close();
	} else {
		char str[255];
		double value_out;
		// вначале считываем количество чисел в файле
		ifin.getline(str, 255);
		if (!IsCorrectDouble(str, value_out))
		{
			if (showMessage) cout<<"При чтении файла возникли ошибки: количество чисел "<<str<<" не является числом!";
			return NULL;
		}
		size = (int)value_out;
		// выделяем память под массив
		arr = new double[size];
		int i=0;
		char seps[]   = " \t";
		char *token, *next_token;
		bool read_error = false;
		// заполняем массив
		while (!ifin.eof() && (i<size) && (!read_error))
		{
			// считываем строчку из файла
			ifin.getline(str, 255);
			// выделяем первое "число" из массива
			token = strtok_s(str, seps, &next_token);
			// цикл пока из строки удается выделять "числа"
			while(token != NULL)
			{
				if (IsCorrectDouble(token, value_out))
					arr[i++] = value_out;
				else
				{
					if (showMessage)
						cout<<"При чтении файла возникли ошибки: "<<token<<" не является числом!";
					delete []arr;
					arr = NULL;
					read_error = true;
					break;
				}
				// выделяем следующее "число" из строки
				token = strtok_s(NULL, seps, &next_token);
			}
		}
		if (!read_error)
		{
			ifin.close();
			// обрабатываем случай, когда в файле было меньше указанного количества элементов
			for (i; i<size; i++)
				arr[i] = 0;
			// сразу же сортируем (для гарантии того, что он отсортирован)
			BubbleSort(arr, size);
		}
	}
	return arr;
}

// файл пуст или не существует
bool FileIsEmpty(char *path, bool showMessage)
{
	bool rez = true;
	// вначале проверяем: есть ли такой файл и пуст ли он
	ifstream ifin (path,ios::in);
	if ((ifin) && (ifin.peek() != EOF))
	{
		if (showMessage) 
			cout<<"Файл не пуст! ";
		rez = false;
	}
	ifin.close();
	return rez;
}

// сохранение в файл
void SaveToFile(char *path, double arr[], int size, bool saveKey, double key, int pos, bool showMessage)
{
    // сравниваем символ, который находится в начале файла и будет прочитан в качестве размера с символом конца файла
	// если файл пуст - то это будет символ конца файла
	bool canWrite = false;
	char userchoice;
	// пока файл не окажется пустым или несуществующим или указано подавление сообщений
	while ((!canWrite) && showMessage)
	{
		canWrite = FileIsEmpty(path, showMessage);
		if (!canWrite)
		{
			userchoice = 'g';
			while ((userchoice != 'y') && (userchoice != 'n'))
			{
				cout<<"Перезаписать? (y/n): ";
				cin.clear();
				cin.sync();			
				cin>>userchoice;
			}
			if (userchoice == 'n')
			{
				cout<<"Введите путь к файлу: ";
				_flushall();
				cin.getline(path, 250);
			} else
				canWrite = true;
		}
	}
	ofstream ifout (path,ios::out); // открытие для записи
	if (!ifout) //если при создании файла были ошибки, то !ifin вернет значение отличное от 0
	{
		if (showMessage) cout<<"Файл "<<path<<" создать не удалось!"<<endl;
	} else {
		// вначале записываем количество чисел в массиве
		ifout<<size<<endl;
		// сохраняем числа
		for (int i=0; i<size; i++)
			ifout<<arr[i]<<" ";
		ifout<<endl;
		// сохраняем, если нужно, результаты поиска
		if (saveKey)
		{
			ifout<<"Элемент "<<key<<" был найден на позиции "<<pos<<endl;
		}
		ifout.close();
		if (showMessage) cout<<"Файл был успешно сохранен!\n";
	}
}

// ввод массива с клавиатуры
double* FillArray(int &size)
{
	cout<<"Введите размер массива: ";
	size = -1;
	while (size <= 0)
	{
		size = (int)InputDouble();
		if (size <= 0)
			cout<<"Размер массива должен быть > 0!\n";
	}
	double * arr;
    // выделяем память под массив
	arr = new double[size];
	// заполняем массив
	for (int i=0; i<size; i++)
	{
		cout<<"Введите "<<i+1<<"-й элемент массива: ";
		arr[i] = InputDouble();
	}	
	// сразу же сортируем (для гарантии того, что он отсортирован)
	BubbleSort(arr, size);
	return arr;
}
