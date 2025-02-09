#pragma once

#include "AbstractPhilosopher.h"

class SelfishPhilosopher : public AbstractPhilosopher
{
public:
    SelfishPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) noexcept;
    ~SelfishPhilosopher() override = default;

    SelfishPhilosopher(const AbstractPhilosopher&) = delete;
    SelfishPhilosopher& operator=(const AbstractPhilosopher&) = delete;
    SelfishPhilosopher(AbstractPhilosopher&&) = delete;
    SelfishPhilosopher& operator=(AbstractPhilosopher&&) = delete;

private:
    void eat(std::mutex& outputMutex, const TimeGenerator& eatingTimeGenerator) override;
};
