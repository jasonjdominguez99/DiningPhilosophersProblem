#include <iostream>
#include <stop_token>
#include <thread>

#include "Fork.h"
#include "LeftHandedPhilosopher.h"
#include "OrderedPhilosopher.h"
#include "RightHandedPhilosopher.h"

namespace
{
    constexpr int MinThinkingTime = 100;
    constexpr int MaxThinkingTime = 300;
    constexpr int MinEatingTime = 200;
    constexpr int MaxEatingTime = 500;
    constexpr int TotalRunTime = 10000; // milliseconds
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

    // LeftHandedPhilosopher  philosopher1(fork1, fork5, 1);
    // RightHandedPhilosopher philosopher2(fork2, fork1, 2);
    // LeftHandedPhilosopher  philosopher3(fork3, fork2, 3);
    // RightHandedPhilosopher philosopher4(fork4, fork3, 4);
    // LeftHandedPhilosopher  philosopher5(fork5, fork4, 5);

    OrderedPhilosopher philosopher1(fork1, fork5, 1);
    OrderedPhilosopher philosopher2(fork2, fork1, 2);
    OrderedPhilosopher philosopher3(fork3, fork2, 3);
    OrderedPhilosopher philosopher4(fork4, fork3, 4);
    OrderedPhilosopher philosopher5(fork5, fork4, 5);

    std::jthread t0([&](std::stop_token stopToken)
                    { philosopher1.start(context, stopToken); });
    std::jthread t1([&](std::stop_token stopToken)
                    { philosopher2.start(context, stopToken); });
    std::jthread t2([&](std::stop_token stopToken)
                    { philosopher3.start(context, stopToken); });
    std::jthread t3([&](std::stop_token stopToken)
                    { philosopher4.start(context, stopToken); });
    std::jthread t4([&](std::stop_token stopToken)
                    { philosopher5.start(context, stopToken); });

    std::this_thread::sleep_for(std::chrono::milliseconds(TotalRunTime));
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Stopping philosophers..." << std::endl;
    }

    return 0;
}
