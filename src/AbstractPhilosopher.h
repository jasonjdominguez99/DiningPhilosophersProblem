#pragma once

#include <mutex>

class Fork;

class AbstractPhilosopher
{
public:
    explicit AbstractPhilosopher(std::mutex& outputMutex, Fork& leftFork, Fork& rightFork, const unsigned int id);
    virtual ~AbstractPhilosopher() = default;

    void start();

protected:
    virtual void eat() = 0;

    void think();

protected:
    std::mutex& m_outputMutex;

    Fork& m_leftFork;
    Fork& m_rightFork;

    const unsigned int m_id;
};
