#include <iostream>
#include <cmath>
#include <conio.h>
#include <cstdlib>

using namespace std;

double checkfunc(char number[]);
int factor(int n);
double iteration(double x, int n);

int main()
{
	long double left, right=0;
	double x,z;
	char x_check[255], z_check[255];

    first:
    cout << endl << "Enter x: ";
	cin >> x_check;
	if (checkfunc(x_check) == 0)
    {
        goto first;
    }
	x = checkfunc(x_check);

    second:
    cout << "Enter z: ";
    cin >> z_check;
	if (checkfunc(z_check) == 0)
    {
        cout << endl << "Invalid Input (?>0)" << endl;
        goto second;
    }
	z = checkfunc(z_check);

	left = sin(x);
	for (int i = 1; i < 1000; i++)
	{
		right = iteration(x, i);
		if (abs(left - right) < z)
		{
		    cout << "======================" << endl;
			cout << "It converges for x = " << x << ", when  n = " << i << endl;
			break;
		}
	}

	
	cout << "Right part : " << right << endl;
	cout << "Left part  : " << left << endl;

	getch();
    return 0;
}

double checkfunc(char number[])
{
    int check = 0;
    for (int i = 0; number[i] != '\0'; i++)
    {
        if (number[i] < '0' || number[i] > '9')
        {
            if (number[i] != ',')
            {
                check++;
            }
        }
    }
     if (check)
    {
       cout << " Invalid Input!\n";
       return 0;
    } else
    {
       double num = atof(number);
       return num;
    }
}

int factorial(int n)
{
	int factorial=1;
	for (int i = 2; i <= n; i++)
	{
		factorial *= i;
	}
	return factorial;
}

double iteration(double x, int n)
{
	double result = 0;
	for (int i = 1; i <= n; i++)
	{
		 result += pow((-1), i - 1) * pow(x, 2 * i - 1) / factorial(2 * i - 1);
	}
	return result;
}
