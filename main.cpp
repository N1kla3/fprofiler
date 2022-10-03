#include <iostream>
#include <thread>
#include "Core.h"

using namespace omp::prof;

void function()
{
    PROFILE_FUNCTION()
    int x = 0;
    for (int i = 0; i < 11111111; i++)
    {
        x = 1 * 2 * 3 * 4 * 5;
    }
}

int main() {
    PROFILE_THREAD("Main")
    std::cout << "Hello, World!" << std::endl;
    //function();
    std::cout << std::this_thread::get_id() << std::endl;
    std::thread first([](){
        PROFILE_THREAD("first")
        PROFILE_FUNCTION_NAME("Lyamda")
        function();
        std::cout << std::this_thread::get_id() << std::endl;
    });
    std::thread second([](){
        PROFILE_THREAD("second")
        PROFILE_FUNCTION()
        for (int i = 0; i < 10; i++)
        {
            std::cout << std::this_thread::get_id() << std::endl;
        }
    });
    first.join();
    second.join();
    std::thread third([](){
        PROFILE_THREAD("third")
        std::cout << std::this_thread::get_id() << std::endl;
    });
    third.join();
    return 0;
}
