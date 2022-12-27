#include <iostream>
using namespace std;

//Задача.Дан двумерный массив целых чисел.Размеры массива вводятся с клавиатуры.Записать функции :
//
//выделение динамической памяти под массив
//заполнение массива случайными числами
//печатание массива;
//удаление массива из динамической памяти
//функции для записи массива в текстовый и бинарный файл.
//функции считывания массива из текстового и бинарного файла.

const int TEXT = 0;
const int BINARY = 1;
const int ONE_DIMENSIONAL = 0;
const int TWO_DIMENSIONAL = 1;

double* CreatingDynamicArray(int n) {
	double* mas = (double*)malloc(n * sizeof(double));
	return mas;
}

double** CreatingDynamicArray(int n, int m) {
	double** arr = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; i++)
	{
		arr[i] = (double*)malloc(m * sizeof(double));
	}
	return arr;
}

void FillingArrayRandomNumbers(double* arr, int n) {
	for (size_t i = 0; i < n; i++)
	{
		arr[i] = 0.001 * (rand() % 10000);
	}
}

void FillingArrayRandomNumbers(double** arr, int n, int m) {
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			arr[i][j] = 0.001 * (rand() % 10000);
		}
	}
}

void PrintArray(double* arr, int n) {
	for (size_t i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void PrintArray(double** arr, int n, int m) {
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

void RemovArray(double* arr) {
	free(arr);
}

void RemovArray(double** arr, int n) {
	for (size_t i = 0; i < n; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

void WritingArrayToTextFile(double* arr, int n, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "wt");
	if (pf != nullptr) {
		fprintf(pf, "%i\n", n);
		for (size_t i = 0; i < n; i++)
		{
			fprintf(pf, "%lf\t", arr[i]);
		}
		fclose(pf);
	}
	else {
		cout << "Error write file" << endl;
		system("pause");
	}
}

void WritingArrayToTextFile(double** arr, int n, int m, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "wt");
	if (pf != nullptr) {
		fprintf(pf, "%i\n", n);
		fprintf(pf, "%i\n", m);
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				fprintf(pf, "%lf\t", arr[i][j]);
			}
			fprintf(pf, "\n");
		}
		fclose(pf);
	}
	else {
		cout << "Error write file" << endl;
		system("pause");
	}
}

void WritingArrayToBinaryFile(double* arr, int& n, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "wb");
	if (pf != nullptr)
	{
		fwrite(&n, sizeof(n), 1, pf);
		fwrite(arr, n * sizeof(arr[0]), 1, pf);
		fclose(pf);
	}
	else {
		cout << "Error write file" << endl;
		system("pause");
	}
}

void WritingArrayToBinaryFile(double** arr, int& n, int& m, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "wb");
	if (pf != nullptr)
	{
		fwrite(&n, sizeof(n), 1, pf);
		fwrite(&m, sizeof(m), 1, pf);
		for (size_t i = 0; i < n; i++)
		{
			fwrite(arr[i], m * sizeof(arr[0][0]), 1, pf);
		}
		fclose(pf);
	}
	else {
		cout << "Error write file" << endl;
		system("pause");
	}

}

double* ReadingArrayFromTextFile(int& n, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "rt");
	if (pf != nullptr) {
		fscanf_s(pf, "%i/n", &n);
		double* arr = CreatingDynamicArray(n);
		for (size_t i = 0; i < n; i++)
		{
			fscanf_s(pf, "%lf\t", &arr[i]);
		}
		fclose(pf);
		return arr;
	}
	else {
		cout << "Error reaad file" << endl;
		system("pause");
	}
	return NULL;
}

double** ReadingArrayFromTextFile(int& n, int& m, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "rt");
	if (pf != nullptr) {
		fscanf_s(pf, "%i/n", &n);
		fscanf_s(pf, "%i/n", &m);
		double** arr = CreatingDynamicArray(n, m);
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				fscanf_s(pf, "%lf\t", &arr[i][j]);
			}
		}
		fclose(pf);
		return arr;
	}
	else {
		cout << "Error reaad file" << endl;
		system("pause");
	}
	return NULL;

}

double* ReadingArrayFromBinaryFile(int& n, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "rb ");
	if (pf != nullptr) {
		fread(&n, sizeof(n), 1, pf);
		double* mas = CreatingDynamicArray(n);
		fread(mas, n * sizeof(mas[0]), 1, pf);
		fclose(pf);
		return mas;
	}
	else {
		cout << "Error reaad file" << endl;
		system("pause");
	}
	return NULL;
}

double** ReadingArrayFromBinaryFile(int& n, int& m, char fileName[]) {
	FILE* pf;
	fopen_s(&pf, fileName, "rb ");
	if (pf != nullptr) {
		fread(&n, sizeof(n), 1, pf);
		fread(&m, sizeof(m), 1, pf);
		double** mas = CreatingDynamicArray(n, m);
		for (size_t i = 0; i < n; i++)
		{
			fread(mas[i], m * sizeof(mas[0][0]), 1, pf);
		}
		fclose(pf);
		return mas;
	}
	else {
		cout << "Error reaad file" << endl;
		system("pause");
	}
	return NULL;
}

void MenuChoiseTypeArray(int& typeArray) {
	char choise;
	do {
		cin.clear();
		/*cin.ignore(numeric_limits<streamsize>::max(), '\n');*/
		system("cls");
		cout << "Меню:" << endl;
		cout << "Выбор типа массива" << endl << endl;
		cout << "1 - одномерный" << endl;
		cout << "2 - двумерный" << endl;
		cin >> choise;

		if (choise == '1')
		{
			typeArray = ONE_DIMENSIONAL;
			break;
		}
		else if (choise == '2')
		{
			typeArray = TWO_DIMENSIONAL;
			break;
		}
		else
		{
			cout << "Не корректный ввод" << endl;
			system("pause");
		}
	} while (true);

	cout << endl;
}

void MenuChoiseTypeFile(int& typeFile) {
	char choise;
	do {
		cin.clear();
		/*cin.ignore(numeric_limits<streamsize>::max(), '\n');*/
		system("cls");
		cout << "Меню:" << endl;
		cout << "Выбор типа файла" << endl << endl;
		cout << "1 - текстовый" << endl;
		cout << "2 - бинарный" << endl;
		cin >> choise;

		if (choise == '1')
		{
			typeFile = TEXT;
			break;
		}
		else if (choise == '2')
		{
			typeFile = BINARY;
			break;
		}
		else
		{
			cout << "Не корректный ввод" << endl;
			system("pause");
		}
	} while (true);
}

void MenuArray(const int typeArray, const int typeFile) {
	char choise;
	double* arrOne = NULL;
	double** arrTwo = NULL;
	int n;
	int m;
	do {
		cin.clear();
		/*cin.ignore(numeric_limits<streamsize>::max(), '\n');*/
		system("cls");
		cout << "Меню:" << endl;
		cout << "Выбор типа файла" << endl << endl;
		cout << "1 - создать массив" << endl;
		cout << "2 - заполнить массив рандомными значениями" << endl;
		cout << "3 - записать массив в файл" << endl;
		cout << "4 - считать массив с файла" << endl;
		cout << "5 - вывести на экран" << endl;
		cout << "6 - назад" << endl;
		cin >> choise;

		if (choise == '1')
		{
			system("cls");
			//создание массива
			if (typeArray == ONE_DIMENSIONAL)
			{
				cout << "Введите количество строк >> ";
				cin >> n;
				arrOne = CreatingDynamicArray(n);
			}
			else {
				cout << "Введите количество строк >> ";
				cin >> n;
				cout << "Введите количество столбцов >> ";
				cin >> m;
				arrTwo = CreatingDynamicArray(n, m);
			}

			system("cls");
			cout << "создан неинициализированный массив" << endl;
			system("pause");
		}
		else if (choise == '2')
		{
			//Заполнить массив
			if (typeArray == ONE_DIMENSIONAL && arrOne != nullptr)
			{
				FillingArrayRandomNumbers(arrOne, n);
			}
			else if (typeArray == TWO_DIMENSIONAL && arrTwo != nullptr)
			{
				FillingArrayRandomNumbers(arrTwo, n, m);
			}
			system("cls");
			cout << "массив заполнен" << endl;
			system("pause");
		}
		else if (choise == '3')
		{
			//Запись массива в файл
			char fileName[100];
			cout << "Введите имя файла >> ";
			scanf_s("%s", fileName, 100);
			if (typeFile == TEXT)
			{
				if (typeArray == ONE_DIMENSIONAL && arrOne != nullptr)
				{
					WritingArrayToTextFile(arrOne, n, fileName);
				}
				else if (typeArray == TWO_DIMENSIONAL && arrTwo != nullptr)
				{
					WritingArrayToTextFile(arrTwo, n, m, fileName);
				}
			}
			else if (typeFile == BINARY)
			{
				if (typeArray == ONE_DIMENSIONAL && arrOne != nullptr)
				{
					WritingArrayToBinaryFile(arrOne, n, fileName);
				}
				else if (typeArray == TWO_DIMENSIONAL && arrTwo != nullptr)
				{
					WritingArrayToBinaryFile(arrTwo, n, m, fileName);
				}
			}
			system("cls");
			cout << "массив записан в файл" << endl;
			system("pause");
		}
		else if (choise == '4')
		{
			// Чтенее из файла
			char fileName[100];
			cout << "Введите имя файла >> ";
			scanf_s("%s", fileName, 100);
			if (typeFile == TEXT)
			{
				if (typeArray == ONE_DIMENSIONAL)
				{
					arrOne = ReadingArrayFromTextFile(n, fileName);
				}
				else if (typeArray == TWO_DIMENSIONAL)
				{
					arrTwo = ReadingArrayFromTextFile(n, m, fileName);
				}
			}
			else if (typeFile == BINARY)
			{
				if (typeArray == ONE_DIMENSIONAL)
				{
					arrOne = ReadingArrayFromBinaryFile(n, fileName);
				}
				else if (typeArray == TWO_DIMENSIONAL)
				{
					arrTwo = ReadingArrayFromBinaryFile(n, m, fileName);
				}
			}
			system("cls");
			cout << "массив прочитан" << endl;
			system("pause");
		}
		else if (choise == '5')
		{
			//Заполнить массив
			if (typeArray == ONE_DIMENSIONAL && arrOne != nullptr)
			{
				system("cls");
				PrintArray(arrOne, n);
				system("pause");
			}
			else if (typeArray == TWO_DIMENSIONAL && arrTwo != nullptr)
			{
				system("cls");
				PrintArray(arrTwo, n, m);
				system("pause");
			}
			else {
				system("cls");
				cout << "массив не создан" << endl;
				system("pause");
			}
		}
		else if (choise == '6')
		{
			break;
		}
		else
		{
			cout << "Не корректный ввод" << endl;
			system("pause");
		}
	} while (true);

}

int main()
{
	setlocale(LC_ALL, "");
	srand(time(0));
	int typeArray;
	int typeFile;

	char choise;
	do
	{
		MenuChoiseTypeArray(typeArray);
		MenuChoiseTypeFile(typeFile);
		MenuArray(typeArray, typeFile);
		cin.clear();
		system("cls");
		cout << "1 - начать заново" << endl;
		cout << "2 - выйти" << endl;
		cin >> choise;

		if (choise == '2')
		{
			break;
		}
		else if (choise != '1')
		{
			cout << "Не корректный ввод" << endl;
			system("pause");
		}
	} while (true);

}