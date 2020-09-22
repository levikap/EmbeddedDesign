#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void duplicatearray(int arraysize, int randomarray, int arrayalias)
{
for(int i = 0; i < arraysize; i++) {
        arrayalias[i] = randomarray[i];
}
}

int main()
{
//Create an array to hold 10 integer values: randomarray
int arraysize = 10;
int randomarray[arraysize];
int arrayalias[arraysize];
// Generate 10 ranodm integer values and save them to randomarray
srand(time(NULL));
for(int i = 0; i < arraysize; i++)
{
        randomarray[i] = rand() % 100;
}
// Display randomarray
for(int j = 0; j < arraysize; j++)
{
        cout << randomarray[j] << endl;
}
// Sort randomarray in ascending order
int min = randomarray[0];
duplicatearray();
for(int k = 0; k < arraysize-1; k++)
{
int min = k;
        for(int l = 0; l < arraysize; l++)
        {
                if(randomarray[l] < randomarray[min])
                {
                        min = l;
                }
        }
if(min != k)
{
        randomarray[k] = arrayalias[min];
        randomarray[min] = arrayalias[k];
        duplicatearray();
        }
        }
        // Display randomarray
        return 0;
        }
