#include <iostream>
#include <thread>

#include "Fork.h"
#include "SelfishPhilosopher.h"

namespace
{
    constexpr int MinThinkingTime = 100;
    constexpr int MaxThinkingTime = 300;
    constexpr int MinEatingTime = 200;
    constexpr int MaxEatingTime = 500;
}

int main()
{
    std::cout << "Dining Philosophers Problem" << std::endl;

    std::mutex outputMutex;

    std::mutex                      randomMutex;
    std::random_device              rd;
    std::mt19937                    randomGenerator(rd());
    std::uniform_int_distribution<> thinkingTimeDist(MinThinkingTime, MaxThinkingTime);
    std::uniform_int_distribution<> eatingTimeDist(MinEatingTime, MaxEatingTime);

    Fork fork1(1), fork2(2), fork3(3), fork4(4), fork5(5);

    SelfishPhilosopher philosopher1(fork1, fork2, 1);
    SelfishPhilosopher philosopher2(fork2, fork3, 2);
    SelfishPhilosopher philosopher3(fork3, fork4, 3);
    SelfishPhilosopher philosopher4(fork4, fork5, 4);
    SelfishPhilosopher philosopher5(fork5, fork1, 5);

    std::jthread t0([&]
                    { philosopher1.start(outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist); });
    std::jthread t1([&]
                    { philosopher2.start(outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist); });
    std::jthread t2([&]
                    { philosopher3.start(outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist); });
    std::jthread t3([&]
                    { philosopher4.start(outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist); });
    std::jthread t4([&]
                    { philosopher5.start(outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist); });

    return 0;
}
