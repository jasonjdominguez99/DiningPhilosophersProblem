#pragma once

#include "SelfishPhilosopher.h"

class LeftHandedPhilosopher : public SelfishPhilosopher
{
public:
    LeftHandedPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) noexcept :
        SelfishPhilosopher(leftFork, rightFork, id) {};

    ~LeftHandedPhilosopher() override = default;
};
