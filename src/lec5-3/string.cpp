#include <iostream>
#include <string.h>

class MyString
{
  char *string_content; // 문자열 값 포인터
  int string_length;    // 문자열 길이

public:
  MyString(char c);              // 문자 하나로 생성
  MyString(const char *str);     // 문자열로 부터 생성
  MyString(const MyString &str); // 복사 생성자

  ~MyString();

  int length() const;
  void print() const;
  void println() const;
};

/**
 * @param c 문자 하나로 생성
 * @returns
 */
MyString::MyString(char c)
{
  string_content = new char[1];
  string_content[0] = c;
}

/**
 * @param *str 문자열로부터 생성
 * @returns
 */
MyString::MyString(const char *str)
{
  string_length = strlen(str);
  string_content = new char[string_length];
  for (int i = 0; i != string_length; i++)
  {
    string_content[i] = str[i];
  }
}

/**
 * @param MyString_&str 복사생성자
 * @returns
 */
MyString::MyString(const MyString &str)
{
  string_length = str.string_length;
  string_content = new char[string_length];
  for (int i = 0; i != string_length; i++)
    string_content[i] = str.string_content[i];
}

MyString::~MyString() { delete[] string_content; }

/**
 * @param
 * @returns string_length
 */
int MyString::length() const { return string_length; }

void MyString::print() const
{
  for (int i = 0; i != string_length; i++)
  {
    std::cout << string_content[i];
  }
}

/**
 * @note print all strings
 */
void MyString::println() const
{
  for (int i = 0; i != string_length; i++)
  {
    std::cout << string_content[i];
  }

  std::cout << std::endl;
}

int main()
{
  MyString str1("hello world!");
  MyString str2(str1);
  str1.println();
  str2.println();
}