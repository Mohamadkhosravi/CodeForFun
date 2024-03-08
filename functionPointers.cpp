#include <iostream>

//How to use function as function input using function address and pointers (callback function)

int sum(int a, int b);
int sub(int a, int b);
int mult(int a, int b);
int dive(int a, int b);

int main()
{

  int chose;
  int number1;
  int number2;
  int result;

  std::cout << "number1=" << std::endl;
  std::cin >> number1;

  std::cout << "number2=" << std::endl;
  std::cin >> number2;

  std::cout << "chose=" << std::endl;
  std::cin >> chose;

  int (*math[4])(int a, int b);

  math[0] = sum;
  math[1] = sub;
  math[2] = mult;
  math[3] = dive;

  result = math[chose](number1, number2);

  std::cout << "result=" << std::endl;
  std::cout << result << std::endl;
  return 0;
};

int sum(int a, int b)
{
  return a + b;
};

int sub(int a, int b)
{
  return a - b;
};

int mult(int a, int b)
{
  return a * b;
};

int dive(int a, int b)
{
  return a / b;
};
