#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
#include <cstring>
#include <set>
#include <cctype>
#include <thread>

using namespace std;

// Function to be executed by the first thread
void threadFunction1()
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 1: " << i << std::endl;
    }
}

// Function to be executed by the second thread
void threadFunction2()
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 2: " << i << std::endl;
    }
}

int main()
{

    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);
    std::thread t3(threadFunction1);

    cout << t1.get_id() << endl;
    cout << t2.get_id() << endl;

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Main function continues..." << std::endl;

    return 0;
}
