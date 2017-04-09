#include <iostream>
#include <stdio.h>
#include <string>
#include <stack>
#include <string.h>
#include <fstream>

using namespace std;

const int MAXSIZE = 100;
struct Stack 
{
    char data[MAXSIZE];
    int size;
};

int Push ( Stack &S, char x ) 
{
    if( S.size == MAXSIZE ) return 0;
    S.data[S.size] = x;
    S.size ++;
    return 1;
}

char Pop ( Stack &S ) 
{
    if( S.size == 0 ) return char(255);
    S.size --;
    return S.data[S.size];
}

int isEmpty ( Stack &S ) 
{
    return ( S.size == 0 );
}

int main() 
{

    char br1[1] = {'('};
    char br2[1] = {')'};
    char s[80], upper;
    int i = 0, k, h = 0, error = 0;
    char str;
    Stack S;
    S.size = 0;
    ifstream read ("Text.txt");
    while(read >> s[i])
    {
        if (s[i] == '(' || s[i] == ')')
            h++;
        i++;

    }
    read.close();
    for(unsigned short int i = 0; i < strlen(s); i++ ) 
    {
        for(k = 0; k < 1; k++)      
        {
            if( s[i] == br1[k] ) 
            {
                Push ( S, s[i] );
                break;
            }
            if( s[i] == br2[k] ) 
            {
                upper = Pop ( S );
                if( upper != br1[k] ) error = 1;
                {
                    break;
                }
            }
        }
        if( error ) break;
     }

    if( !error && (S.size == 0) )
    {
        int num1 = 2,num2 = h - 1, num3 = 1, num4 = h, arg = 0;
        ifstream read("Text.txt");
        ofstream write("Output.txt");
        while (read >> str)
        {
            if(str == '(' || str == ')')
            {
                arg++;
                if ( str == '(' && arg == num1 )
                {
                    str = '[';
                }
                if ( str == ')' && arg == num2 )
                {
                   str = ']'; 
                }
                if ( str == '(' && arg != num1 && arg != num2 && arg != num3 && arg != num4 )
                {
                    str = '{';
                }
                if ( str == ')' && arg != num1 && arg != num2 && arg != num3 && arg != num4 )
                {
                   str = '}'; 
                }        
            }
            write << str;
        }
        read.close();
        write.close();

        cout << "Number of brackets observed correctly!" << endl;
    }
    else
    cout << "The number of brackets is incorrect, find and correct the error in the text!";
    return 0;
}
