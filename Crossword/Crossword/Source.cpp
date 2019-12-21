#include <locale.h>
#include <fstream>
#include <iostream>

using namespace std;

const char * word_file_name = "seven_lab.txt";
const char * pole_file_name = "pole.txt";
const int n = 6, m = 6; // количество столбцов и строк кроссворда

enum word_rotate { vertical, horizontal };

struct WordPos {
	int x, y;
	word_rotate wr;
};

// лучший вариант размещения слов (по количеству пересечений)
struct {
	char pole[m][n];
	int cross_count; // количество пересечений
} best_crossword;

// вывод кроссворда на экран
void print_crossword(char pole[m][n])
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << pole[i][j];
		cout << endl;
	}
}

// размещает слово на поле
void place_word(char pole[m][n], char * word, WordPos pos)
{
	if (pos.wr == horizontal)
		for (int i = 0; i < strlen(word); i++)
			pole[pos.y][pos.x + i] = word[i];
	else // вертикальное размещение
		for (int i = 0; i < strlen(word); i++)
			pole[pos.y + i][pos.x] = word[i];
}

bool allow_char(char ch)
{
	return (ch == '#') || (ch == ' ');
}

// стирает слово из поля
void clear_word(char pole[m][n], char * word, WordPos pos)
{
	if (pos.wr == horizontal)
	{
		for (int i = 0; i < strlen(word); i++)
			// если сверху или снизу есть буквы, текущую стирать нельзя
			if (((pos.y == 0) || allow_char(pole[pos.y - 1][pos.x + i])) &&
				((pos.y == m - 1) || allow_char(pole[pos.y + 1][pos.x + i])))
				pole[pos.y][pos.x + i] = ' ';
	}
	else
	{
		for (int i = 0; i < strlen(word); i++)
			if (((pos.x == 0) || allow_char(pole[pos.y + i][pos.x - 1])) &&
				((pos.x == n - 1) || allow_char(pole[pos.y + i][pos.x + 1])))
				pole[pos.y + i][pos.x] = ' ';
	}
}

// k - номер текущей проверяемой буквы слова
bool correct_char_place(char pole[m][n], char letter, char next, int x, int y, word_rotate wr, int k)
{
	// клетка пустая или с нужной буквой
	bool res = (pole[y][x] == ' ') || (pole[y][x] == letter);
	if (wr == horizontal)
	{
		// сверху
		if (res && (y > 0))
			// если буква уже есть, выше или ниже нее может быть часть пересекаемого слова
			res = (pole[y][x] == letter) || allow_char(pole[y - 1][x]);
		// снизу
		if (res && (y < m - 1))
			res = (pole[y][x] == letter) || allow_char(pole[y + 1][x]);
		// слева (только для первой буквы слова)		
		if (res && (x > 0) && (k == 0))
			res = (pole[y][x] == letter) || allow_char(pole[y][x - 1]);
		// справа		
		if (res && (x < n - 1))
			res = ((next == ' ') && allow_char(pole[y][x + 1])) ||
			((next != ' ') && ((pole[y][x + 1] == next) || (pole[y][x + 1] == ' ')));
	}
	else // вертикальное размещение
	{
		// сверху (только для первой буквы слова)
		if (res && (y > 0) && (k == 0))
			res = (pole[y][x] == letter) || (allow_char(pole[y - 1][x]));
		// внизу может быть как допустимый символ, так и буква другого слова
		if (res && (y < m - 1))
			res = ((next == ' ') && allow_char(pole[y + 1][x])) ||
			((next != ' ') && ((pole[y + 1][x] == next) || (pole[y + 1][x] == ' ')));
		// слева 
		if (res && (x > 0))
			res = (pole[y][x] == letter) || allow_char(pole[y][x - 1]);
		// справа		
		if (res && (x < n - 1))
			res = (pole[y][x] == letter) || allow_char(pole[y][x + 1]);
	}
	return res;
}

bool correct_position(char pole[m][n], char * word, WordPos pos)
{
	int k = 0;
	char next;
	// pole[i][pos.x] - первая координата, это номер строки, вторая - номер столбца
	if (pos.wr == horizontal)
	{
		// если места для вставки нет
		if (strlen(word) > (n - pos.x))
			return false;
		for (int i = 0; i < strlen(word); i++)
		{
			if (k < strlen(word) - 1)
				next = word[k + 1];
			else
				next = ' ';
			if (correct_char_place(pole, word[k], next, pos.x + i, pos.y, pos.wr, k))
				k++;
			else
				return false;
		}
	}
	else {
		if (strlen(word) > (m - pos.y))
			return false;
		for (int i = 0; i < strlen(word); i++)
		{
			if (k < strlen(word) - 1)
				next = word[k + 1];
			else
				next = ' ';
			if (correct_char_place(pole, word[k], next, pos.x, pos.y + i, pos.wr, k))
				k++;
			else
				return false;
		}
	}
	return true;
}

// вычисляет количество пересечений слов в кроссворде
void define_best_crossword(char pole[m][n])
{
	// вычисляем количество пересечений слов
	int cross = 0;
	// количество букв в строке и в столбце в окрестности текущей буквы
	int row_char, col_char;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// если это не решетка и не пустая клетка
			if (!allow_char(pole[i][j]))
			{
				row_char = 0;
				col_char = 0;
				// считаем количество клеток с буквами сверху и снизу
				if ((i > 0) && (!allow_char(pole[i - 1][j])))
					col_char++;
				if ((i < m - 1) && (!allow_char(pole[i + 1][j])))
					col_char++;
				// слева и справа
				if ((j > 0) && (!allow_char(pole[i][j - 1])))
					row_char++;
				if ((j < n - 1) && (!allow_char(pole[i][j + 1])))
					row_char++;
				// для пересечения нужно как минимум два символа по вертикали и по горизонтали возле текущего
				if ((row_char > 0) && (col_char > 0))
					cross++;
			}
		}
	}
	if (best_crossword.cross_count < cross)
	{
		best_crossword.cross_count = cross;
		// копируем кроссворд как новый "лучший"
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				best_crossword.pole[i][j] = pole[i][j];
	}
}

// генерация корректного местоположения для k слова на текущем варианте поля
void generate(char **words, int size, int k, char pole[m][n])
{
	if (k == size)
	{
		define_best_crossword(pole);
		return;
	}
	WordPos pos;
	for (int y = 0; y < m; y++)
	{
		for (int x = 0; x < n; x++)
		{
			pos.x = x;
			pos.y = y;
			pos.wr = horizontal;
			if (correct_position(pole, words[k], pos))
			{
				place_word(pole, words[k], pos);
				generate(words, size, k + 1, pole);
				clear_word(pole, words[k], pos);
			}

			pos.wr = vertical;
			if (correct_position(pole, words[k], pos))
			{
				place_word(pole, words[k], pos);
				generate(words, size, k + 1, pole);
				clear_word(pole, words[k], pos);
			}
		}
	}
}

int main()
{
	// локализация кодовой страницы
	setlocale(LC_CTYPE, "rus");
	ifstream fin(word_file_name);
	if (!fin.is_open())
		cout << "Не удалось открыть файл!\n";
	else {
		char word[100];
		word[0] = '\0';
		// подсчитываем количество слов в файле
		// количество слов
		int size = 0;
		while (!fin.eof())
		{
			fin >> word;
			if (strlen(word) > 0)
				size++;
		}
		fin.close();
		// заполняем массив слов
		char ** words = new char*[size];
		fin.open(word_file_name);
		int i = 0;
		while (!fin.eof())
		{
			fin >> word;
			if (strlen(word) > 0)
			{
				words[i] = new char[strlen(word) + 1];
				strcpy_s(words[i], strlen(word) + 1, word);
				i++;
			}
		}
		fin.close();
		// сортировка списка слов по невозрастанию длины
		for (i = 0; i < size; i++)
			for (int j = 0; j < size - i - 1; j++)
			{
				if (strlen(words[j]) < strlen(words[j + 1]))
				{
					char * tmp = words[j];
					words[j] = words[j + 1];
					words[j + 1] = tmp;
				}
			}
		// показываем результат
		cout << "Список слов для составления кроссворда!\n";
		for (i = 0; i < size; i++)
		{
			cout << words[i] << endl;
		}
		// считываем матрицу для размещения кроссворда
		ifstream fpole(pole_file_name);
		if (!fpole.is_open())
			cout << "Не удалось открыть файл с содержимым поля для генерации кроссворда!\n";
		else
		{
			char cell;
			char pole[m][n];
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
				{
					fpole >> cell;
					if (cell == '1')
						pole[i][j] = '#';
					else
						pole[i][j] = ' ';
				}
			fpole.close();
			print_crossword(pole);
			best_crossword.cross_count = 0;
			print_crossword(pole);
			generate(words, size, 0, pole);
			if (best_crossword.cross_count > 0)
			{
				cout << "Кроссворд успешно составлен!\n";
				print_crossword(best_crossword.pole);
			}
			else {
				cout << "Не удалось составить кроссворд из указанных слов!\n";
			}
		}
		// удаляем массив слов
		for (i = 0; i < size; i++)
			delete[]words[i];
		delete[]words;
	}
	system("pause");
	return 0;
}