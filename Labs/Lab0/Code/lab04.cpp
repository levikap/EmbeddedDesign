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
    cout << &arraysize << endl;
    cout << &randomarray << endl;
    cout << &min << endl;
    for(int i = 0; i < arraysize; i++)
    {
     cout << &randomarray[i] << endl;
   }
    // Sort randomarray in ascending order
    int min;
    // go through each element
    for(int i = 0; i < arraysize; i++)
        {
            // set the min equal to the current element
            min = i;
            // see if it's actually the min, if not set min equal to smaller number
            for(int j = 0; j < arraysize; j++)
            {
                if(randomarray[min] < randomarray[j])
                {
                    min = j;
                }
                // swap the two numbers in the array
                swap(&randomarray[min], &randomarray[i]);
            }
        }
    // Display randomarray
    cout << endl;
       for(int i = 0; i < arraysize; i++)
    {
        cout << randomarray[i] << endl;
    }

    // display addresses
    cout << &arraysize << endl;
    cout << &randomarray << endl;
    cout << &min << endl;
    for(int i = 0; i < arraysize; i++)
    {
     cout << &randomarray[i] << endl;
   }

  return 0;
}
