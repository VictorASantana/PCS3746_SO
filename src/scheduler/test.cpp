#include <iostream>
#include <deque>

using namespace std;

int main()
{
    deque<int> teste = {1, 2, 3, 4, 5};
    int a = teste.front();
    cout << a;
    for (int &i : teste)
    {
        std::cout << i << ' ';
    }
    teste.push_back(6);
    for (int &i : teste)
    {
        std::cout << i << ' ';
    }
    return 0;
}