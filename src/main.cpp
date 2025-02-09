#include <iostream>
#include <thread>

#include "Fork.h"
#include "LeftHandedPhilosopher.h"
#include "RightHandedPhilosopher.h"

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

    const PhilosopherContext context { outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist };

    Fork fork1(1), fork2(2), fork3(3), fork4(4), fork5(5);

    // LeftHandedPhilosopher philosopher1(fork1, fork5, 1);
    // LeftHandedPhilosopher philosopher2(fork2, fork1, 2);
    // LeftHandedPhilosopher philosopher3(fork3, fork2, 3);
    // LeftHandedPhilosopher philosopher4(fork4, fork3, 4);
    // LeftHandedPhilosopher philosopher5(fork5, fork4, 5);

    LeftHandedPhilosopher  philosopher1(fork1, fork5, 1);
    RightHandedPhilosopher philosopher2(fork2, fork1, 2);
    LeftHandedPhilosopher  philosopher3(fork3, fork2, 3);
    RightHandedPhilosopher philosopher4(fork4, fork3, 4);
    LeftHandedPhilosopher  philosopher5(fork5, fork4, 5);

    std::jthread t0([&]
                    { philosopher1.start(context); });
    std::jthread t1([&]
                    { philosopher2.start(context); });
    std::jthread t2([&]
                    { philosopher3.start(context); });
    std::jthread t3([&]
                    { philosopher4.start(context); });
    std::jthread t4([&]
                    { philosopher5.start(context); });

    return 0;
}
