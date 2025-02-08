#include <iostream>
#include <thread>

#include "Fork.h"
#include "SelfishPhilosopher.h"

int main()
{
    std::cout << "Dining Philosophers Problem" << std::endl;

    std::mutex outputMutex;
    Fork       fork1(1), fork2(2), fork3(3), fork4(4), fork5(5);

    SelfishPhilosopher philosopher1(outputMutex, fork1, fork2, 1);
    SelfishPhilosopher philosopher2(outputMutex, fork2, fork3, 2);
    SelfishPhilosopher philosopher3(outputMutex, fork3, fork4, 3);
    SelfishPhilosopher philosopher4(outputMutex, fork4, fork5, 4);
    SelfishPhilosopher philosopher5(outputMutex, fork5, fork1, 5);

    std::jthread t0([&]
                    { philosopher1.start(); });
    std::jthread t1([&]
                    { philosopher2.start(); });
    std::jthread t2([&]
                    { philosopher3.start(); });
    std::jthread t3([&]
                    { philosopher4.start(); });
    std::jthread t4([&]
                    { philosopher5.start(); });

    return 0;
}
