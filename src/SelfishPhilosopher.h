#pragma once

#include "AbstractPhilosopher.h"

class SelfishPhilosopher : public AbstractPhilosopher
{
public:
    SelfishPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id);
    ~SelfishPhilosopher() override = default;

private:
    void eat(std::mutex&                      outputMutex,
             std::mutex&                      randomMutex,
             std::mt19937&                    randomGenerator,
             std::uniform_int_distribution<>& eatingTimeDist) override;
};
