#pragma once

#include "SelfishPhilosopher.h"

class RightHandedPhilosopher : public SelfishPhilosopher
{
public:
    RightHandedPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) noexcept :
        SelfishPhilosopher(rightFork, leftFork, id) {};

    ~RightHandedPhilosopher() override = default;
};
