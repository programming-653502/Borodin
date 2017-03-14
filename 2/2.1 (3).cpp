#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cmath>
using namespace std;

float funct_1(float x1, float y1, float x2, float y2);
double checkfunction(string number);
int checkfunction_2(string number);
void segm();
void drawling();
void per_ar();
void Triangle();

int main()
{
    int switcher, exit = 0;
    string switch_check;

    cout << "\t\tMathematical builder \n-------------------------------------------------\n";
    cout << "Welcome to the math program\n" << endl;

    do
    {
        cout << "Please, select the desired number:" << endl;
        cout << "1. Find line segments\n2. Drawing a triangle\n3. Type of triangle\n4. Area and perimeter of the triangle\n5. Author and ver. of the program\n6. Exit" << endl;
        cin >> switch_check;
        switcher = checkfunction_2(switch_check);
        switch(switcher)
        {
            case 1:
            {
                segm();
                break;
            }
            case 2:
            {
                drawling();
                break;
            }
            
            case 3:
            {
                Triangle();
                break;
            }
            case 4:
            {
                per_ar();;
                break;
            }
             case 5:
            {
                cout << "=========\nProgramm version: 1.0  \nMade by Alexander Borodin \n=========\n";
                break;
            }
            case 6:
            {
                exit = 1;
                cout << "=========\nExit, see you soon\n=========";
                break;
            }
            default:
            {
                cout << "Invalid Input !\n-----------------------\n";
                break;
            }
        }
    } while(exit == 0);
    getch();
    return 0;
}


float segm_1, segm_2, segm_3;
double checkfunction(string number){
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
        double num = atof(number.c_str());
        return num;
    }
}


int checkfunction_2(string number){
    int check = 0;
    for (int i = 0; number[i] != '\0'; i++)
    {
        if (number[i] < '0' || number[i] > '9')
        {
            check++;
        }
    }
    if (check)
    {
        return 10;
    } else
    {
        int num = atoi(number.c_str());
        return num;
    }

}


float funct_1(float x1, float y1, float x2, float y2){
	float result;
	result = sqrt( ( pow ( (x2 - x1), 2) ) + ( pow ( (y2 - y1), 2 ) ) );
	return result;
}


void segm(){
	string a1_check, b1_check, a2_check, b2_check, c1_check, d1_check, c2_check, d2_check, e1_check, f1_check, e2_check, f2_check;
	int a1, b1 , a2 , b2, c1 , d1 , c2, d2, e1, e2, f1, f2;
  	
	cout << "===========\n**You need to enter coordinates of the points of the first segmetn(AB). " << endl;
	cout << "*Enter the coordinates X,Y of point A: " << endl;
	cin >> a1_check >> b1_check; 
	a1 = checkfunction(a1_check);
	b1 = checkfunction(b1_check);
	cout << "\n*Enter the coordinates X,Y of point B: " << endl;
	cin >> a2_check >> b2_check; 
	a2 = checkfunction(a2_check);
	b2 = checkfunction(b2_check);
	cout <<"The length of the first segment is:" << funct_1(a1, b1 , a2 , b2) << endl  ;
	segm_1 = funct_1(a1, b1 , a2 , b2);
	
	cout <<"\n**Enter coordinates of the points of the second segmetn(CD). " << endl;
	cout << "*Enter the coordinates X,Y of point C: " << endl;
	cin >> c1_check >> d1_check; 
	c1 = checkfunction(c1_check);
	d1 = checkfunction(d1_check);
	cout << "\n*Enter the coordinates X,Y of point D: " << endl;
	cin >> c2_check >> d2_check; 
	c2 = checkfunction(c2_check);
	d2 = checkfunction(d2_check);
	cout <<"The length of the second segment is: " << funct_1(c1 , d1 , c2, d2) << endl;
	segm_2 = funct_1(c1 , d1 , c2, d2);
	
	cout <<"\n**Enter coordinates of the points of the third segmetn(ED). " << endl;
	cout << "*Enter the coordinates X,Y of point E: " << endl;
	cin >> e1_check >> f1_check; 
	e1 = checkfunction(e1_check);
	f1 = checkfunction(f1_check);
	cout << "\n*Enter the coordinates X,Y of point D: " << endl;
	cin >> e2_check >> f2_check; 
	e2 = checkfunction(e2_check);
	f2 = checkfunction(f2_check);
	cout <<"The length of the third segment is: " << funct_1(e1, f1, e2, f2) <<"\n========\n" << endl;
	segm_3 = funct_1(e1, f1, e2, f2);
}
	
        
void drawling(){
	bool q;
	if (segm_1 == segm_2 == segm_3 == 0){
		cout <<"\nPlease go back and start with item one, because\n";
	}
	else if (segm_1 + segm_2 >= segm_3 && segm_3 + segm_2 >= segm_1 && segm_1 + segm_3 >= segm_2) q = true; else q = false;{}
 		if (q) {
		 cout << "=========\nTriangle with such sides exists\n=========\n" << endl;
		}
		else cout << "=========\nTriangle with such sides does not exist\n=========\n" << endl;
   }


void Triangle(){
	bool q;
	if (segm_1 == segm_2 == segm_3 == 0){
		cout <<"\nPlease go back and start with item one, because you did not enter the values of the segments \n";
	}
	
    else if ( (pow(segm_1, 2) + pow(segm_2, 2) == pow(segm_3, 2)) || ( pow(segm_3, 2) + pow(segm_2, 2) == pow(segm_1, 2)) || ( pow(segm_1, 2) + pow(segm_3, 2) == pow(segm_2, 2) ) ) q=true; else q=false;{}
	 if (q) { cout << "=========\nTriangle is rectangular\n=========\n" << endl;
		}
	 else if (segm_1 == segm_2 || segm_1 == segm_3 || segm_2 == segm_3){
		  
	  		cout << "=========\nTriangle is isosceles\n=========\n" << endl;
	 	 }
	 else if(segm_1 == segm_2 == segm_3 ){
		  
	  		cout << "=========\nTriangle is equilateral\n=========\n" << endl;
	  }
	 else
	  	 cout << "=========\nTriangle is arbitrary \n=========\n" << endl;
}

void per_ar(){
	float perimeter, area, p;
   		p = (segm_1 + segm_2 + segm_3) / 2;
        perimeter = segm_1 + segm_2 + segm_3;
		area = sqrt( p * (p - segm_1) * (p - segm_2) * (p- segm_3));
        cout << "=======\nArea of a triangle: " << area<< endl ;
        cout << "Perimeter of a triangle: " << perimeter <<  endl;
        cout << "=======\n";
   }
