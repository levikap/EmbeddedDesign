#include <iostream>
#include <string>

using namespace std;

// vector values
double *v;
int count;
int size;
// string representing menu options
string menuString = "Main menu:\n1. Print the array\n2. Append element at the end\n3. Remove last element\n4. Insert one element\n5. Exit \nSelect an option: _";

// Initialize method stub
void Initialize();
// Finalize method stub
void Finalize();
// runMenu method stub
int runMenu();
// selectStatement method stub
int selectStatement(char selection);
// Grow method stub
void Grow();

/*
 * Initializes the vector values and runs the menu.
 * @return : int representing the user's desire to quit the program
 */
int main()
{
  Initialize();
  Grow();
  return runMenu();
}

/*
 * Runs the menu, displaying menu options and getting user input.
 * @return : int if the program is exited, representing the user wanting to quit the program
 */
int runMenu()
{
  char selection;
  cout << menuString;
  cin >> selection;
  return selectStatement(selection);
}

/*
 * Represents logic for performing the desired action as specified by the user.
 * @param : selection the character selected by the user to be used for the switch
 * @return : 0 if the program is exited, otherwise recurs on runMenu()
 */
int selectStatement(char selection)
{
  switch (selection) {
    // print the array
    case '1':
      cout << "Print the array" << endl;
      runMenu();
    // append element at end
    case '2':
      cout << "Append element at the end" << endl;
      runMenu();
    // remove last element
    case '3':
      cout << "Remove last element" << endl;
      runMenu();
    // insert one element
    case '4':
      cout << "Insert one element" << endl;
      runMenu();
    // exit the program
    case '5':
      Finalize();
      return 0;
      break;
    // if invalid, display an error and run the menu again
    default:
      cout << "Error: please enter a valid option" << endl;
      runMenu();
  }
}

/*
 * Initializes vector values
 */
void Initialize()
{
  size = 2;
  count = 2;
  v = new double[size];
  // test values for testing purposes
  v[0] = 1;
  v[1] = 2;
}

/*
 * Deletes vector to free up memory space
 */
void Finalize()
{
  delete[] v;
}

/*
 * Doubles the size in memory of the array v .
 */
void Grow()
{
  // initializes pointer to nv
  double *nv;
  // sets nvSize equal to a doubling of the current size
  int nvSize = size * 2;
  // initializes nv
  nv = new double[nvSize];
  // for each element in v, set that same index in nv equal to its value
  for(int i = 0; i < count; i++)
  {
    double val = v[i];
    nv[i] = val;
  }
  // delete v
  delete[] v;
  // set to now point to nv
  v = nv;

  // print the details of the Grow() call
  cout << "Vector grown" << endl;
  cout << "Previous capacity: " << size << " elements" << endl;
  cout << "New capacity: " << nvSize << " elements" << endl;
  // set the new size equal to nvSize
  size = nvSize;
}
