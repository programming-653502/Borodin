#include <windows.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cctype>
#include <ctime>
#include <stdio.h>

using namespace std;

HANDLE _ConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);   // ���������� �������
BOOL console_size(short x, short y)                       // ��������� ������� ������ �������
{
	COORD size = { x, y };
	return ::SetConsoleScreenBufferSize(_ConsoleOut, size);
}

struct A
{                            // �������� ��������� �������� ������� ���� �����������
	int   volume;							// ����� ���������
	int   year;							// ��� ������������
	int   price;						// ������� ����
	int   priseout;						// ���� ����� ������ ������� � ������ ������� ����������
	char  type[80];					// ������ ����������
	A()
	{
	    memset(this, 0, sizeof(A));
    } // ����������� (�������� ������)
};

struct B
{						  // �������� ��������� �������� ������� ���� ��������
	int   year;           // ��� ������������ (�� ������)
	int   price;          // ���� (�� ����)
	char  type[80];       // �������� ������
	char  Full_name[80];  // ��� �������
	B()
	{
	    memset(this, 0, sizeof(B));
    } // ����������� (�������� ������)
};

class Base
{
public:

	void initMenu();                   // ������������� ����������
	Base();
	~Base();

private:

	// ������ ��� ������ � ����� ����������� (A - Auto)
	void AddA();	// �������� ������
	void NewA();	// ������� � ��������� ����
	void WriteA();	// �������� � �������� ����
	void ClearA();	// ��������� ���� �� ������
	void ReadA();	// ��������� �� ��������� �����
	void ShowA();	// ���������� � �������
	void EditA();	// ������������� ������ � ����
	void DeleteA();	// ������� ������ �� ����
	void toDoA();	// ����� ��������
	bool ComparisonA(A&, A&); //  ��������� ���� ������� �� ���������� ����
						// ���� - ��� ������������ ������, ���� �� �������� ������������ ��������� ������������
						//���������� commandA
	void FSA(); 	// ����� � ����������

	// ���������� ��� ���� �������� (B - Buyers)
	void AddB(); // �������� ������
	void NewB(); // ������� � ��������� ����
	void WriteB(); // �������� � �������� ����
	void ClearB(); // ��������� ���� �� ������
	void ReadB(); // ��������� �� ��������� �����
	void ShowB(); // ���������� � �������
	void EditB(); // ������������� ������ � ����
	void DeleteB(); // ������� ������ �� ����
	void toDoB();  // ����� ��������
	bool ComparisonB(B&, B&); //  ��������� ���� ������� �� ���������� ����
						// ���� - ��� ������������ ������, ���� �� �������� ������������ ��������� ������������
						//���������� command�
	void Search_Base(); // ����� � ���� ��������


	int GArrow();// ������ � �����������
	int mainMenu(char** mMat, char* header, int mSize);// ������������� ����
	void Info(); // ���������� � ����������� �����
	void findPosition();// ������ ������� ��� �������
	void inStr(char *);// ������ ������
	void inInt(int &);// ������ ������


	void cPrice(A&); // ����������� ���� ��� �������
	int gesheft(A&);// ����������� ������� ����� �� ������

	B* clientBase;// ������ ������� ���� ��������
	int cbaseSize; // ������ �������

	A* autoBase;// ������ ������� ���� �����������
	int abaseSize; // ������ �������

	int currentYear;	// ������� ���

	enum opA {
		FMOD,
		FYEAR,
		FVOL,
		FPRICE,
		SPRICE,
		SYEAR,
		EXIT
	} commandA;  // ���������� ������ ��������� ������������� ��������,
				//������� ���������� ��������� � ����� ����������� (����� �� ��������� ����, ����������)

	enum opB {
		FNAMEB,
		FMODB,
		FPRICEB,
		FYEARB,
		EXIBT
	} commandB; // ���������� ������ ��������� ������������� ��������,
				//������� ���������� ��������� � ����� �������� (����� �� ��������� ����, ����������)

};

void Base::inStr(char * outStr)
{
	cin.getline(outStr, 80);
}
void Base::inInt(int & outInt)
{
	// ���� ��������� �������� � ������ �� �������� ������� ������
	// atoi ���������� 0, ���� 0 ���������� ������ �� ��������� �����.

	int tmp = 0;
	do
	{
		char str[80];
		cin.getline(str, 80);
		tmp = atoi(str);

		if (tmp == 0)
        {
            cout << "������ �������, ��������� ���� �����" << endl;
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
            cout << " �� ���������� ���� ��� ������ " << endl;
            system("pause");
            return;
        }


	// ������������ ���� �� ������ ��������
	char** clientbaseList = new char*[cbaseSize];
	for (int i = 0; i < cbaseSize; i++)
		clientbaseList[i] = clientBase[i].Full_name;

	// ������������� ���������� � ���� �������
	int id = mainMenu(clientbaseList, "\t������� �������, ��� �������� ����� �������� ������\n\n", cbaseSize);

	// ����� ������� � ������ ���� �����������, ������� ������������� �������� �������
	int posCount = 0;

	cout << "������� �������� ��������� �������:" << endl;

	// ����� �� ����� ��������� �������
	for (int i = 0; i < abaseSize; i++)
		if ((strcmp(autoBase[i].type, clientBase[id].type) == 0)&&(autoBase[i].priseout<= clientBase[id].price) && (autoBase[i].year >= clientBase[id].year))
		{
			posCount++;
			cout << "\n������:\t" << i + 1 << "\n\t������:\t\t" << autoBase[i].type << "\n\t�����:\t\t" << autoBase[i].volume << "\n\t���:\t\t" << autoBase[i].year << "\n\t������� ����:\t" << autoBase[i].price << "\n\t�������� ����:\t" << autoBase[i].priseout <<"\n\t�������:\t"<<gesheft(autoBase[i])<< endl;
		}


	if (posCount == 0) // ���� ������� �� ������� ������ ���������
	{
        cout << "���������� ������� �� �������:" << endl;
        cout << endl;
        system("pause");
	}
	else
	{
		cout << endl;
		system("pause");

		// ������� ���� "��" "���" ������������ ������ ����������
		char* yn[2];
		yn[0] = " ��";
		yn[1] = " ���";
		int m = mainMenu(yn, "\t������������ ������ ��� ���������� ?\n\n", 2);

		if (m == 0)  // ������������ ������
		{

			// ������ ����� ����, ����������� ��������� �������
			char** foundposList = new char*[posCount];

			int j = 0;

			for (int i = 0; i < abaseSize; i++)
			{
				if ((strcmp(autoBase[i].type, clientBase[id].type) == 0) && (autoBase[i].priseout <= clientBase[id].price) && (autoBase[i].year >= clientBase[id].year))
				{
					foundposList[j] = new char[200];  // ����� ������ ����
					foundposList[j][0] = '\0';

					//��������������� ������ � ������
					sprintf(foundposList[j], "������: %s ����: %d ���: %d", autoBase[i].type, autoBase[i].priseout, autoBase[i].year);
					j++;
				}
			}

			// ������������� ��������� ������� ��� ������������ ������
			int k = mainMenu(foundposList, "\t������� ��������� ������� ��� �������� ���������� \n\n", posCount);

			ofstream fout("������_����������.txt");

			int count = 0;

			// ������������ ������ � ����� � ����
			for (int i = 0; i < abaseSize; i++)

				if (strcmp(autoBase[i].type, clientBase[id].type) == 0)
				{
					if(count ==k)
					fout << "\n��� ���������:\t\t"<< clientBase[id].Full_name << "\n�������:\t"<< "\n\t������:\t\t" << autoBase[i].type << "\n\t�����:\t\t" << autoBase[i].volume << "\n\t���:\t\t" << autoBase[i].year << "\n\t������� ����:\t" << autoBase[i].price << "\n\t�������� ����:\t" << autoBase[i].priseout << "\n\t�������:\t" << gesheft(autoBase[i]) << endl;
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
				cout << "---> " << mMat[i] << endl;  // �������������� ������ ����������� ������� �������
			else
				cout << "    " << mMat[i] << endl;  //  �������������� ������ ����� ����
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
	cout << "�������� ����� ���� ��������" << endl;
	cout << "������� ������ ����: M= ";
	inInt(cbaseSize);
	clientBase = new B[cbaseSize];
	for (int i = 0; i < cbaseSize; i++)
	{
		cout << "������� ���: " << endl;
		inStr(clientBase[i].Full_name);
		cout << "������� �������� ������: "<<endl;
		inStr(clientBase[i].type);
		cout << "������� ��� ������������: ";
		inInt(clientBase[i].year);
		cout << "������� ��������� ���������: ";
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
        cout << " ���� �������� ����������� " << endl;
        system("pause");
        return;
    }
	ofstream f("client.dat", ios::binary | ios::out); // f - ������ ������ ofstream, ������������ ��� ������ � ����
	f << cbaseSize;
	f.write((char*)clientBase, cbaseSize*(sizeof(B)));
	cout << " ���� �������� �������� ������� " << endl; system("pause");
}

void Base::ShowB()
{
	if (!clientBase)
    {   cout << " ���� �������� ����������� " << endl;
        system("pause");
        return;
    }
	cout << "���� ��������:" << endl;
	for (int i = 0; i < cbaseSize; i++)//rty
    {
       cout << "\n������:\t" << i + 1 << "\n\t���:\t\t" << clientBase[i].Full_name << "\n\t������:\t\t" << clientBase[i].type << "\n\t���:\t\t" << clientBase[i].year << "\n\t��.����:\t" << clientBase[i].price << endl;
	}
	cout << endl;
	system("pause");
}

void Base::ReadB()
{
	ClearB();
	ifstream in("client.dat", ios::binary | ios::in); //in - ������ ������ ifstream, ������������ ��� ������ �� �����.
	in >> cbaseSize;
	clientBase = new B[cbaseSize];
	in.read((char*)clientBase, cbaseSize*(sizeof(B)));
	cout << " ���� �������� ��������� ������� " << endl;
	system("pause");
}

void Base::EditB()
{

	if (!clientBase)
    {
        cout << " ���� �������� ����������� " << endl;
        system("pause");
        return;
    }

	char** clientbaseList = new char*[cbaseSize];

	for (int i = 0; i < cbaseSize; i++)
    {
       clientbaseList[i] = clientBase[i].Full_name;
    }

	int i = mainMenu(clientbaseList, "\t�������� ������� ��� �������������� ������\n\n", cbaseSize);

		cout << "��������� ������: " << endl;
		cout << "\n������:\t" << i + 1 << "\n\t���:\t\t" << clientBase[i].Full_name << "\n\t������:\t\t" << clientBase[i].type << "\n\t���:\t\t" << clientBase[i].year << "\n\t��.����:\t" << clientBase[i].price << endl;
		cout << endl;
		cout << "������� ����� ���: " << endl;
		inStr(clientBase[i].Full_name);
		cout << "������� ����� ������: ";
		cout << endl;
		inStr(clientBase[i].type);
		cout << "������� ����� ��� ������������: ";
		inInt(clientBase[i].year);
		cout << "������� ����� ��������� ���������: ";
		inInt(clientBase[i].price);
		cout << endl;

	delete[]clientbaseList;
}

void Base::AddB()
{
	if (!clientBase)
    {
        cout << " ���� �������� ����������� " << endl;
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

	cout << "���������� ����� ������ � ���������� ����: " << endl;
	cout << "������� ���: " << endl;
	inStr(clientBase[cbaseSize].Full_name);
	cout << "������� �������� ������: ";
	cout << endl;
	inStr(clientBase[cbaseSize].type);
	cout << "������� ��� ������������: ";
	inInt(clientBase[cbaseSize].year);
	cout << "������� ��������� ���������: ";
	inInt(clientBase[cbaseSize].price);
	cout << endl;
	cbaseSize++;
}

void Base::DeleteA()
{
	if (!autoBase)
    {
        cout << " ���� ����������� ����������� " << endl;
        system("pause");
        return;
    }
	if (abaseSize == 1)
	{
		ClearA();
	}
	else
	{
		// ������ ����� ����, ���������������� ������ � ���� �����������
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
			strcat(abaseList[i], " ����: ");
			strcat(abaseList[i], cost);
			strcat(abaseList[i], " ���: ");
			strcat(abaseList[i], Twelvemonth);
		}

		// ����� ������
		int id = mainMenu(abaseList, "\t�������� ������ ��� ��������\n\n", abaseSize);

		int j  =  0;

		// �������� ��������� ������
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
        cout << " ���� �������� ����������� " << endl;
        system("pause");
        return;
    }
	if (cbaseSize == 1)
	{
		ClearB();
	}
	else
	{
		// ����������� ����� ���� � ��������� ��������
		char** clientbaseList = new char*[cbaseSize];
		for (int i = 0; i < cbaseSize; i++)
        {
            clientbaseList[i] = clientBase[i].Full_name;
        }

		int id = mainMenu(clientbaseList, "\t�������� ������ ��� ��������\n\n", cbaseSize);


		// �������� ������ �� �������
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
        cout << " ���� ����������� ����������� " << endl;
        system("pause");
        return;
    }

		A* Temp = new A[abaseSize + 1];
		for (int i = 0; i < abaseSize; i++)
		{
		    Temp[i] = autoBase[i];
		}

		delete[]autoBase;	autoBase = Temp;
		cout << "���������� ����� ������ � ���� �����������: " << endl;
		cout << "�������� ������: " << endl;
		inStr(autoBase[abaseSize].type);
		cout << "��� ������������: ";
		inInt(autoBase[abaseSize].year);
		cout << "����� ���������: ";
		inInt(autoBase[abaseSize].volume);
		cout << "������� ����: ";
		inInt(autoBase[abaseSize].price);
		cout << endl;

		cPrice(autoBase[abaseSize]);
		abaseSize++;
}

void Base::NewA()
{

	ClearA();
	cout << "�������� ����� ���� �����������" << endl;
	cout << "������� ������ ����: N= ";
	inInt(abaseSize);
	autoBase = new A[abaseSize];
	for (int i = 0; i < abaseSize; i++)
	{
		cout << "�������� ������: " << endl;
		inStr(autoBase[i].type);
		cout << "��� ������������: ";
		inInt(autoBase[i].year);
		cout << "����� ���������: ";
		inInt(autoBase[i].volume);
		cout << "������� ����: ";
		inInt(autoBase[i].price);
		cout << endl;

		cPrice(autoBase[i]);
	}

}

void Base::WriteA()
{
	if (!autoBase)
    {
        cout << " ���� ����������� ����������� " << endl;
        system("pause");
        return;
    }
		ofstream f("auto.dat", ios::binary | ios::out);
		f << abaseSize;
		f.write((char*)autoBase, abaseSize*(sizeof(A)));

		cout << " ���� ����������� �������� ������� " << endl;
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

	cout << " ���� ����������� ��������� ������� " << endl;
	system("pause");
}

void Base::ShowA()
{
	if (!autoBase)
    {
        cout << " ���� ����������� ����������� " << endl;
        system("pause");
        return;
    }
		cout << "���� �����������:" << endl;
		for (int i = 0; i < abaseSize; i++)
        {
           cout << "\n������:\t" << i + 1 << "\n\t������:\t\t" << autoBase[i].type << "\n\t�����:\t\t" << autoBase[i].volume << "\n\t���:\t\t" << autoBase[i].year << "\n\t������� ����:\t" << autoBase[i].price << "\n\t�������� ����:\t" << autoBase[i].priseout << endl;
        }
		cout << endl;
		system("pause");
}

void Base::EditA()
{

	if (!autoBase)
    {
        cout << " ���� ����������� ����������� " << endl;
        system("pause");
        return;
    }

	// ������ ����� ����, ���������������� ������ � ���� �����������
	char** abaseList = new char*[abaseSize];
	for (int i = 0; i < abaseSize; i++)
	{
		abaseList[i] = new char[200];
		abaseList[i][0] = '\0';
		sprintf(abaseList[i], "������: %s ����: %d ���: %d", autoBase[i].type, autoBase[i].priseout, autoBase[i].year);
	}

	// �������������� ��������� ������
	int i = mainMenu(abaseList, "\t�������� ������� ��� �������������� ������\n\n", abaseSize);

		cout << " ��������� ������: " << endl;
		cout << "\n������:\t" << i + 1 << "\n\t������:\t" << autoBase[i].type << "\n\t�����:\t" << autoBase[i].volume << "\n\t���:\t" << autoBase[i].year << "\n\t������� ����:\t" << autoBase[i].price << endl;
		cout << endl;
		cout << "�������� ������: " << endl;
		inStr(autoBase[i].type);
		cout << "��� ������������: ";
		inInt(autoBase[i].year);
		cout << "����� ���������: ";
		inInt(autoBase[i].volume);
		cout << "������� ����: ";
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
        cout << " ���� ����������� ����������� " << endl;
    }
	else
    {
        cout << " ������ ���� �����������: " <<abaseSize<<endl;
    }
	if (!clientBase)
    {
        cout << " ���� �������� ����������� " << endl;
    }
	else
    {
        cout << " ������ ���� ��������: " << cbaseSize << endl;
    }
    system("pause");
}

void Base::toDoA()
{
	if (!autoBase)
    {
        cout << " ���� ����������� ����������� " << endl;
        system("pause");
        return;
    }

	char* todo[EXIT + 1];

	todo[FMOD] = " �����, �������� ������";
	todo[EXIT] = " ������";
	todo[FPRICE] = " �����, ���� �� ���� ��������";
	todo[FVOL] = " �����, ����� ���������";
	todo[FYEAR] = " �����, ��� �������";
	todo[SPRICE] = " ����������, ���� ";
	todo[SYEAR] = " ����������, ��� �������";

	commandA = (opA)mainMenu(todo, "\t������ � ����� �����������\n\n", EXIT + 1);
	if(commandA!=EXIT)
    {
        FSA();
    }

}

bool Base::ComparisonA(A & x, A & temp) //������ ���� �����������, ����� ���������� ��� ������ �� ������ �� ����� ( ���������� ���� ������������ ���������� commandA).
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
		cout << "������� �������� ������:" << endl;
		inStr(temp.type);
	}
	if (commandA == FPRICE)
	{
		cout << "������� ��������� ���������:" << endl;
		inInt(temp.priseout);
	}
	if (commandA == FVOL)
	{
		cout << "������� ����� ���������:" << endl;
		inInt(temp.volume);
	}
	if (commandA == FYEAR)
	{
		cout << "������� ��� ������������:" << endl;
		inInt(temp.year);
	}

	if (commandA < SPRICE)
	{
		cout << "�������� ������ ������������� ������:" << endl;

		bool flag = true; //�� �������� flag ����� ����������, ������� �� �����.

		for (int i = 0; i < abaseSize; i++)
			if (ComparisonA(autoBase[i], temp))
			{
				flag = false;
				cout << "\n������:\t" << i + 1 << "\n\t������:\t\t" << autoBase[i].type << "\n\t�����:\t\t" << autoBase[i].volume << "\n\t���:\t\t" << autoBase[i].year << "\n\t������� ����:\t" << autoBase[i].price << "\n\t�������� ����:\t" << autoBase[i].priseout << endl;
			}

		if (flag)
        {
            cout << "������� �� �������:" << endl;
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
		cout << "���� ����������� �������������:" << endl;
	}
	cout << endl;
	system("pause");

}

void Base::Search_Base()
{
	B temp;

	if (commandB == FNAMEB)
	{
		cout << "������� ��� �������:" << endl;
		inStr(temp.Full_name);
	}
	if (commandB == FMODB)
	{
		cout << "������� �������� ������:" << endl;
		inStr(temp.type);
	}
	if (commandB == FPRICEB)
	{
		cout << "������� ��������� �������� ����:" << endl;
		inInt(temp.price);
	}
	if (commandB == FYEARB)
	{
		cout << "������� ��� ������������:" << endl;
		inInt(temp.year);
	}

	cout << "�������� ������ ������������� ������:" << endl;

	bool flag = true;

	for (int i = 0; i < cbaseSize; i++)
    {
		if (ComparisonB(clientBase[i], temp))
		{
			flag = false;

			cout << "\n������:\t" << i + 1 << "\n\t���:\t\t" << clientBase[i].Full_name << "\n\t������:\t\t" << clientBase[i].type << "\n\t���:\t\t" << clientBase[i].year << "\n\t��.����:\t" << clientBase[i].price << endl;
		}
    }

	if (flag)
    {
        cout << "������� �� �������:" << endl;
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
        cout << " ���� �������� ����������� " << endl;
        system("pause");
        return;
    }

	char* todo[EXIBT + 1];

	todo[FNAMEB] = " �����, ��� ������� ";
	todo[FMODB] = " �����, �������� ������";
	todo[FPRICEB] = " �����, ���� �� ���� ��������";
	todo[FYEARB] = " �����, ��� �������";
	todo[EXIBT] = " ������";

	commandB = (opB)mainMenu(todo, "\t������ � ����� ��������\n\n", EXIBT + 1);
	if (commandB != EXIBT)
    {
        Search_Base();
    }
}

Base::Base()
{
	memset(this, 0, sizeof(Base));   // ��������� �����
	currentYear = 2017;                  // ��������� �������� ����
}

void Base::initMenu()
{

      int mainmenuSize = 21;// ����� ������� �������� ����
      char** menu = new char*[mainmenuSize];// ������ ����� �������� ����

	  menu[0] = " ���������� � ����������� �����\n   ----------����� � �������-------------------------------";
	  menu[1] = " ���� ��������";
	  menu[2] = " ���� �����������\n   ----------��������� �� �����----------------------------";
	  menu[3] = " ���� �����������";
	  menu[4] = " ���� ��������\n   ----------��������� � ����------------------------------";
	  menu[5] = " ���� ��������";
	  menu[6] = " ���� �����������\n   ----------������� ����, ��������� ����� �������---------";
	  menu[7] = " ���� ��������";
	  menu[8] = " ���� �����������\n   ----------������������� ����----------------------------";
	  menu[9] = " ���� ��������";
	  menu[10] = " ���� �����������\n   ----------�������� ������ � ����, ���� �� �������-------";
	  menu[11] = " ���� ��������";
	  menu[12] = " ���� �����������\n   ----------������� ������ �� ����------------------------";
	  menu[13] = " ���� ��������";
	  menu[14] = " ���� �����������\n   ----------����� � ����������----------------------------";
	  menu[15] = " ���� ��������";
	  menu[16] = " ���� �����������\n   ----------��������� �� ����������� ������---------------";
	  menu[17] = " ���� ��������";
	  menu[18] = " ���� �����������\n   --------------------------------------------------------";
	  menu[19] = " ������ ����������� ��� �������\n   --------------------------------------------------------";
	  menu[20] = " ����� �� ���������";

	  //"   ----------����� � �������-------------------------------";
	  //"   ----------��������� �� �����----------------------------";
	  //"   ----------��������� � ����------------------------------";
	  //"   ----------������� ����, ��������� ����� �������---------";
	  //"   ----------������������� ����----------------------------";
	  //"   ----------�������� ������ � ����, ���� �� �������-------";
	  //"   ----------������� ������ �� ����------------------------";
	  //"   ----------����� � ����������----------------------------";
	  //"   --------------------------------------------------------";
	  //"   ----------��������� �� ����������� ������---------------";


	int NumMenu = 0;
	while (NumMenu != mainmenuSize - 1)
	{
		NumMenu = mainMenu(menu, "\t���� ����������� ������-�\n\n", mainmenuSize);

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
	system("chcp 1251");                      // ��������� ��������� �������
	system("MODE CON: COLS=100 LINES=40");    // ��������� ������� ���� �������
	console_size(100, 200);                   // ��������� ������� ������ �������
	Base B;                                   // �������� ������� - ����

	B.initMenu();                             // ���� � ���� ���������
	return 0;
}

