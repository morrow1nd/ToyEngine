#include <iostream>
#include <cstdlib>

#include <vector>
#include <memory>


using namespace std;


int main()
{
    std::cout << sizeof(std::vector<int>) << std::endl;
    std::cout << sizeof(std::vector<std::vector<int>>) << std::endl;
    std::cout << sizeof(shared_ptr<int>) << std::endl;

    system("pause");
    return 0;
}