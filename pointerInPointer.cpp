/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

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
