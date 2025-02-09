#pragma once

#include <mutex>
#include <random>

class Fork;

struct PhilosopherContext
{
    std::mutex&                      outputMutex;
    std::mutex&                      randomMutex;
    std::mt19937&                    randomGenerator;
    std::uniform_int_distribution<>& thinkingTimeDist;
    std::uniform_int_distribution<>& eatingTimeDist;
};

struct TimeGenerator
{
    std::mutex&                      randomMutex;
    std::mt19937&                    randomGenerator;
    std::uniform_int_distribution<>& timeDist;
};

class AbstractPhilosopher
{
public:
    explicit AbstractPhilosopher(Fork&              leftFork,
                                 Fork&              rightFork,
                                 const unsigned int id) noexcept;
    virtual ~AbstractPhilosopher() = default;

    AbstractPhilosopher(const AbstractPhilosopher&) = delete;
    AbstractPhilosopher& operator=(const AbstractPhilosopher&) = delete;
    AbstractPhilosopher(AbstractPhilosopher&&) = delete;
    AbstractPhilosopher& operator=(AbstractPhilosopher&&) = delete;

    void start(const PhilosopherContext& context);

protected:
    virtual void eat(std::mutex& outputMutex, const TimeGenerator& eatingTimeGenerator) = 0;
    void         think(std::mutex& outputMutex, const TimeGenerator& thinkingTimeGenerator);

    [[nodiscard]] int getRandomTime(const TimeGenerator& timeGenerator);

    void displayGrabbedFork(std::mutex& outputMutex, const unsigned int forkId) const;
    void displayLetGoOfFork(std::mutex& outputMutex, const unsigned int forkId) const;
    void displayEating(std::mutex& outputMutex) const;
    void displayThinking(std::mutex& outputMutex) const;

protected:
    Fork& m_leftFork;
    Fork& m_rightFork;

    const unsigned int m_id;
};
