#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void swap(int *min, int *current)
{
    int temp = *min;
    *min = *current;
    *current = temp;

}

void RandomArray(int v[], int size)
{
  srand(time(NULL));
  for(int i = 0; i < size; i++)
  {
      v[i] = rand() % 100;
  }
}

void PrintArray(int v[], int size)
{
  for(int i = 0; i < size; i++)
  {
  cout << v[i] << endl;
  }
}

void SortArray(int v[], int size)
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
    //Create an array to hold 10 integer values: randomarray
    int arraysize = 10;
    int randomarray[arraysize];
    // Generate 10 ranodm integer values and save them to randomarray
    RandomArray(randomarray, arraysize);
    // Display randomarray
    PrintArray(randomarray, arraysize);
    // Sort randomarray in ascending order
    SortArray(randomarray, arraysize);
    // Display randomarray
    cout << endl;
    PrintArray(randomarray, arraysize);
    return 0;
}
