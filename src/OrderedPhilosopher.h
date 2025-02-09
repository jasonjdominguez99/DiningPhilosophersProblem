#pragma once

#include "SelfishPhilosopher.h"

class OrderedPhilosopher : public SelfishPhilosopher
{
public:
    OrderedPhilosopher(Fork& fork1, Fork& fork2, const unsigned int id) noexcept :
        SelfishPhilosopher(getLowestFork(fork1, fork2), getHighestFork(fork1, fork2), id) {};

    ~OrderedPhilosopher() override = default;

private:
    [[nodiscard]] Fork& getLowestFork(Fork& fork1, Fork& fork2) const noexcept;
    [[nodiscard]] Fork& getHighestFork(Fork& fork1, Fork& fork2) const noexcept;
};
