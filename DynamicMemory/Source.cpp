#include<iostream>
using namespace std;

#define tab "\t"

template<typename T>
T** Allocate(const int rows, const int cols);
template<typename T>
void Clear(T**& arr, const int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(char arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols);
void FillRand(char** arr, const int rows, const int cols);
template<typename T>
void Print(T arr[], const int n);
template<typename T>
void Print(T** arr, const int rows, const int cols);

template<typename T>
T* push_back(T arr[], int& n, int value);
template<typename T>
T* push_front(T arr[], int& n, int value);
template<typename T>
T* pop_back(T* arr, int& n);
template<typename T>
T* pop_front(T* arr, int& n);

template<typename T>
T** push_row_down(T** arr, int& rows, const int cols);
template<typename T>
T** pop_row_down(T** arr, int& rows, const int cols);

template<typename T>
void push_col_right(T** arr, const int rows, int& cols);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");
#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер исходного массива: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	cout << "Исходный массив :" << endl;
	Print(arr, n);

	int value;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	//arr = push_front(arr, n, value);
	Print(arr = push_front(arr, n, value), n);
	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_front(arr, n), n);

	delete[] arr;
#endif // DYNAMIC_MEMORY_1

	int rows;
	int cols;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	//Объявление двумерного динамического массива:
	char** arr = Allocate<char>(rows, cols);

	//Использование двумерного динамического массива:
	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	
	arr = push_row_down(arr, rows, cols);
	Print(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);

	push_col_right(arr, rows, cols);
	Print(arr, rows, cols);

	cout << "Удаление последней строки:\n";
	arr = pop_row_down(arr, rows, cols);
	Print(arr, rows, cols);

	//Удаление двумерного динамического массива:
	Clear(arr, rows);
	cout << arr << endl;

}
template<typename T>T** Allocate(const int rows, const int cols)
{
	T** arr = new T* [rows] {};
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols] {};
	}
	return arr;
}
template<typename T>void Clear(T**& arr, const int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];      //удаляем строки
	}
	delete[]arr;      //удаляем массив указателей
	arr = nullptr;     //Оператор delete[] принимает указатель arr, и удаляет память по адресу в этом указателе,
	//при этом адрес хранящийся в указателе arr НЕ изменяется и вполне возможна ситуация, 
		//когда к массиву обратятся после его удаления, что приведёт к ошибке на этапе выполнения и аварийному замершению программы. 
	//Для того чтобы избежать таких ситуаций указатели лучше занулять после удаленияб и при каждом обращении к массиву проверять массив на nullptr.
}
void FillRand(char arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand();
	}

}
void FillRand(char** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand();
		}
	}
}
template<typename T>void Print(T arr[], const int n)
{
	for (int i = 0; i< n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

template<typename T>void Print(T** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << *(*(arr + i) + j) << tab;
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>T* push_back(T arr[], int& n, int value)
{
	//1) Создаём буферный массив: 
	T* buffer = new T[n + 1]{};
	//2) Копируем все элементы из исходного массива в буферный:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) Удавляем исходный массив:
	delete[] arr;
	//4) Подменяем адрес исходного массива, адресом нового массива:
	arr = buffer;
	//Только теперь в массив arr можно добавлять значение, поскольку там появилася ячейка для нового значенияю
	//5) Добавляем значение в конец массива
	arr[n] = value;
	//6) После того как в массиве добавился элемент, количество его элементов увеличивается
	n++;
	// Победа
	return arr;
}

template<typename T>T* push_front(T arr[], int& n, int value)
{
	T* buffer = new T[n + 1]{};
	for (int i = 0; i < n; i++)

		buffer[i + 1] = arr[i];

	delete[] arr;
	arr = buffer;
	arr[0] = value;
	n++;
	return arr;

}

template<typename T>T* pop_back(T* arr, int& n)
{
	T* buffer = new T[--n]{};
	for (int i = 0; i < n; i++) buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

template<typename T>T* pop_front(T* arr, int& n)
{
	T* buffer = new T[--n]{};
	for (int i = 0; i < n; i++) buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

template<typename T>T** push_row_down(T** arr, int& rows, const int cols)
{
	//1) Создаём буферный массив указателей:
	T** buffer = new T* [rows + 1]{};
	//2) Копируем адреса строк из исходного массива указателей в буферный:
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}
	//3)Удаляем исходный массив:
	delete[]arr;
	//4) адрес старого = адресу нового:
	arr = buffer;
	//5) Создаём добавляемую строку:
	arr[rows] = new T[cols] {};
	//6) увеличиваем количество строк:
	rows++;
	return arr;
}
template<typename T>T** pop_row_down(T** arr, int& rows, const int cols)
{
	//rows--;
	delete[] arr[rows-1];
	T** buffer = new T*[--rows] {};
	for (int i = 0; i < rows; i++) buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

template<typename T>void push_col_right(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols + 1]{};
		for (int j = 0; j < cols; j++) buffer[j] = arr[i][j];
		delete[]arr[i];
		arr[i] = buffer;
	}
	cols++;
}