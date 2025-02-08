#pragma once

#include <mutex>
#include <random>

class Fork;

class AbstractPhilosopher
{
public:
    explicit AbstractPhilosopher(Fork&              leftFork,
                                 Fork&              rightFork,
                                 const unsigned int id);
    virtual ~AbstractPhilosopher() = default;

    void start(std::mutex&                      outputMutex,
               std::mutex&                      randomMutex,
               std::mt19937&                    randomGenerator,
               std::uniform_int_distribution<>& thinkingTimeDist,
               std::uniform_int_distribution<>& eatingTimeDist);

protected:
    virtual void eat(std::mutex&                      outputMutex,
                     std::mutex&                      randomMutex,
                     std::mt19937&                    randomGenerator,
                     std::uniform_int_distribution<>& eatingTimeDist) = 0;

    void think(std::mutex&                      outputMutex,
               std::mutex&                      randomMutex,
               std::mt19937&                    randomGenerator,
               std::uniform_int_distribution<>& thinkingTimeDist);

protected:
    Fork& m_leftFork;
    Fork& m_rightFork;

    const unsigned int m_id;
};
