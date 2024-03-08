
#include <iostream>
#include <vector>
using namespace std;

/*
  state machine without using any condition and 
  using from function pointer
*/
bool ascendingCompair(int number1, int number2)
{
  if (number1 > number2)
    return true;
  else
    return false;
}
bool descendingCompair(int number1, int number2)
{
  if (number1 < number2)
    return true;
  else
    return false;
}

void customSort(vector<int> numbers, bool (*sortFunction)(int, int))
{

  for (int i = 0; i < numbers.size(); i++)
  {
    for (int j = 0; j < numbers.size(); j++)
    {
      if (sortFunction(numbers[i], numbers[j]))
      {
        swap(numbers[i], numbers[j]);
      }
    }
  }
  for (int i = 0; i < numbers.size(); i++)
  {
    cout << numbers[i] << endl;
  }
}
int main()
{
  vector<int> arrayOfIntegers = {77, 3, 4, 6, 32, 1};
  bool (*sortFunc)(int, int) = descendingCompair;
  customSort(arrayOfIntegers, sortFunc);
  customSort(arrayOfIntegers, ascendingCompair);

  return 0;
}
