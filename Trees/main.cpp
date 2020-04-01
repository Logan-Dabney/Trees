// Trees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "SkipList.h"
#include "BST.h"
#include "RBT.h"
#include "AVL.h"
#include <time.h>

using namespace std;

int main()
{
    char c;
    double readInTime, treeTime;
    RBT* RBT_T = new RBT(); // instantiate each of the trees
    AVL* AVL_T = new AVL(); //
    BST* BST_T = new BST(); //
    SkipList* SL = new SkipList(); // and the skip list
    char chari[50]; // assumes no word is longer than 49 characters
    memset(chari, 0, 50); // zero the word buffer
    int iPtr;
    ifstream inFile;
    for (int pass = 0; pass < 6; pass++)
    {
        bool IsDelimiter = false, WasDelimiter = false;

        inFile.open("D:\\Shakespeare.txt", ios::binary);
        if (inFile.fail())
        {
            cout << "Unable to open input file\n\n"
                << "Program Exiting\n\nPress ENTER to exit\n";
            cin.get(c);
            exit(1);
        }
        iPtr = 0;
        clock_t start = clock();
        inFile.get(c); // priming read
        while (!inFile.eof())
        {
            IsDelimiter = (c == ' ' || c == 10 || c == 13 || c == ',' || c == '.' || c == '\'' ||
                c == ':' || c == ';' || c == '"' || c == '?' || c == '!' || c == '-' || c == '(' ||
                c == ')' || c == '[' || c == ']' || c == '_' || c == '*' || c == 9);
            if (IsDelimiter && !WasDelimiter) // if THIS character IS a delimiter, and the
            // last one WASN’T, it’s the end of a word
            {
                WasDelimiter = true;
                if (pass == 2) RBT_T->Insert(chari); // insert this word in the RBT
                else if (pass == 3) AVL_T->Insert(chari); // insert it in the AVL Tree
                else if (pass == 4) BST_T->Insert(chari); // insert it in the BST
                else if (pass == 5) SL->Insert(chari); // insert it in the skip list
                memset(chari, 0, 50); // zero the word buffer
                iPtr = 0;
            }
            else if (!IsDelimiter) // if this isn’t a delimiter, keep going
            {
                chari[iPtr++] = c;
            }
            else if (IsDelimiter && WasDelimiter)
            {
                // Do nothing -- two consecutive delimiters.
            }
            WasDelimiter = IsDelimiter; // for the NEXT iteration
            inFile.get(c);
        }
        inFile.close();

        if (pass == 2) { if (strlen(chari)) RBT_T->Insert(chari);} // RBT
        else if (pass == 3) { if (strlen(chari))AVL_T->Insert(chari);} // AVL
        else if (pass == 4) { if (strlen(chari)) BST_T->Insert(chari);} // BST
        else if (pass == 5) { if (strlen(chari)) SL->Insert(chari); } // skip list 
        clock_t end = clock();

        if (pass == 2) { RBT_T->GetData(); } // RBT
        else if (pass == 3) { AVL_T->GetData(); } // AVL
        else if (pass == 4) { BST_T->GetData(); } // BST
        else if (pass == 5) { SL->GetData(); } // skip list 

        if (pass == 1) readInTime = (double)(end - start) / 1000.0;
        else if (pass > 1) {
            treeTime = ((double)(end - start) / 1000.0) - readInTime;
            cout << "Time Elapsed: " << treeTime << "ms" << endl;
            cout << endl;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
