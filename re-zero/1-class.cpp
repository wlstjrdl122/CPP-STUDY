#include <iostream>

class Human
{
  int age;
  int money;

public:
  /**
   * @param arg_age {int} 나이
   * @param arg_money {int} 돈
   */
  void set_human(int arg_age, int arg_money)
  {
    age = arg_age;
    money = arg_money;
  }

  void get_money(int arg_money)
  {
    money += arg_money;
  }

  void print_status()
  {
    std::cout << "나이: " << age << "\t | 돈: " << money << "\n";
  }
};

int main()
{
  Human first_human;
  first_human.set_human(20, 100);
  first_human.print_status();

  first_human.get_money(10);
  first_human.print_status();

  return 0;
}