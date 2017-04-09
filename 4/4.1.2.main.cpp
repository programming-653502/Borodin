#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    cout << "Enter text: ";
    char *mas = new char[1];
    string text;
    getline(cin,text);
    for (unsigned short int i = 0; i < text.length(); i++ )
    {
        mas[i] = text[i];
    }
    cout << "Before:" << text << endl;
    int letter = (int)mas[0] - 32;
    if ((int)mas[0] > 96 && (int)mas[0] < 123)
    {
        mas[0] = (char)letter;
    }
    cout << "After:";
    for(unsigned short int i = 0; i < text.length(); i++ )
    {
        cout << mas[i];
        if ( mas[i] == '.' || mas[i] == '!' || mas[i] == '?' )
        {
            i++;
            if ((int)mas[i] > 96 && (int)mas[i] < 123 )
            {
                letter = (int)mas[i] - 32;
                mas[i] = (char)letter;
            }
            i--;
            cout<< " ";
        }
        else if ( mas[i] == ';' || mas[i] == ',' || mas[i] == ':' )
        {
            cout<< " ";
        }
    }
    delete[] mas;
    return 0;
}
