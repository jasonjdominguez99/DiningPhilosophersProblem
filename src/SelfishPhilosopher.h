#pragma once

#include "AbstractPhilosopher.h"

class SelfishPhilosopher : public AbstractPhilosopher
{
public:
    SelfishPhilosopher(Fork& firstFork, Fork& secondFork, const unsigned int id) noexcept;
    virtual ~SelfishPhilosopher() = 0;

private:
    void eat(std::mutex& outputMutex, const TimeGenerator& eatingTimeGenerator) override;
};
