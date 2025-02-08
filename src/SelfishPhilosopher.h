#pragma once

#include "AbstractPhilosopher.h"

class SelfishPhilosopher : public AbstractPhilosopher
{
public:
    SelfishPhilosopher(std::mutex& outputMutex, Fork& leftFork, Fork& rightFork, const unsigned int id);
    ~SelfishPhilosopher() override = default;

private:
    void eat() override;
};
