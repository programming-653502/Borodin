#include <windows.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cctype>
#include <ctime>
#include <stdio.h>

using namespace std;

HANDLE _ConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);   // дескриптор консоли
BOOL console_size(short x, short y)                       // изменение размера буфера консоли
{
    	//структура хранения координат буфера консоли, через переменную типа COORD
    	//происходит передача параметров (размера буфера консоли) в функцию SetConsoleScreenBufferSize ( функция Windows API).
	COORD size = { x, y };
	return ::SetConsoleScreenBufferSize(_ConsoleOut, size);
}

struct AUTO
{                           // описание структуры хранения записей базы автомобилей
	int   volume;			// объем двигателя
	int   year;				// год производства
	int   price;			// базовая цена
	int   priseout;			// цена после уплаты пошлины с учетом наценки поставщика
	char   type[20];		// модель автомобиля
	AUTO()
	{
	    memset(this, 0, sizeof(AUTO));
    };  // конструктор (обнуляет записи)
};

struct BUYER
{							 // описание структуры хранения записей базы клиентов
	int   year;              // год производства (не старше)
	int   price;             // цена (не выше)
	char   type[20];         // желаемая модель
	char   FullName[20];     // имя клиента
	BUYER()
	{
	    memset(this, 0, sizeof(BUYER));
    };  // конструктор (обнуляет записи)
};


class Base
{

public:

	void initMenu();    // Инициализация интерфейса
	Base();
	~Base();

private:

	// методы для работы с базой автомобилей
	void AddAuto();	    // добавить запись
	void NewAuto();	    // создать и заполнить базу
	void WriteAuto();	// записать в бинарный файл
	void ClearAuto();	// выгрузить базу из памяти
	void ReadAuto();	// прочитать из бинарного файла
	void ShowAuto();	// отобразить в консоль
	void EditAuto();	// редактировать записи в базе
	void DeleteAuto();	// удалить запись из базы
	void toDoAuto();	// выбор действия
	bool CompareAuto(AUTO&, AUTO&);   //  сравнение двух записей по выбранному полю
						// вход - две сравниваемые записи, поле по которому производится сравнение определяется
						//переменной commandA
	void Find_Sort_Auto(); 	// поиск и сортировка

	// аналогично для базы клиентов
	void AddBuyer();    // добавить запись
	void NewBuyer();    // создать и заполнить базу
	void WriteBuyer();  // записать в бинарный файл
	void ClearBuyer();  // выгрузить базу из памяти
	void ReadBuyer();   // прочитать из бинарного файла
	void ShowBuyer();   // отобразить в консоль
	void EditBuyer();   // редактировать записи в базе
	void DeleteBuyer(); // удалить запись из базы
	void toDoBuyer();   // выбор действия
	bool CompareBuyer(BUYER&, BUYER&);  // сравнение двух записей по выбранному полю
						// вход - две сравниваемые записи, поле по которому производится сравнение определяется
						// переменной commandВ
	void FindInBase();  // поиск в базе клиентов


	int GArrow();               // работа с клавиатурой
	int mMenu(char** mMat, char* header, int mSize);// интерактивное меню
	void Info();                // информация о загруженных базах
	void findPosition();        // подбор позиций для клиента
	void inStr(char *);         // чтение строки
	void inInt(int &, int);     // чтение целого
	void readText();
	void customerPrice(AUTO&);  // определение цены для клиента
	int profit(AUTO&);          // определение прибыли фирмы от сделки

	BUYER* clientBase;  // массив записей базы клиентов
	int clientbaseSize; // размер массива
	AUTO* autoBase;     // массив записей базы автомобилей
	int autobaseSize;   // размер массива
	int currentYear;	// текущий год

	enum opAuto
	{
		FMOD,
		FYEAR,
		FVOL,
		FPRICE,
		SPRICE,
		SYEAR,
		EXIT
	} commandAuto;  // переменная хранит выбранное пользователем действие,
                    // которое необходимо выполнить с базой автомобилей (поиск по заданному полю, сортировка)

	enum opBuyer
	{
		FNAMEB,
		FMODB,
		FPRICEB,
		FYEARB,
		EXIBT
	} commandBuyer; // переменная хранит выбранное пользователем действие,
                    // которое необходимо выполнить с базой клиентов (поиск по заданному полю, сортировка)
};

void Base::readText()
{
	ifstream file("заявка_поставщику.txt");
	if (!file.is_open())
	{
		cout << "Файл с заявкой не обнаружен" << endl;
	}
	else
	{
		cout << "Содержимое файла \"заявка_поставщику.txt\":\n " << endl;
		char str[80];
		while (!file.eof())
		{
			file.getline(str, 80);
			cout << str << endl;
		}
		file.close();
	}
	system("pause");
}

void Base::inStr(char * outStr)
{
	bool tmp = false;
	while (!tmp)
	{
		cin.getline(outStr, 80);
		if (strlen(outStr) > 14)
		{
			tmp = false;
			cout << "Строка должна содержать не больше 14 символов, повторите ввод" << endl;
		}
		else
        {
           tmp = true;
        }
	}
}

void Base::inInt(int & outInt, int lstr)
{
	// если введенное значение в строке не отвечает формату целого
	// atoi возвращает 0, пока 0 происходит запрос на повторный вввод.

	int tmp = 0;
	do
	{
		char str[80];
		cin.getline(str, 80);
		tmp = atoi(str);
		if (tmp == 0)
        {
            cout << "Ошибка формата, повторите ввод числа" << endl;
        }
		if (strlen(str) > lstr)
		{
			tmp = 0;
			cout << "Число не должно содержать больше "<<lstr<<" знаков"<< endl;
		}
	} while (tmp==0);

	outInt = tmp;
}

void Base::customerPrice(AUTO &x)
{
	int old = currentYear - x.year;
	double CustomClearance = 0;

	if (old <= 3)
    {
        CustomClearance = 0.6 * x.volume;
    }
	if (old > 3 && old <= 10)
	{
		if(x.volume < 2500)
        {
            CustomClearance = 0.35 * x.volume;
        }
		else
        {
            CustomClearance = 0.6 * x.volume;
        }
	}
	if (old > 10 && old < 14)
    {
        CustomClearance = 0.6 * x.volume;
    }
	if(old >= 14)
    {
        CustomClearance = 2.0 * x.volume;
    }

	x.priseout = (int)((double)x.price + 250.0 + CustomClearance) * 1.15;
}

int Base::profit(AUTO & x)
{
	return (int)((double)x.priseout - (double)x.priseout / 1.15);
}

void Base::findPosition()
{
	if (!clientBase || !autoBase)
    {
        cout << " Не определены базы для поиска " << endl;
        system("pause");
        return;
    }

	//индекс массиве, индекс указывает на машину для
	//которой сформирована заявка поставщику, элемент массива удаляется.
	int deli = -1;

	// формирование меню из списка клиентов
	char** clientbaseList = new char*[clientbaseSize];
	for (int i = 0; i < clientbaseSize; i++)
    {
        clientbaseList[i] = clientBase[i].FullName;
    }

	// идентификатор выбранного в меню клиента
	int id = mMenu(clientbaseList, "\tУкажите клиента, для которого будет выполнен подбор\n\n", clientbaseSize);

	// число позиций в списке базы автомобилей, которые соответствуют запросам клиента
	int posCount = 0;

	cout << "Клиенту подходят следующие позиции:" << endl;

	// вывод на экран найденных позиций
	for (int i = 0; i < autobaseSize; i++)
    {
		if ((strcmp(autoBase[i].type, clientBase[id].type) == 0) && (autoBase[i].priseout <= clientBase[id].price) && (autoBase[i].year >= clientBase[id].year))
		{
			posCount++;
			cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout <<"\n\tПрибыль:\t"<<profit(autoBase[i])<< endl;
		}
    }

    // если позиции не найдены вывыод сообщения
	if (posCount == 0)
	{
	cout << "подходящих записей не найдено:" << endl;
	cout << endl;
	system("pause");
	}
	else
	{
		cout << endl;
		system("pause");

		// задание меню "да" "нет" сформировать заявку поставщику
		char* yesNo[2];
		yesNo[0] = " Да";
		yesNo[1] = " Нет";

		//вспомогательная переменная, хранит ответ пользователя (да, нет, отмена), полученный при работе функции меню.
		int m = mMenu(yesNo, "\tСформировать заявку для поставщика ?\n\n", 2);

        // сформировать заявку
		if (m == 0)
		{
			// массив строк меню, описывающие найденные позиции
			char** foundposList = new char*[posCount];
			int j = 0;
			for (int i = 0; i < autobaseSize; i++)
			{
				if ((strcmp(autoBase[i].type, clientBase[id].type) == 0) && (autoBase[i].priseout <= clientBase[id].price) && (autoBase[i].year >= clientBase[id].year))
				{
				    // новая строка меню
					foundposList[j] = new char[200];
					foundposList[j][0] = '\0';

					//форматированная запись в строку
					sprintf(foundposList[j], "Модель: %s Цена: %d Год: %d", autoBase[i].type, autoBase[i].priseout, autoBase[i].year);
					j++;
				}
			}

			// идентификатор выбранной позиции для формирования заявки
			//вспомогательная переменная, хранит информацию о выбранной
			//пользователем позици в меню из подходящих вариантов для формирования заявки поставщику
			int k = mMenu(foundposList, "\tУкажите выбранную позицию для отправки поставщику \n\n", posCount);
			ofstream fout("заявка_поставщику.txt");
			int count = 0;

			// формирование заявки и вывод в файл
			for (int i = 0; i < autobaseSize; i++)
            {
				if (strcmp(autoBase[i].type, clientBase[id].type) == 0)
				{
					if (count == k)
					{
						deli = i;
						fout << "\nФИО заказчика:\t\t" << clientBase[id].FullName << "\nПозиция:\t" << "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout << "\n\tПрибыль:\t" << profit(autoBase[i]) << endl;
					}
					count++;
				}
            }
			fout.close();
			for (int i = 0; i < posCount; i++)
            {
                delete[]foundposList[i];
            }
			delete[]foundposList;
		}
	}

	delete[]clientbaseList;

	if (deli != -1)
	{
		int j = 0;
		AUTO* Temp = new AUTO[autobaseSize - 1];
		for (int i = 0; i < autobaseSize; i++)
		{
			if (deli != i)
			{
				Temp[j] = autoBase[i];
				j++;
			}
		}
		delete[]autoBase;
		autoBase = Temp;
		autobaseSize--;
	}
}

int Base::GArrow()
{
	unsigned char key = _getch();
	if (key == 224)
	{
		key = _getch();
		if (key == 72)
        {
            return 1;
        }
		if (key == 80)
        {
            return 0;
        }
	}
	else
    {
		if (key == 13)
        {
            return 2;
        }
		else
        {
            return 100;
        }
    }
}

int Base::mMenu(char ** mMat, char * header, int mSize)
{
	int cursor = 0;
	while (1)
	{
		system("cls");
		cout << header;
		int i;
		for (i = 0; i < mSize; i++)
		{
			if (cursor == i)
            {
                // форматирование строки совпадающей текущим пунктом
				cout << "---> " << mMat[i] << endl;
            }
			else
            {
                //  форматирование прочих строк меню
                cout << "    " << mMat[i] << endl;
            }
		}
		int key = GArrow();
		if (key == 0)
        {
            cursor = ++cursor % mSize;
        }
		if (key == 1)
		{
			// вспомогательная переменная, нужна для организации
			//"закольцовывания" курсора при проходе по пунктам меню
			int ts = cursor;
			if (--ts%mSize<0)
            {
				cursor = mSize - 2 - (--cursor % mSize);
            }
			else
            {
                cursor = (--cursor) % mSize;
            }
		}
		if (key == 2)
		{
			system("cls");
			return cursor;
		}
	}
}

void Base::NewBuyer()
{
	ClearBuyer();
	cout << "Создание новой базы клиентов" << endl;
	cout << "введите размер базы: M= ";
	inInt(clientbaseSize,10);
	clientBase = new BUYER[clientbaseSize];
	for (int i = 0; i < clientbaseSize; i++)
	{
		cout << "Введите ФИО: " << endl;
		inStr(clientBase[i].FullName);
		cout << "Введите желаемую модель: "<<endl;
		inStr(clientBase[i].type);
		cout << "Введите год производства: ";
		inInt(clientBase[i].year,5);
		cout << "Введите граничную стоимость: ";
		inInt(clientBase[i].price,8);
		cout << endl;
	}
}

void Base::ClearBuyer()
{
	if (!clientBase)
    {
        return;
    }
	delete[] clientBase;
	clientBase = 0;
	clientbaseSize = 0;
}

void Base::WriteBuyer()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }
	ofstream f("client.dat", ios::binary | ios::out);
	f << clientbaseSize;
	f.write((char*)clientBase, clientbaseSize*(sizeof(BUYER)));
	cout << " База клиентов записана успешно " << endl; system("pause");
}

void Base::ShowBuyer()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }
	cout << "База клиентов:" << endl;
	for (int i = 0; i < clientbaseSize; i++)
    {
		cout << "\nЗапись:\t" << i + 1 << "\n\tФИО:\t\t" << clientBase[i].FullName << "\n\tМодель:\t\t" << clientBase[i].type << "\n\tГод:\t\t" << clientBase[i].year << "\n\tГр.цена:\t" << clientBase[i].price << endl;
    }
	cout << endl;
	system("pause");
}

void Base::ReadBuyer()
{
	ClearBuyer();
	ifstream in("client.dat", ios::binary | ios::in);
	in >> clientbaseSize;
	clientBase = new BUYER[clientbaseSize];
	in.read((char*)clientBase, clientbaseSize*(sizeof(BUYER)));
	cout << " База клиентов загружена успешно " << endl;
	system("pause");
}

void Base::EditBuyer()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }
	char** clientbaseList = new char*[clientbaseSize];
	for (int i = 0; i < clientbaseSize; i++)
    {
			clientbaseList[i] = clientBase[i].FullName;
    }
	int i = mMenu(clientbaseList, "\tВыберите клиента для редактирования записи\n\n", clientbaseSize);

		cout << "Выбранная запись: " << endl;
		cout << "\nЗапись:\t" << i + 1 << "\n\tФИО:\t\t" << clientBase[i].FullName << "\n\tМодель:\t\t" << clientBase[i].type << "\n\tГод:\t\t" << clientBase[i].year << "\n\tГр.цена:\t" << clientBase[i].price << endl;
		cout << endl;
		cout << "Введите новое ФИО: " << endl;
		inStr(clientBase[i].FullName);
		cout << "Введите новую модель: ";
		cout << endl;
		inStr(clientBase[i].type);
		cout << "Введите новый год производства: ";
		inInt(clientBase[i].year,5);
		cout << "Введите новую граничную стоимость: ";
		inInt(clientBase[i].price,8);
		cout << endl;

	delete[]clientbaseList;
}

void Base::AddBuyer()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }

	BUYER* Temp = new BUYER[clientbaseSize + 1];

	for (int i = 0; i < clientbaseSize; i++)
    {
        Temp[i] = clientBase[i];
    }

	delete[]clientBase;
	clientBase = Temp;

	cout << "Добавление новой записи в клиентскую базу: " << endl;
	cout << "Введите ФИО: " << endl;
	inStr(clientBase[clientbaseSize].FullName);
	cout << "Введите желаемую модель: ";
	cout << endl;
	inStr(clientBase[clientbaseSize].type);
	cout << "Введите год производства: ";
	inInt(clientBase[clientbaseSize].year,5);
	cout << "Введите граничную стоимость: ";
	inInt(clientBase[clientbaseSize].price,8);
	cout << endl;
	clientbaseSize++;
}

void Base::DeleteAuto()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }
	if (autobaseSize == 1)
	{
		ClearAuto();
	}
	else
	{
		// список строк меню, идентифицирующих записи в базе автомобилей
		char** abaseList = new char*[autobaseSize];
		for (int i = 0; i < autobaseSize; i++)
		{
			abaseList[i] = new char[100];
			abaseList[i][0] = '\0';

			char cost[20];
			char annum[20];
			sprintf(cost, "%d", autoBase[i].priseout);
			sprintf(annum, "%d", autoBase[i].year);

			strcat(abaseList[i], autoBase[i].type);
			strcat(abaseList[i], " Цена: ");
			strcat(abaseList[i], cost);
			strcat(abaseList[i], " Год: ");
			strcat(abaseList[i], annum);
		}

		// выбор записи
		int id = mMenu(abaseList, "\tВыберите запись для удаления\n\n", autobaseSize);

        //вспомогательная переменная j, нужна для организации удаления элемента
        //из базы, представляет собой индекс нового массива, указывает на
        //текущую позицию, куда производить копирование записи из текущего массива
		int j  =  0;

		// удаление выбранной записи
		AUTO* Temp = new AUTO[autobaseSize - 1];

		for (int i = 0; i < autobaseSize; i++)
		{
			if (id != i)
			{
				Temp[j] = autoBase[i];
				j++;
			}
		}

		delete[]autoBase;
		autoBase = Temp;

		for (int i = 0; i < autobaseSize; i++)
        {
            delete[]abaseList[i];
        }

		delete[]abaseList;

		autobaseSize--;
	}
}

void Base::DeleteBuyer()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }
	if (clientbaseSize == 1)
	{
		ClearBuyer();
	}
	else
	{
		// определение строк меню с фамилиями клиентов
		char** clientbaseList = new char*[clientbaseSize];
		for (int i = 0; i < clientbaseSize; i++)
        {
            clientbaseList[i] = clientBase[i].FullName;
        }

		int id = mMenu(clientbaseList, "\tВыберите запись для удаления\n\n", clientbaseSize);

		// удаление записи из массива
		int j = 0;
		BUYER* Temp = new BUYER[clientbaseSize - 1];

		for (int i = 0; i < clientbaseSize; i++)
		{
			if (id != i)
			{
				Temp[j] = clientBase[i];
				j++;
			}
		}

		delete[]clientBase;
		clientBase = Temp;

		delete[]clientbaseList;
		clientbaseSize--;
	}
}

void Base::AddAuto()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }

		AUTO* Temp = new AUTO[autobaseSize + 1];
		for (int i = 0; i < autobaseSize; i++)
        {
            Temp[i] = autoBase[i];
        }

		delete[]autoBase;
		autoBase = Temp;
		cout << "Добавление новой записи в базу автомобилей: " << endl;
		cout << "Название модели: " << endl;
		inStr(autoBase[autobaseSize].type);
		cout << "Год производства: ";
		inInt(autoBase[autobaseSize].year,5);
		cout << "Объем двигателя: ";
		inInt(autoBase[autobaseSize].volume,5);
		cout << "Базовая цена: ";
		inInt(autoBase[autobaseSize].price,8);
		cout << endl;

		customerPrice(autoBase[autobaseSize]);
		autobaseSize++;
}

void Base::NewAuto()
{
	ClearAuto();
	cout << "Создание новой базы автомобилей" << endl;
	cout << "Введите размер базы: N= ";
	inInt(autobaseSize,10);
	autoBase = new AUTO[autobaseSize];
	for (int i = 0; i < autobaseSize; i++)
	{
		cout << "Название модели: " << endl;
		inStr(autoBase[i].type);
		cout << "Год производства: ";
		inInt(autoBase[i].year,5);
		cout << "Объем двигателя: ";
		inInt(autoBase[i].volume,5);
		cout << "Базовая цена: ";
		inInt(autoBase[i].price,8);
		cout << endl;

		customerPrice(autoBase[i]);
	}
}

void Base::WriteAuto()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }
		// f - файловая переменная для записи базы автомобилей.
		ofstream f("auto.dat", ios::binary | ios::out);
		f << autobaseSize;
		f.write((char*)autoBase, autobaseSize*(sizeof(AUTO)));

		cout << " База автомобилей записана успешно " << endl;
		system("pause");
}

void Base::ClearAuto()
{
	if (!autoBase)
	{
        return;
    }
		delete[] autoBase;
		autoBase = 0;
		autobaseSize = 0;
}

void Base::ReadAuto()
{
	ClearAuto();

    // in - файловая переменная для чтения базы автомобилей.
	ifstream in("auto.dat", ios::binary | ios::in);
	in >> autobaseSize;
	autoBase = new AUTO[autobaseSize];
	in.read((char*)autoBase, autobaseSize*(sizeof(AUTO)));

	cout << " База автомобилей загружена успешно " << endl; system("pause");
}

void Base::ShowAuto()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }
		cout << "База автомобилей:" << endl;
		for (int i = 0; i < autobaseSize; i++)
        {
			cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout << endl;
        }
		cout << endl;
		system("pause");
}

void Base::EditAuto()
{
	if (!autoBase)
	{
	    cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }

	// список строк меню, идентифицирующих записи в базе автомобилей
	char** abaseList = new char*[autobaseSize];
	for (int i = 0; i < autobaseSize; i++)
	{
		abaseList[i] = new char[200];
		abaseList[i][0] = '\0';
		sprintf(abaseList[i], "Модель: %s Цена: %d Год: %d", autoBase[i].type, autoBase[i].priseout, autoBase[i].year);
	}

	// редактирование выбранной записи
	int i = mMenu(abaseList, "\tВыберите клиента для редактирования записи\n\n", autobaseSize);

		cout << " Выбранная запись: " << endl;
		cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t" << autoBase[i].type << "\n\tОбъем:\t" << autoBase[i].volume << "\n\tГод:\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << endl;
		cout << endl;
		cout << "Название модели: " << endl;
		inStr(autoBase[i].type);
		cout << "Год производства: ";
		inInt(autoBase[i].year,5);
		cout << "Объем двигателя: ";
		inInt(autoBase[i].volume,5);
		cout << "Базовая цена: ";
		inInt(autoBase[i].price,8);
		cout << endl;

		customerPrice(autoBase[i]);

	for (int i = 0; i < autobaseSize; i++)
	{
		delete[]abaseList[i];
	}

	delete[]abaseList;
}

void Base::Info()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
    }
	else
    {
        cout << " Размер базы автомобилей: " <<autobaseSize<<endl;
    }
	if (!clientBase)
    {
		cout << " База клиентов отсутствует " << endl;
    }
	else
    {
		cout << " Размер базы клиентов: " << clientbaseSize << endl;
    }

	system("pause");
}

void Base::toDoAuto()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }

	char* todo[EXIT + 1];

	todo[FMOD] = " Поиск, название модели";
	todo[EXIT] = " Отмена";
	todo[FPRICE] = " Поиск, цена не выше заданной";
	todo[FVOL] = " Поиск, объем двигателя";
	todo[FYEAR] = " Поиск, год выпуска";
	todo[SPRICE] = " Сортировка, цена ";
	todo[SYEAR] = " Сортировка, год выпуска";

	commandAuto = (opAuto)mMenu(todo, "\tРабота с базой автомобилей\n\n", EXIT + 1);
	if(commandAuto != EXIT)
    {
        Find_Sort_Auto();
    }

}

bool Base::CompareAuto(AUTO & x, AUTO & temp)
{
	if (commandAuto == FMOD)
    {
        return strcmp(x.type, temp.type) == 0;
    }
	if (commandAuto == FPRICE)
    {
        return x.priseout<=temp.priseout;
    }
	if (commandAuto == FVOL)
	{
	    return x.volume == temp.volume;
	}
	if (commandAuto == FYEAR)
    {
        return x.year == temp.year;
    }
	if (commandAuto == SPRICE)
    {
        return x.priseout < temp.priseout;
    }
	if (commandAuto == SYEAR)
    {
        return x.year < temp.year;
    }
	return false;
}

void Base::Find_Sort_Auto()
{
	AUTO temp;

	if (commandAuto == FMOD)
	{
		cout << "Введите название модели:" << endl;
		inStr(temp.type);
	}
	if (commandAuto == FPRICE)
	{
		cout << "Введите граничную стоимость:" << endl;
		inInt(temp.priseout,8);
	}
	if (commandAuto == FVOL)
	{
		cout << "Введите объем двигателя:" << endl;
		inInt(temp.volume,5);
	}
	if (commandAuto == FYEAR)
	{
		cout << "Введите год производства:" << endl;
		inInt(temp.year,5);
	}
	if (commandAuto < SPRICE)
	{
		cout << "Критерию поиска соответствуют записи:" << endl;
		bool flag = true;

		for (int i = 0; i < autobaseSize; i++)
        {
			if (CompareAuto(autoBase[i], temp))
			{
				flag = false;
				cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout << endl;
			}
        }
		if (flag)
        {
            cout << "записей не найдено:" << endl;
        }
	}
	else
	{
		for (int i = 0; i < autobaseSize - 1; i++)
        {
			for (int j = 0; j < autobaseSize - i - 1; j++)
			{
				if (CompareAuto(autoBase[j], autoBase[j + 1]))
				{
					temp = autoBase[j];
					autoBase[j] = autoBase[j + 1];
					autoBase[j + 1] = temp;
				}
			}
		}
		cout << "База автомобилей отсортирована:" << endl;
	}
	cout << endl;
	system("pause");

}

void Base::FindInBase()
{
	BUYER temp;

	if (commandBuyer == FNAMEB)
	{
		cout << "Введите ФИО клиента:" << endl;
		inStr(temp.FullName);
	}
	if (commandBuyer == FMODB)
	{
		cout << "Введите название модели:" << endl;
		inStr(temp.type);
	}
	if (commandBuyer == FPRICEB)
	{
		cout << "Введите граничное значение цены:" << endl;
		inInt(temp.price,8);
	}
	if (commandBuyer == FYEARB)
	{
		cout << "Введите год производства:" << endl;
		inInt(temp.year,5);
	}

	cout << "Критерию поиска соответствуют записи:" << endl;

	bool flag = true;

	for (int i = 0; i < clientbaseSize; i++)
    {
		if (CompareBuyer(clientBase[i], temp))
		{
			flag = false;

			cout << "\nЗапись:\t" << i + 1 << "\n\tФИО:\t\t" << clientBase[i].FullName << "\n\tМодель:\t\t" << clientBase[i].type << "\n\tГод:\t\t" << clientBase[i].year << "\n\tГр.цена:\t" << clientBase[i].price << endl;
		}
    }

	if (flag)
    {
        cout << "записей не найдено:" << endl;
    }
	system("pause");
}

bool Base::CompareBuyer(BUYER & x, BUYER & temp)
{
	if (commandBuyer == FNAMEB)
    {
        return strcmp(x.FullName, temp.FullName) == 0;
    }
	if (commandBuyer == FMODB)
    {
        return strcmp(x.type, temp.type) == 0;
    }
	if (commandBuyer == FPRICEB)
    {
        return x.price>=temp.price;
    }
	if (commandBuyer == FYEARB)
    {
        return x.year == temp.year;
    }

	return false;
}

void Base::toDoBuyer()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }

	char* todo[EXIBT + 1];

	todo[FNAMEB] = " Поиск, имя клиента ";
	todo[FMODB] = " Поиск, желаемая модель";
	todo[FPRICEB] = " Поиск, цена не ниже заданной";
	todo[FYEARB] = " Поиск, год выпуска";
	todo[EXIBT] = " Отмена";

	commandBuyer = (opBuyer)mMenu(todo, "\tРабота с базой клиентов\n\n", EXIBT + 1);
	if (commandBuyer != EXIBT)
    {
        FindInBase();
    }
}

Base::Base()
{
	memset(this, 0, sizeof(Base));   // обнуление полей
	currentYear = 2017;                  // установка текущего года
}

void Base::initMenu()
{
      int mainmenuSize = 22;// число пунктов главного меню
      char** menu = new char*[mainmenuSize];// массив строк главного меню

	  menu[0] = " Информация о загруженных базах\n   ----------Вывод в консоль-------------------------------";
	  menu[1] = " База клиентов";
	  menu[2] = " База автомобилей\n   ----------Загрузить из файла----------------------------";
	  menu[3] = " База автомобилей";
	  menu[4] = " База клиентов\n   ----------Сохранить в файл------------------------------";
	  menu[5] = " База клиентов";
	  menu[6] = " База автомобилей\n   ----------Создать базу, заполнить через консоль---------";
	  menu[7] = " База клиентов";
	  menu[8] = " База автомобилей\n   ----------Редактировать базу----------------------------";
	  menu[9] = " База клиентов";
	  menu[10] = " База автомобилей\n   ----------Добавить запись в базу, ввод из консоли-------";
	  menu[11] = " База клиентов";
	  menu[12] = " База автомобилей\n   ----------Удалить запись из базы------------------------";
	  menu[13] = " База клиентов";
	  menu[14] = " База автомобилей\n   ----------Поиск и сортировка----------------------------";
	  menu[15] = " База клиентов";
	  menu[16] = " База автомобилей\n   ----------Выгрузить из оперативной памяти---------------";
	  menu[17] = " База клиентов";
	  menu[18] = " База автомобилей\n   --------------------------------------------------------";
	  menu[19] = " Подбор предложений для клиента\n   --------------------------------------------------------";
	  menu[20] = " Вывести заявку в консоль\n   --------------------------------------------------------";
	  menu[21] = " Выйти из программы";

	  //"   ----------Вывод в консоль-------------------------------";
	  //"   ----------Загрузить из файла----------------------------";
	  //"   ----------Сохранить в файл------------------------------";
	  //"   ----------Создать базу, заполнить через консоль---------";
	  //"   ----------Редактировать базу----------------------------";
	  //"   ----------Добавить запись в базу, ввод из консоли-------";
	  //"   ----------Удалить запись из базы------------------------";
	  //"   ----------Поиск и сортировка----------------------------";
	  //"   --------------------------------------------------------";
	  //"   ----------Выгрузить из оперативной памяти---------------";

	int NumberMenu = 0;
	while (NumberMenu != mainmenuSize - 1)
	{
		NumberMenu = mMenu(menu, "\tБаза автомобилей Атлант-М\n\n", mainmenuSize);

		if (NumberMenu == 0)
        {
            Info();
        }
		if (NumberMenu == 1)
        {
            ShowBuyer();
        }
		if (NumberMenu == 2)
        {
            ShowAuto();
        }
		if (NumberMenu == 3)
        {
            ReadAuto();
        }
		if (NumberMenu == 4)
        {
            ReadBuyer();
        }
		if (NumberMenu == 5)
        {
            WriteBuyer();
        }
		if (NumberMenu == 6)
        {
            WriteAuto();
        }
		if (NumberMenu == 7)
        {
            NewBuyer();
        }
		if (NumberMenu == 8)
        {
            NewAuto();
        }
		if (NumberMenu == 9)
        {
            EditBuyer();
        }
		if (NumberMenu == 10)
        {
            EditAuto();
        }
		if (NumberMenu == 11)
        {
            AddBuyer();
        }
		if (NumberMenu == 12)
        {
            AddAuto();
        }
		if (NumberMenu == 13)
        {
            DeleteBuyer();
        }
		if (NumberMenu == 14)
        {
            DeleteAuto();
        }
		if (NumberMenu == 15)
        {
            toDoBuyer();
        }
		if (NumberMenu == 16)
        {
            toDoAuto();
        }
		if (NumberMenu == 17)
        {
            ClearBuyer();
        }
		if (NumberMenu == 18)
        {
            ClearAuto();
        }
		if (NumberMenu == 19)
        {
            findPosition();
        }
		if (NumberMenu == 20)
        {
            readText();
        }
	}

	delete[]menu;
}

Base::~Base()
{
	ClearAuto();
	ClearBuyer();
}

int main()
{
	system("chcp 1251");                      // установка кодировки консоли
	system("MODE CON: COLS=100 LINES=40");    // установка размера окна консоли
	console_size(100, 200);                   // установка размера буфера консоли
	Base B;                                   // создание объекта - базы

	B.initMenu();                             // вход в цикл обработки
	return 0;
}
