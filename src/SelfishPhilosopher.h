#pragma once

#include "AbstractPhilosopher.h"

class SelfishPhilosopher : public AbstractPhilosopher
{
public:
    SelfishPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) noexcept;
    ~SelfishPhilosopher() override = default;

private:
    void eat(std::mutex& outputMutex, const TimeGenerator& eatingTimeGenerator) override;
};
