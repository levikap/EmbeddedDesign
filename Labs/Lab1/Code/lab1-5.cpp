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
int RunMenu();
// selectStatement method stub
int SelectStatement(char selection);
// Grow method stub
void Grow();
// AddElement method stub
void AddElement(double element);
// PrintVector method stub
void PrintVector();
// RemoveElement method stub
void RemoveElement();
// InsertElement method stub
void InsertElement(int index, double element);
// Shrink method stub
void Shrink();

/*
 * Initializes the vector values and runs the menu.
 * @return : int representing the user's desire to quit the program
 */
int main()
{
  Initialize();
  return RunMenu();
}

/*
 * Runs the menu, displaying menu options and getting user input.
 * @return : int if the program is exited, representing the user wanting to quit the program
 */
int RunMenu()
{
  char selection;
  cout << menuString;
  cin >> selection;
  return SelectStatement(selection);
}

/*
 * Represents logic for performing the desired action as specified by the user.
 * @param : selection the character selected by the user to be used for the switch
 * @return : 0 if the program is exited, otherwise recurs on runMenu()
 */
int SelectStatement(char selection)
{
  double newElem;
  int index;
  double elem;
  switch (selection) {
    // print the array
    case '1':
      cout << "Print the array" << endl;
      PrintVector();
      RunMenu();
      break;
    // append element at end
    case '2':
      cout << "Append element at the end" << endl;
      cout << "Enter the new element: _";
      cin >> newElem;
      AddElement(newElem);
      RunMenu();
      break;
    // remove last element
    case '3':
      cout << "Remove last element" << endl;
      RemoveElement();
      RunMenu();
      break;
    // insert one element
    case '4':
      cout << "Insert one element" << endl;
      cout << "Enter the index of new element: _";
      cin >> index;
      cout << endl;
      cout << "Enter the new element: _";
      cin >> elem;
      InsertElement(index, elem);
      RunMenu();
      break;
    // exit the program
    case '5':
      Finalize();
      return 0;
      break;
    // if invalid, display an error and run the menu again
    default:
      cout << "Error: please enter a valid option" << endl;
      RunMenu();
      break;
  }
}

/*
 * Initializes vector values
 */
void Initialize()
{
  size = 0;
  count = 0;
  v = new double[size];
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
/*
 * adds the passed-in element to the end of the vector.
 * @param double : the element to add to the end of the vector
 */
void AddElement(double element)
{
  // if the size is 0, we want to add the element at the first slot and increment count and size
  if(size == 0)
  {
    v[0] = element;
    count = count + 1;
    size = size + 1;
  }
  // otherwise, if size is greater than count, we don't need to Grow the vector, so just add it
  else if(size > count)
  {
    v[count] = element;
    count = count + 1;
  }
  // size is equal to count -- the vector needs to be grown  before more can be added
  else
  {
    // grow the vector
    Grow();
    // recursively call AddElement now that the vector has grown
    AddElement(element);
  }
}

/*
 * Prints the vector to the console.
 */
void PrintVector()
{
  // establish opening bracket
  cout << "[";
  // if there's an element present, add the elements
  if(count > 0)
  {
    // if there's just one element, we just add the first element
    if (count == 1)
    {
    cout << v[0];
    // there are multiple elements -- loop through them all
    } else {
      for(int i = 0; i < count - 1; i++) {
        cout << v[i] << ", ";
      }
      // print out the last element
      cout << v[count - 1];
    }
  }
  // close out the braces
  cout << "]" << endl;
}

/*
 * Removes an element from the end of the Vector.
 */
 void RemoveElement()
 {
   // initializes pointer to cv
   double *cv;
   // sets cvSize equal to the size of v
   int cvSize = size;
   // initializes cv
   cv = new double[cvSize];
   // if the size is zero, there's nothing to remove, so tell the user
   if(count == 0)
   {
     cout << "Could not perform: there are no elements left to remove" << endl;
   } else {
     // for each element in v up to but not including the last element,
      // set that same index in cv equal to its value
     for(int i = 0; i < count - 1; i++)
     {
       double val = v[i];
       cv[i] = val;
     }
     // reduce the count if the count is greater than 0
     if (count > 0) {
       count = count - 1;
     }
     // delete v
     delete[] v;
     // set to now point to cv
     v = cv;

    if(count < size * 0.3) {
      Shrink();
    }
   }
 }


/*
 * Inserts the given element at the given index. The index should be between 0 and count.
 * @Param index : int - the index for which to insert the element
 * @ Param element : double - the element to insert at the given index
 */
 void InsertElement(int index, double element) {
   // check for invalid params - the index should be in the range [0, count]
   if (index > count || index < 0)
   {
     // print the error message
     cout << "Index out of range. Please pick an index between 0 and the vector's count" << endl;
   // the index is valid - insert the element at the appropriate index
   } else {
     // Grow the vector preemptively to account for the new element
     Grow();
   // shift the elements in the vector up to the index inserted at one to the right
    for(int i = count; i >= index + 1; i--)
    {
      v[i] = v[i - 1];
    }
    // insert the element at the index specified
    v[index] = element;
    // increase the count of the vector
    count = count + 1;
  }
 }

/*
 * Reallocates the Vector with 50% capacity.
 */
 void Shrink()
 {
  // initialize pointer to the small vector (sv)
  double *sv;
  // sets svSize equal to the size of v divided by 2
  int svSize = size / 2;
  // initializes sv
  sv = new double[svSize];
  // for each element in v, set that same index in sv equal to its value
  for(int i = 0; i < count; i++)
  {
    double val = v[i];
    sv[i] = val;
  }
  // delete v
  delete[] v;
  // set to now point to sv
  v = sv;

  // print debug info
  cout << "Shrunk the vector" << endl;
  cout << "Previous capacity: " << size << endl;
  cout << "New capacity: " << svSize << endl;
  // set the size equal to the new size
  size = svSize;
 }
