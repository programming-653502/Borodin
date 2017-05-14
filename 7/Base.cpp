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
	COORD size = { x, y };
	return ::SetConsoleScreenBufferSize(_ConsoleOut, size);
}

struct A
{                            // описание структуры хранения записей базы автомобилей
	int   volume;							// объем двигателя
	int   year;							// год производства
	int   price;						// базовая цена
	int   priseout;						// цена после уплаты пошлины с учетом наценки поставщика
	char  type[80];					// модель автомобиля
	A()
	{
	    memset(this, 0, sizeof(A));
    } // конструктор (обнуляет записи)
};

struct B
{						  // описание структуры хранения записей базы клиентов
	int   year;           // год производства (не старше)
	int   price;          // цена (не выше)
	char  type[80];       // желаемая модель
	char  Full_name[80];  // имя клиента
	B()
	{
	    memset(this, 0, sizeof(B));
    } // конструктор (обнуляет записи)
};

class Base
{
public:

	void initMenu();                   // Инициализация интерфейса
	Base();
	~Base();

private:

	// методы для работы с базой автомобилей (A - Auto)
	void AddA();	// добавить запись
	void NewA();	// создать и заполнить базу
	void WriteA();	// записать в бинарный файл
	void ClearA();	// выгрузить базу из памяти
	void ReadA();	// прочитать из бинарного файла
	void ShowA();	// отобразить в консоль
	void EditA();	// редактировать записи в базе
	void DeleteA();	// удалить запись из базы
	void toDoA();	// выбор действия
	bool ComparisonA(A&, A&); //  сравнение двух записей по выбранному полю
						// вход - две сравниваемые записи, поле по которому производится сравнение определяется
						//переменной commandA
	void FSA(); 	// поиск и сортировка

	// аналогично для базы клиентов (B - Buyers)
	void AddB(); // добавить запись
	void NewB(); // создать и заполнить базу
	void WriteB(); // записать в бинарный файл
	void ClearB(); // выгрузить базу из памяти
	void ReadB(); // прочитать из бинарного файла
	void ShowB(); // отобразить в консоль
	void EditB(); // редактировать записи в базе
	void DeleteB(); // удалить запись из базы
	void toDoB();  // выбор действия
	bool ComparisonB(B&, B&); //  сравнение двух записей по выбранному полю
						// вход - две сравниваемые записи, поле по которому производится сравнение определяется
						//переменной commandВ
	void Search_Base(); // поиск в базе клиентов


	int GArrow();// работа с клавиатурой
	int mainMenu(char** mMat, char* header, int mSize);// интерактивное меню
	void Info(); // информация о загруженных базах
	void findPosition();// подбор позиций для клиента
	void inStr(char *);// чтение строки
	void inInt(int &);// чтение целого


	void cPrice(A&); // определение цены для клиента
	int gesheft(A&);// определение прибыли фирмы от сделки

	B* clientBase;// массив записей базы клиентов
	int cbaseSize; // размер массива

	A* autoBase;// массив записей базы автомобилей
	int abaseSize; // размер массива

	int currentYear;	// текущий год

	enum opA {
		FMOD,
		FYEAR,
		FVOL,
		FPRICE,
		SPRICE,
		SYEAR,
		EXIT
	} commandA;  // переменная хранит выбранное пользователем действие,
				//которое необходимо выполнить с базой автомобилей (поиск по заданному полю, сортировка)

	enum opB {
		FNAMEB,
		FMODB,
		FPRICEB,
		FYEARB,
		EXIBT
	} commandB; // переменная хранит выбранное пользователем действие,
				//которое необходимо выполнить с базой клиентов (поиск по заданному полю, сортировка)

};

void Base::inStr(char * outStr)
{
	cin.getline(outStr, 80);
}
void Base::inInt(int & outInt)
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


	} while (tmp == 0);

	outInt = tmp;
}

void Base::cPrice(A &x)
{
	int old = currentYear - x.year;
	double ras = 0;

	if (old <= 3)
    {
        ras = 0.6 * x.volume;
    }
    if (old > 3 && old <= 10)
	{
		if (x.volume < 2500)
        {
            ras = 0.35 * x.volume;
        }
		else
        {
			ras = 0.6 * x.volume;
        }
	}
	if (old > 10 && old < 14)
	{
            ras = 0.6 * x.volume;
	}

	if(old >= 14)
    {
        ras = 2.0 * x.volume;
    }
	x.priseout = (int)((double)x.price + 250.0 + ras) * 1.15;

}

int Base::gesheft(A & x)
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


	// формирование меню из списка клиентов
	char** clientbaseList = new char*[cbaseSize];
	for (int i = 0; i < cbaseSize; i++)
		clientbaseList[i] = clientBase[i].Full_name;

	// идентификатор выбранного в меню клиента
	int id = mainMenu(clientbaseList, "\tУкажите клиента, для которого будет выполнен подбор\n\n", cbaseSize);

	// число позиций в списке базы автомобилей, которые соответствуют запросам клиента
	int posCount = 0;

	cout << "Клиенту подходят следующие позиции:" << endl;

	// вывод на экран найденных позиций
	for (int i = 0; i < abaseSize; i++)
		if ((strcmp(autoBase[i].type, clientBase[id].type) == 0)&&(autoBase[i].priseout<= clientBase[id].price) && (autoBase[i].year >= clientBase[id].year))
		{
			posCount++;
			cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout <<"\n\tПрибыль:\t"<<gesheft(autoBase[i])<< endl;
		}


	if (posCount == 0) // если позиции не найдены вывыод сообщения
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
		char* yn[2];
		yn[0] = " Да";
		yn[1] = " Нет";
		int m = mainMenu(yn, "\tСформировать заявку для поставщика ?\n\n", 2);

		if (m == 0)  // сформировать заявку
		{

			// массив строк меню, описывающие найденные позиции
			char** foundposList = new char*[posCount];

			int j = 0;

			for (int i = 0; i < abaseSize; i++)
			{
				if ((strcmp(autoBase[i].type, clientBase[id].type) == 0) && (autoBase[i].priseout <= clientBase[id].price) && (autoBase[i].year >= clientBase[id].year))
				{
					foundposList[j] = new char[200];  // новая строка меню
					foundposList[j][0] = '\0';

					//форматированная запись в строку
					sprintf(foundposList[j], "Модель: %s Цена: %d Год: %d", autoBase[i].type, autoBase[i].priseout, autoBase[i].year);
					j++;
				}
			}

			// идентификатор выбранной позиции для формирования заявки
			int k = mainMenu(foundposList, "\tУкажите выбранную позицию для отправки поставщику \n\n", posCount);

			ofstream fout("заявка_поставщику.txt");

			int count = 0;

			// формирование заявки и вывод в файл
			for (int i = 0; i < abaseSize; i++)

				if (strcmp(autoBase[i].type, clientBase[id].type) == 0)
				{
					if(count ==k)
					fout << "\nФИО заказчика:\t\t"<< clientBase[id].Full_name << "\nПозиция:\t"<< "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout << "\n\tПрибыль:\t" << gesheft(autoBase[i]) << endl;
					count++;
				}

			fout.close();

			for (int i = 0; i < posCount; i++)
				delete[]foundposList[i];
			delete[]foundposList;
		}

	}
	delete[]clientbaseList;
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
		if (key == 13)
        {
            return 2;
        }
		else
        {
            return 100;
        }

}

int Base::mainMenu(char ** mMat, char * header, int mSize)
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
				cout << "---> " << mMat[i] << endl;  // форматирование строки совпадающей текущим пунктом
			else
				cout << "    " << mMat[i] << endl;  //  форматирование прочих строк меню
		}

		int key = GArrow();

		if (key == 0)
        {
            cursor = ++cursor%mSize;
        }
		if (key == 1)
		{
			int ts = cursor;
			if (--ts%mSize < 0)
            {
                cursor = mSize - 2 - (--cursor%mSize);
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

void Base::NewB()
{
	ClearB();
	cout << "Создание новой базы клиентов" << endl;
	cout << "введите размер базы: M= ";
	inInt(cbaseSize);
	clientBase = new B[cbaseSize];
	for (int i = 0; i < cbaseSize; i++)
	{
		cout << "Введите ФИО: " << endl;
		inStr(clientBase[i].Full_name);
		cout << "Введите желаемую модель: "<<endl;
		inStr(clientBase[i].type);
		cout << "Введите год производства: ";
		inInt(clientBase[i].year);
		cout << "Введите граничную стоимость: ";
		inInt(clientBase[i].price);
		cout << endl;
	}
}

void Base::ClearB()//rty
{
	if (!clientBase)
	{
	    return;
	}
	delete[] clientBase;
	clientBase = 0;
	cbaseSize = 0;
}

void Base::WriteB()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }
	ofstream f("client.dat", ios::binary | ios::out); // f - объект класса ofstream, используется для записи в файл
	f << cbaseSize;
	f.write((char*)clientBase, cbaseSize*(sizeof(B)));
	cout << " База клиентов записана успешно " << endl; system("pause");
}

void Base::ShowB()
{
	if (!clientBase)
    {   cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }
	cout << "База клиентов:" << endl;
	for (int i = 0; i < cbaseSize; i++)//rty
    {
       cout << "\nЗапись:\t" << i + 1 << "\n\tФИО:\t\t" << clientBase[i].Full_name << "\n\tМодель:\t\t" << clientBase[i].type << "\n\tГод:\t\t" << clientBase[i].year << "\n\tГр.цена:\t" << clientBase[i].price << endl;
	}
	cout << endl;
	system("pause");
}

void Base::ReadB()
{
	ClearB();
	ifstream in("client.dat", ios::binary | ios::in); //in - объект класса ifstream, используется для чтения из файла.
	in >> cbaseSize;
	clientBase = new B[cbaseSize];
	in.read((char*)clientBase, cbaseSize*(sizeof(B)));
	cout << " База клиентов загружена успешно " << endl;
	system("pause");
}

void Base::EditB()
{

	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }

	char** clientbaseList = new char*[cbaseSize];

	for (int i = 0; i < cbaseSize; i++)
    {
       clientbaseList[i] = clientBase[i].Full_name;
    }

	int i = mainMenu(clientbaseList, "\tВыберите клиента для редактирования записи\n\n", cbaseSize);

		cout << "Выбранная запись: " << endl;
		cout << "\nЗапись:\t" << i + 1 << "\n\tФИО:\t\t" << clientBase[i].Full_name << "\n\tМодель:\t\t" << clientBase[i].type << "\n\tГод:\t\t" << clientBase[i].year << "\n\tГр.цена:\t" << clientBase[i].price << endl;
		cout << endl;
		cout << "Введите новое ФИО: " << endl;
		inStr(clientBase[i].Full_name);
		cout << "Введите новую модель: ";
		cout << endl;
		inStr(clientBase[i].type);
		cout << "Введите новый год производства: ";
		inInt(clientBase[i].year);
		cout << "Введите новую граничную стоимость: ";
		inInt(clientBase[i].price);
		cout << endl;

	delete[]clientbaseList;
}

void Base::AddB()
{
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }

	B* Temp = new B[cbaseSize + 1];
	for (int i = 0; i < cbaseSize; i++)
    {
        Temp[i] = clientBase[i];
    }
	delete[]clientBase;

	clientBase = Temp;

	cout << "Добавление новой записи в клиентскую базу: " << endl;
	cout << "Введите ФИО: " << endl;
	inStr(clientBase[cbaseSize].Full_name);
	cout << "Введите желаемую модель: ";
	cout << endl;
	inStr(clientBase[cbaseSize].type);
	cout << "Введите год производства: ";
	inInt(clientBase[cbaseSize].year);
	cout << "Введите граничную стоимость: ";
	inInt(clientBase[cbaseSize].price);
	cout << endl;
	cbaseSize++;
}

void Base::DeleteA()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }
	if (abaseSize == 1)
	{
		ClearA();
	}
	else
	{
		// список строк меню, идентифицирующих записи в базе автомобилей
		char** abaseList = new char*[abaseSize];
		for (int i = 0; i < abaseSize; i++)
		{
			abaseList[i] = new char[100];
			abaseList[i][0] = '\0';

			char cost[20];
			char Twelvemonth[20];
			sprintf(cost, "%d", autoBase[i].priseout);
			sprintf(Twelvemonth, "%d", autoBase[i].year);

			strcat(abaseList[i], autoBase[i].type);
			strcat(abaseList[i], " Цена: ");
			strcat(abaseList[i], cost);
			strcat(abaseList[i], " Год: ");
			strcat(abaseList[i], Twelvemonth);
		}

		// выбор записи
		int id = mainMenu(abaseList, "\tВыберите запись для удаления\n\n", abaseSize);

		int j  =  0;

		// удаление выбранной записи
		A* Temp = new A[abaseSize - 1];

		for (int i = 0; i < abaseSize; i++)
		{
			if (id != i)
			{
				Temp[j] = autoBase[i];
				j++;
			}
		}

		delete[]autoBase;	autoBase = Temp;

		for (int i = 0; i < abaseSize; i++)
        {
            delete[]abaseList[i];
        }

		delete[]abaseList;

		abaseSize--;
	}
}

void Base::DeleteB()
{

	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
        system("pause");
        return;
    }
	if (cbaseSize == 1)
	{
		ClearB();
	}
	else
	{
		// определение строк меню с фамилиями клиентов
		char** clientbaseList = new char*[cbaseSize];
		for (int i = 0; i < cbaseSize; i++)
        {
            clientbaseList[i] = clientBase[i].Full_name;
        }

		int id = mainMenu(clientbaseList, "\tВыберите запись для удаления\n\n", cbaseSize);


		// удаление записи из массива
		int j = 0;
		B* Temp = new B[cbaseSize - 1];

		for (int i = 0; i < cbaseSize; i++)
		{
			if (id != i)
			{
				Temp[j] = clientBase[i];
				j++;
			}
		}

		delete[]clientBase;	clientBase = Temp;

		delete[]clientbaseList;
		cbaseSize--;
	}
}

void Base::AddA()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }

		A* Temp = new A[abaseSize + 1];
		for (int i = 0; i < abaseSize; i++)
		{
		    Temp[i] = autoBase[i];
		}

		delete[]autoBase;	autoBase = Temp;
		cout << "Добавление новой записи в базу автомобилей: " << endl;
		cout << "Название модели: " << endl;
		inStr(autoBase[abaseSize].type);
		cout << "Год производства: ";
		inInt(autoBase[abaseSize].year);
		cout << "Объем двигателя: ";
		inInt(autoBase[abaseSize].volume);
		cout << "Базовая цена: ";
		inInt(autoBase[abaseSize].price);
		cout << endl;

		cPrice(autoBase[abaseSize]);
		abaseSize++;
}

void Base::NewA()
{

	ClearA();
	cout << "Создание новой базы автомобилей" << endl;
	cout << "Введите размер базы: N= ";
	inInt(abaseSize);
	autoBase = new A[abaseSize];
	for (int i = 0; i < abaseSize; i++)
	{
		cout << "Название модели: " << endl;
		inStr(autoBase[i].type);
		cout << "Год производства: ";
		inInt(autoBase[i].year);
		cout << "Объем двигателя: ";
		inInt(autoBase[i].volume);
		cout << "Базовая цена: ";
		inInt(autoBase[i].price);
		cout << endl;

		cPrice(autoBase[i]);
	}

}

void Base::WriteA()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }
		ofstream f("auto.dat", ios::binary | ios::out);
		f << abaseSize;
		f.write((char*)autoBase, abaseSize*(sizeof(A)));

		cout << " База автомобилей записана успешно " << endl;
		system("pause");
}

void Base::ClearA()
{
	if (!autoBase)
    {
        return;
    }
		delete[] autoBase;
		autoBase = 0;
		abaseSize = 0;
}

void Base::ReadA()
{
	ClearA();
	ifstream in("auto.dat", ios::binary | ios::in);
	in >> abaseSize;
	autoBase = new A[abaseSize];
	in.read((char*)autoBase, abaseSize*(sizeof(A)));

	cout << " База автомобилей загружена успешно " << endl;
	system("pause");
}

void Base::ShowA()
{
	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }
		cout << "База автомобилей:" << endl;
		for (int i = 0; i < abaseSize; i++)
        {
           cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout << endl;
        }
		cout << endl;
		system("pause");
}

void Base::EditA()
{

	if (!autoBase)
    {
        cout << " База автомобилей отсутствует " << endl;
        system("pause");
        return;
    }

	// список строк меню, идентифицирующих записи в базе автомобилей
	char** abaseList = new char*[abaseSize];
	for (int i = 0; i < abaseSize; i++)
	{
		abaseList[i] = new char[200];
		abaseList[i][0] = '\0';
		sprintf(abaseList[i], "Модель: %s Цена: %d Год: %d", autoBase[i].type, autoBase[i].priseout, autoBase[i].year);
	}

	// редактирование выбранной записи
	int i = mainMenu(abaseList, "\tВыберите клиента для редактирования записи\n\n", abaseSize);

		cout << " Выбранная запись: " << endl;
		cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t" << autoBase[i].type << "\n\tОбъем:\t" << autoBase[i].volume << "\n\tГод:\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << endl;
		cout << endl;
		cout << "Название модели: " << endl;
		inStr(autoBase[i].type);
		cout << "Год производства: ";
		inInt(autoBase[i].year);
		cout << "Объем двигателя: ";
		inInt(autoBase[i].volume);
		cout << "Базовая цена: ";
		inInt(autoBase[i].price);
		cout << endl;

		cPrice(autoBase[i]);


	for (int i = 0; i < abaseSize; i++)
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
        cout << " Размер базы автомобилей: " <<abaseSize<<endl;
    }
	if (!clientBase)
    {
        cout << " База клиентов отсутствует " << endl;
    }
	else
    {
        cout << " Размер базы клиентов: " << cbaseSize << endl;
    }
    system("pause");
}

void Base::toDoA()
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

	commandA = (opA)mainMenu(todo, "\tРабота с базой автомобилей\n\n", EXIT + 1);
	if(commandA!=EXIT)
    {
        FSA();
    }

}

bool Base::ComparisonA(A & x, A & temp) //запись базы автомобилей, метод сравнивает две записи по одному из полей ( конкретное поле определяется переменной commandA).
{
	if (commandA == FMOD)
    {
        return strcmp(x.type, temp.type) == 0;
    }
	if (commandA == FPRICE)
	{
	    return x.priseout <= temp.priseout;
	}

	if (commandA == FVOL)
    {
        return x.volume == temp.volume;
    }
	if (commandA == FYEAR)
    {
        return x.year == temp.year;
    }
	if (commandA == SPRICE)
    {
        return x.priseout < temp.priseout;
    }
	if (commandA == SYEAR)
    {
        return x.year < temp.year;
    }
	return false;
}

void Base::FSA()
{
	A temp;

	if (commandA == FMOD)
	{
		cout << "Введите название модели:" << endl;
		inStr(temp.type);
	}
	if (commandA == FPRICE)
	{
		cout << "Введите граничную стоимость:" << endl;
		inInt(temp.priseout);
	}
	if (commandA == FVOL)
	{
		cout << "Введите объем двигателя:" << endl;
		inInt(temp.volume);
	}
	if (commandA == FYEAR)
	{
		cout << "Введите год производства:" << endl;
		inInt(temp.year);
	}

	if (commandA < SPRICE)
	{
		cout << "Критерию поиска соответствуют записи:" << endl;

		bool flag = true; //по значению flag можно установить, успешен ли поиск.

		for (int i = 0; i < abaseSize; i++)
			if (ComparisonA(autoBase[i], temp))
			{
				flag = false;
				cout << "\nЗапись:\t" << i + 1 << "\n\tМодель:\t\t" << autoBase[i].type << "\n\tОбъем:\t\t" << autoBase[i].volume << "\n\tГод:\t\t" << autoBase[i].year << "\n\tБазовая цена:\t" << autoBase[i].price << "\n\tИтоговая цена:\t" << autoBase[i].priseout << endl;
			}

		if (flag)
        {
            cout << "записей не найдено:" << endl;
        }
	}
	else
	{
		for (int i = 0; i < abaseSize - 1; i++)
        {
			for (int j = 0; j < abaseSize - i - 1; j++)
			{
				if (ComparisonA(autoBase[j], autoBase[j + 1]))
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

void Base::Search_Base()
{
	B temp;

	if (commandB == FNAMEB)
	{
		cout << "Введите ФИО клиента:" << endl;
		inStr(temp.Full_name);
	}
	if (commandB == FMODB)
	{
		cout << "Введите название модели:" << endl;
		inStr(temp.type);
	}
	if (commandB == FPRICEB)
	{
		cout << "Введите граничное значение цены:" << endl;
		inInt(temp.price);
	}
	if (commandB == FYEARB)
	{
		cout << "Введите год производства:" << endl;
		inInt(temp.year);
	}

	cout << "Критерию поиска соответствуют записи:" << endl;

	bool flag = true;

	for (int i = 0; i < cbaseSize; i++)
    {
		if (ComparisonB(clientBase[i], temp))
		{
			flag = false;

			cout << "\nЗапись:\t" << i + 1 << "\n\tФИО:\t\t" << clientBase[i].Full_name << "\n\tМодель:\t\t" << clientBase[i].type << "\n\tГод:\t\t" << clientBase[i].year << "\n\tГр.цена:\t" << clientBase[i].price << endl;
		}
    }

	if (flag)
    {
        cout << "записей не найдено:" << endl;
    }
	system("pause");

}

bool Base::ComparisonB(B & x, B & temp)
{
	if (commandB == FNAMEB)
    {
        return strcmp(x.Full_name, temp.Full_name) == 0;
    }
	if (commandB == FMODB)
    {
        return strcmp(x.type, temp.type) == 0;
    }
	if (commandB == FPRICEB)
    {
        return x.price>=temp.price;
    }
	if (commandB == FYEARB)
    {
        return x.year == temp.year;
    }
	return false;
}

void Base::toDoB()
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

	commandB = (opB)mainMenu(todo, "\tРабота с базой клиентов\n\n", EXIBT + 1);
	if (commandB != EXIBT)
    {
        Search_Base();
    }
}

Base::Base()
{
	memset(this, 0, sizeof(Base));   // обнуление полей
	currentYear = 2017;                  // установка текущего года
}

void Base::initMenu()
{

      int mainmenuSize = 21;// число пунктов главного меню
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
	  menu[20] = " Выйти из программы";

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


	int NumMenu = 0;
	while (NumMenu != mainmenuSize - 1)
	{
		NumMenu = mainMenu(menu, "\tБаза автомобилей Атлант-М\n\n", mainmenuSize);

		if (NumMenu == 0)
        {
            Info();
        }
		if (NumMenu == 1)
        {
            ShowB();
        }
		if (NumMenu == 2)
        {
            ShowA();
        }
		if (NumMenu == 3)
        {
            ReadA();
        }
		if (NumMenu == 4)
        {
            ReadB();
        }
		if (NumMenu == 5)
        {
            WriteB();
        }
		if (NumMenu == 6)
        {
            WriteA();
        }
		if (NumMenu == 7)
        {
            NewB();
        }
		if (NumMenu == 8)
        {
            NewA();
        }
		if (NumMenu == 9)
        {
            EditB();
        }
		if (NumMenu == 10)
        {
            EditA();
        }
		if (NumMenu == 11)
		{
		    AddB();
		}
		if (NumMenu == 12)
		{
		    AddA();
		}
		if (NumMenu == 13)
		{
		    DeleteB();
		}
		if (NumMenu == 14)
		{
		    DeleteA();
		}
		if (NumMenu == 15)
		{
		    toDoB();
		}
		if (NumMenu == 16)
		{
		    toDoA();
		}
		if (NumMenu == 17)
        {
            ClearB();
        }
		if (NumMenu == 18)
		{
		    ClearA();
		}
		if (NumMenu == 19)
		{
		   findPosition();
		}
	}

	delete[]menu;
}

Base::~Base()
{
	ClearA();
	ClearB();
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

