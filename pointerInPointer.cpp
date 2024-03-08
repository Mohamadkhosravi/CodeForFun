
#include <iostream>
/*
 An example of a pointer to a pointer using dynamic memory(new/delete ) to create a pointer that holds the address of other pointers.
 */
int main ()
{
#define rows 10
#define cols 1

  int **tabale = new int *[rows];
  for (int i = 0; i < rows; i++)
	{
	  tabale[i] = new int[cols];
	  tabale[i][cols] = i + 10;
	}
  std::cout << tabale[0][cols] << std::endl;
  std::cout << tabale[1][1] << std::endl;
  std::cout << tabale[2][1] << std::endl;
  std::cout << tabale[3][1] << std::endl;
  std::cout << tabale[4][1] << std::endl;
  std::cout << tabale[5][1] << std::endl;

  for (int i = 0; i < rows; i++)
	{
	  delete[]tabale[i];
	}

  delete[]tabale;
  tabale = NULL;

  return 0;
}
