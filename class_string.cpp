#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class String
{
    char *str;
    int len;

    public:
    String (int l = 0); 
    String (const char *s);
    String (String &s); 
    ~String () 
    {
        if (str)
        {
            delete []str; 
            str = NULL; 
        }
    }
    
    int Len();
    
    String & operator = (const String &s); 
    char & operator [] (int i); 
    bool operator == (String &s);
    bool operator != (String &s); 
    String operator + (const String &s); 
    String & operator += (const String &s);
    friend istream & operator >> (istream &r, String &s);
    friend ostream & operator << (ostream &r, String &s);
    int BMH_search(String &s);
};

String :: String (int l)
{
    str = new char [l+1];
    l = 0;
    str [0] = '\0';
}

String :: String (const char *s)
{
    str = new char [strlen (s) + 1];
    for (len = 0; s[len] != '\0'; len ++)
    {
        str [len] = s[len];
    }
    str [len] = '\0';
}

String :: String (String &s)
{
    str = new char [s.len + 1];
    for (len = 0; len <= s.len; len ++)
    {
        str[len] = s.str[len];
    }
    len--;
}

int String :: Len ()
{
    return len;
}

String & String :: operator = (const String &s)
{
    if (this != &s) //s = s
    {
        delete []str;
        str = new char [(len = s.len) + 1];
        strncpy (str, s.str, len + 1);
    }
    return *this;
}

char & String :: operator [] (int i)
{
    if ((i<0) || (i>=len))
    {
        cout << "Index outside" << endl;
        exit (1);
    }
    return str[i];
}

bool String :: operator == (String &s)
{
    if (strcmp (str, s.str))
    {
        return 0;
    }
    return 1;
}

bool String :: operator != (String &s)
{
       if (strcmp (str, s.str))
    {
        return 1;
    }
    return 0;
}

String String :: operator + (const String &s)
{
    String z (len + s.len + 1);
    z.len = len + s.len;
    strncpy (z.str, str, z.len + 1);
    strncat (z.str, s.str, z.len + 1);
    return z;
}

String & String :: operator += (const String &s)
{
    char *t = new char [len + 1];
    strncpy (t, str, len +1);
    delete []str;
    len = len + s.len;
    str = new char [len + 1];
    strncpy (str, t, len + 1);
    strncat (str, s.str, len + 1);
    delete []t;
    return * this;
}

istream & operator >> (istream &r, String &s)
{
    char buf[80];
    fgets(buf, 80, stdin);
    String q(buf);
    s = q;
    s.len = s.Len();
    return r;
}
ostream & operator << (ostream &r, String &s)
{
    r << s.str;
    return r;
}

int String :: BMH_search (String &s)

{
    int res;
    int T [256]; // T - таблица

    for (int i = 0; i < 256; i ++) // Начальное значение для всех элементов - длина образца
    {
        T[i] = s.len;
    }

    for (int i = 0; i < s.len - 1; i++) // Задаём значения таблицы по образцу
    {
        T[s[i]] = s.len - 1 - i;
    }

    int i, j, k;
    i = s.len - 1;
    j = s.len - 1;
    
    while ((i < len) && (j >= 0))
    {
        k = i;
        j = s.len - 1;

        while (j >= 0)
        {
            if (str[k] == s[j]) 
            {
                j--; k--;
            }

            //если символы не равны, то делаем сдвиг согласно таблице
            else
            {
                i = i + T[str[i]];
                j = s.len - 1;
                break;
            }
        }
    }
    /* возврат позиции
    если не найдено:    -1
    если найдено:   i + 1 - длина подстроки */
    
    return (j >= 0) ? -1 : (i + 1 - s.len);
}


int main ()
{
//    String line_1 ("firjfrgttjj"), line_2 ("rghrueirgu"), line_3 ("rnruunueo"), line_4 ("rnruunueo"), line_5;
//    int len_1, len_2, len_3, len_4, len_5;
//    
//    String line_6 = line_1;
//    cout << line_6;
//
//    cout << (len_1 = line_1.Len()) << endl;
//    
//    line_3 = line_2;
//    cout << line_3 << endl;
//    
//    line_3[1] = 'f';
//    cout << line_3 << endl;
//    cout << line_3[3] << endl;
//
//    cout << (line_3 == line_4) << endl;
//    cout << (line_3 != line_4) << endl;
//    
//    line_3 = line_1 + line_2;
//    cout << line_3 << endl;
//    
//    cout << (line_1 += line_2) << endl;
//    
//    cin >> (line_5);
//    cout << (line_5);

    String str1 ("Per aspera ad astra. An apple a day keeps a doctor away"), str2 ("away");
    cout << (str1.BMH_search(str2)) << endl;
    
    return 0;
}