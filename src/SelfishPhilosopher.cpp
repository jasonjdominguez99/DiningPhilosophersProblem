#include "SelfishPhilosopher.h"
#include "Fork.h"

#include <iostream>
#include <mutex>
#include <thread>

SelfishPhilosopher::SelfishPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) noexcept :
    AbstractPhilosopher(leftFork, rightFork, id)
{
}

void SelfishPhilosopher::eat(std::mutex& outputMutex, const TimeGenerator& eatingTimeGenerator)
{
    std::unique_lock<Fork> leftForkLock(m_leftFork);
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Philosopher " << m_id << " grabbed FORK " << m_leftFork.getId() << std::endl;
    }

    std::unique_lock<Fork> rightForkLock(m_rightFork);
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Philosopher " << m_id << " grabbed FORK " << m_rightFork.getId() << std::endl;
    }

    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Philosopher " << m_id << " EATING" << std::endl;
    }

    const int eatingTime = getRandomTime(eatingTimeGenerator);
    std::this_thread::sleep_for(std::chrono::milliseconds(eatingTime));

    leftForkLock.unlock();
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Philosopher " << m_id << " let go of FORK " << m_leftFork.getId() << std::endl;
    }

    rightForkLock.unlock();
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Philosopher " << m_id << " let go of FORK " << m_rightFork.getId() << std::endl;
    }
}
