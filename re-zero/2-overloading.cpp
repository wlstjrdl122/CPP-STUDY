#include <iostream>

void print(int a) { std::cout << "int " << a << "\n"; }
void print(double a) { std::cout << "double " << a << "\n"; }

int main()
{
  print(1);
  print(1.1);

  return 0;
}