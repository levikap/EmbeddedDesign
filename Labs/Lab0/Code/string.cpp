#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void swap(string *min, string *current)
{
    string temp = *min;
    *min = *current;
    *current = temp;

}

void PrintArray(string v[], int size)
{
  for(int i = 0; i < size; i++)
  {
  cout << v[i] << endl;
  }
}

void SortArray(string v[], int size)
{
  int min;
  // go through each element
  for(int i = 0; i < size; i++)
      {
          // set the min equal to the current element
          min = i;
          // see if it's actually the min, if not set min equal to smaller number
          for(int j = 0; j < size; j++)
          {
              if(v[min] < v[j])
              {
                  min = j;
              }
              // swap the two numbers in the array
              swap(&v[min], &v[i]);
          }
      }
}

int main()
{
    //Create an array to hold 10 integer values: stringarray
    int arraysize = 10;
    string a, b, c, d, e, f, g, h, i, j;
    string stringarray[arraysize];
    // read input from the console
    cin >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j;
    stringarray[0] = a;
    stringarray[1] = b;
    stringarray[2] = c;
    stringarray[3] = d;
    stringarray[4] = e;
    stringarray[5] = f;
    stringarray[6] = g;
    stringarray[7] = h;
    stringarray[8] = i;
    stringarray[9] = j;
    // Sort randomarray in alphabetical order
    SortArray(stringarray, arraysize);
    // Display stringarray
    PrintArray(stringarray, arraysize);
    return 0;
}
