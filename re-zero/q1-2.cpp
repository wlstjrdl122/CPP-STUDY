/*
여러분은 아래와 같은 Date 클래스를 디자인 하려고 합니다. SetDate 는 말그대로 Date 함수
내부를 초기화 하는 것이고 AddDay, AddMonth, AddYear 는 일, 월, 년을 원하는 만큼 더하게
됩니다. 한 가지 주의할 점은 만일 2012 년 2 월 28 일에 3 일을 더하면 2012 년 2 월 31 일이 되는
것이 아니라 2012 년 3 월 2 일이 되겠지요? (난이도 : 上)

class Date
{
  int year_;
  int month_; // 1 부터 12 까지.
  int day_;   // 1 부터 31 까지.
public:
  void SetDate(int year, int month, int date);
  void AddDay(int inc);
  void AddMonth(int inc);
  void AddYear(int inc);
  void ShowDate();
};
*/

#include <iostream>

class Date
{
  int year = -1;
  int month[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  int normal_mon_day_list[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int yun_mon_day_list[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int check_month_index()
  {
    for (int i = 1; i <= 12; i++)
    {
      if (month[i] != 0)
      {
        return i;
      }
    }
  }

public:
  void SetDate(int year, int month, int date);
  void AddDay(int inc);
  void AddMonth(int inc);
  void AddYear(int inc);
  void ShowDate();
};

void Date::SetDate(int arg_year, int arg_month, int arg_day)
{
  if ((1 <= arg_month <= 12) && (1 <= arg_day <= 31))
  {
    if ((arg_month == 2) && (arg_day >= 30))
    {
      std::cout << "not exist " << arg_month << "." << arg_day << "\n";
    }
    else
    {
      year = arg_year;
      month[arg_month] = arg_day;
      month[0] = 1;
    }
  }
  else
  {
    std::cout << "not exist " << arg_month << "." << arg_day << "\n";
  }
}

void Date::AddDay(int inc)
{
  int month_index = check_month_index();
  int day = month[month_index];

  int max_day = 0;
  if ((year % 4) == 0 && (year % 100) != 0 || (year % 400) == 0)
  {
    max_day = yun_mon_day_list[month_index];
  }
  else
  {
    max_day = normal_mon_day_list[month_index];
  }

  day += inc;
  if (day > max_day)
  {
    day -= max_day;
    month[month_index] = 0;
    month_index += 1;

    if (month_index > 12)
    {
      month_index -= 12;
    }

    month[month_index] = day;
  }
}

void Date::AddMonth(int inc)
{
  int month_index = check_month_index();
  int day = month[month_index];

  month[month_index] = 0;
  month_index += inc;

  if (month_index > 12)
  {
    month_index -= 12;
  }

  month[month_index] = day;
}

void Date::AddYear(int inc)
{
  if (-100000 < year + inc < 100000)
  {
    year += inc;
  }
  else
  {
    std::cout << "year or inc is too big" << "\n";
  }
}

void Date::ShowDate()
{
  if ((month[0] == 0))
  {
    std::cout << "you must `set date` first\n";
  }
  else
  {
    for (int i = 1; i <= 12; i++)
    {
      if (month[i] != 0)
      {
        std::cout << year << "." << i << "." << month[i] << "\n";
      }
    }
  }
}

int main()
{
  Date n1;
  n1.ShowDate();

  n1.SetDate(2020, 8, 16);
  n1.ShowDate();

  n1.AddMonth(3);
  n1.ShowDate();

  n1.AddMonth(3);
  n1.ShowDate();

  n1.AddDay(5);
  n1.ShowDate();

  n1.AddDay(20);
  n1.ShowDate();

  return 0;
}