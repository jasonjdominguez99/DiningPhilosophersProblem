#include "AbstractPhilosopher.h"

#include "Fork.h"

#include <iostream>
#include <thread>

AbstractPhilosopher::AbstractPhilosopher(std::mutex& outputMutex, Fork& leftFork, Fork& rightFork, const unsigned int id) :
    m_outputMutex(outputMutex),
    m_leftFork(leftFork),
    m_rightFork(rightFork),
    m_id(id)
{
}

void AbstractPhilosopher::start()
{
    while (true)
    {
        think();
        eat();
    }
}

void AbstractPhilosopher::think()
{
    {
        std::lock_guard<std::mutex> lock(m_outputMutex);
        std::cout << "Philosopher " << m_id << " THINKING" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
