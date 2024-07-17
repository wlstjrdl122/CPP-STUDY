#include <iostream>

class Animal {
  private:
    int food;
    int weight;

  public:
    void set_animal(int _food, int _weight) {
      food = _food;
      weight = _food;
    }

    void increase_food(int increase) {
      food += increase;
      weight += increase / 3;
    }

    void view_status() {
      std::cout << "animal's food: " << food << "\n";
      std::cout << "animal's weight: " << weight << "\n";
    }
};

int test(){
  std::cout << "test func \n";
  return 123;
}

int main()
{
  int ga111o = test();

  std::cout << ga111o;
  std::cout << ga111o;

  Animal first_animal;
  
  first_animal.set_animal(123,123);
  first_animal.view_status();

  first_animal.increase_food(1000);
  first_animal.view_status();


  return 0;
}
