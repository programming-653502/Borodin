#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int check ()
{
    int checknum;
    bool exit;
    do
    {
        string num;
        exit = false;
        cout << "Enter N: ";
        cin >> num;
        for (int i = 0; num[i] != '\0'; i++)
        {
            if(num[i] < '0' || num[i] > '9')
            {
                exit = true;
                cout << "Invalid input!\n";
                break;
            }
        }
        checknum = atoi(num.c_str());
    } while (exit);
    return checknum;
}

void print (int** ptrarray, int n)
{
    for (int count_row = 0; count_row < n; count_row ++)
    {
		for (int count_column = 0; count_column < n ; count_column ++)
		cout << setw(4) << ptrarray[count_row][count_column] << " ";
		cout << endl;
    }
    cout << endl;
}

int main ()
{
    string n_string;
    int n, max, stl, str;
    n = check();
    int  **ptrarray = new int* [n];
    for (int count = 0; count < n; count ++)
    	ptrarray [count] = new int [n];


    for (int count_row = 0; count_row < n; count_row ++)
    {
    	for (int count_column = 0; count_column < n - 1; count_column ++)
        {
		ptrarray[count_row][count_column] = (rand () % 100 + 1);
        }
    }

    for (int count_row = 0; count_row < n; count_row ++)
    {
    	for (int count_column = 0; count_column < n - 1 ; count_column ++)
		cout << setw(4) << ptrarray[count_row][count_column] << " ";
		cout << endl;
    }
	
    cout << endl;
    max = ptrarray [0][0];

    for (int count_row = 0; count_row < n; count_row ++)
    {
	for (int count_column = 0; count_column < n -1 ; count_column ++)
        {
        	if (ptrarray [count_row][count_column] > max)
                {
                	max = ptrarray [count_row][count_column];
                	str = count_row + 1;
                	stl = count_column + 1;
               	}
        }
    }

    cout << "Maximum: " << max << " Raspolojen v " << str << " stroke, stolbze " << stl << endl;

    cout << endl;

    for (int count_row = 0; count_row < n; count_row ++)
    {
   	for (int count_column = n-1; count_column >= stl; count_column --)
        {
            if(count_column == stl)
            {
                ptrarray[count_row][count_column] = 0;
                break;
            }
            int temp = ptrarray[count_row][count_column-1];
            ptrarray[count_row][count_column] = temp;
        }
    }

    print(ptrarray, n);

    for (int count_row = 0; count_row < n; count_row ++)
    {
    	for(int count_column = 0; count_column < count_row; count_column ++)
        {
            int temp = ptrarray[count_row][count_column];
            ptrarray[count_row][count_column] = ptrarray[count_column][count_row];
            ptrarray[count_column][count_row] = temp;
        }
    }

    print(ptrarray, n);

    for (int count_row = 0; count_row < n - 1; count_row ++)
    {
    	for(int count_column = 0; count_column < n - count_row ; count_column ++)
        {
            int temp = ptrarray[count_row][count_column];
        	ptrarray[count_row][count_column] = ptrarray[n - 1 - count_column][n - 1 - count_row];
            ptrarray[n - 1 - count_column][n - 1 - count_row] = temp;
        }
    }

    print(ptrarray, n);

    for (int count = 0; count < n; count ++)
	delete []ptrarray[count];
	
    getch();
    return 0;
}
