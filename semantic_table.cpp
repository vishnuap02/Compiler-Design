// Vishnu Abhay Parvatikar

#include <iostream>
#include <string>
#include <vector>
// #include <bits/stdc++.h>
using namespace std;

class Semantics
{
    int n;
    char plines[100][100];

public:
    bool ispresent(string word, int line, int *ct)
    {
        int j = 0, k = 0;
        bool res = false;
        while (plines[line][j] != '$')
        {
            // When first letter is matched , the other letters too must match , so the below condition
            if ((k == 0) || ((k != 0) && (res == true)))
                if (plines[line][j] == word[k])
                {
                    res = true;
                    // cout << "\n At line " << line << " and character " << j << " , " << plines[line][j] << " is detected!!";
                    // cout << plines[line][j];
                    k++;
                    if (word[k] == '\0')
                        break;
                    j++;
                    continue;
                }
            res = false;
            j++;
        }
        *ct = j + 1;
        return res;
    }
    void semTable()
    {
        // cycle one find all Tuples by variable name and type
        // 1st ly int.
        for (int i = 0; i < n; i++)
        {
            int j = 0, *ct = 0;

            if (ispresent("int", i, ct))
            {
                // run until end of line
                cout << "\n Yay!!";
                j = *ct;
                while (plines[i][j] != '$')
                {
                    if (plines[i][j] == ' ')
                    {
                        j++;
                        continue;
                    }
                                }
                cout << plines[i] << endl;
            }
        }
    }
    void storeString(FILE *ptr)
    {
        char ch;
        int j = 0;
        n = 0;
        do
        {
            ch = fgetc(ptr);
            if (ch == '\n')
            {
                n++;
                plines[n][j] = '$'; //$ indicates end of that line.
                j = 0;
                continue;
            }
            plines[n][j++] = ch;
        } while (ch != EOF);
        // for (int i = 0; i < n; i++)
        // {
        //     cout << plines[i] << endl;
        // }
    }
};

int main()
{
    Semantics s;
    FILE *ptr;
    ptr = fopen("program_input.txt", "r");
    if (ptr == NULL)
    {
        printf("\n File not Read..");
        return 0;
    }
    s.storeString(ptr);
    s.semTable();
    return 0;
}