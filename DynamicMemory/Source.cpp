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
	cout << "������� ������ ��������� �������: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	cout << "�������� ������ :" << endl;
	Print(arr, n);

	int value;
	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "������� ����������� ��������: "; cin >> value;
	//arr = push_front(arr, n, value);
	Print(arr = push_front(arr, n, value), n);
	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_front(arr, n), n);

	delete[] arr;
#endif // DYNAMIC_MEMORY_1

	int rows;
	int cols;
	cout << "������� ���������� �����: "; cin >> rows;
	cout << "������� ���������� ��������� ������: "; cin >> cols;

	//���������� ���������� ������������� �������:
	char** arr = Allocate<char>(rows, cols);

	//������������� ���������� ������������� �������:
	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	
	arr = push_row_down(arr, rows, cols);
	Print(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);

	push_col_right(arr, rows, cols);
	Print(arr, rows, cols);

	cout << "�������� ��������� ������:\n";
	arr = pop_row_down(arr, rows, cols);
	Print(arr, rows, cols);

	//�������� ���������� ������������� �������:
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
		delete[] arr[i];      //������� ������
	}
	delete[]arr;      //������� ������ ����������
	arr = nullptr;     //�������� delete[] ��������� ��������� arr, � ������� ������ �� ������ � ���� ���������,
	//��� ���� ����� ���������� � ��������� arr �� ���������� � ������ �������� ��������, 
		//����� � ������� ��������� ����� ��� ��������, ��� ������� � ������ �� ����� ���������� � ���������� ���������� ���������. 
	//��� ���� ����� �������� ����� �������� ��������� ����� �������� ����� ��������� � ��� ������ ��������� � ������� ��������� ������ �� nullptr.
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
	//1) ������ �������� ������: 
	T* buffer = new T[n + 1]{};
	//2) �������� ��� �������� �� ��������� ������� � ��������:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) �������� �������� ������:
	delete[] arr;
	//4) ��������� ����� ��������� �������, ������� ������ �������:
	arr = buffer;
	//������ ������ � ������ arr ����� ��������� ��������, ��������� ��� ��������� ������ ��� ������ ���������
	//5) ��������� �������� � ����� �������
	arr[n] = value;
	//6) ����� ���� ��� � ������� ��������� �������, ���������� ��� ��������� �������������
	n++;
	// ������
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
	//1) ������ �������� ������ ����������:
	T** buffer = new T* [rows + 1]{};
	//2) �������� ������ ����� �� ��������� ������� ���������� � ��������:
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}
	//3)������� �������� ������:
	delete[]arr;
	//4) ����� ������� = ������ ������:
	arr = buffer;
	//5) ������ ����������� ������:
	arr[rows] = new T[cols] {};
	//6) ����������� ���������� �����:
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