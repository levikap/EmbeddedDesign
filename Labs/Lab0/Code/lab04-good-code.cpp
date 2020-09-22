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

void sort(int randomarray[], int arraysize)
{
    int min;

    for(int i = 0; i < arraysize; i++)
        {
            min = i;
            for(int j = 0; j < arraysize; j++)
            {
                if(randomarray[min] < randomarray[j])
                {
                    min = j;
                }
                swap(&randomarray[min], &randomarray[i]);
            }
        }

    cout << &min << endl;
}

int main()
{
    //Create an array to hold 10 integer values: randomarray
    int arraysize = 10;
    int randomarray[arraysize];
    // Generate 10 ranodm integer values and save them to randomarray
    srand(time(NULL));
    for(int i = 0; i < arraysize; i++)
    {
        randomarray[i] = rand() % 100;
    }
    // Display randomarray
        for(int i = 0; i < arraysize; i++)
    {
        cout << randomarray[i] << endl;
    }
    // Sort randomarray in ascending order
    sort(randomarray, arraysize);
    // Display randomarray
    cout << endl;
       for(int i = 0; i < arraysize; i++)
    {
        cout << randomarray[i] << endl;
    }

    // display addresses
    for (int i = 0; i < arraysize; i++)
    {
      cout << &randomarray[i] << endl;
    }
    cout << &arraysize << endl;

    return 0;
}
