#include "OrderedPhilosopher.h"

#include "Fork.h"

Fork& OrderedPhilosopher::getLowestFork(Fork& fork1, Fork& fork2) const noexcept
{
    return fork1.getId() <= fork2.getId() ? fork1 : fork2;
}

Fork& OrderedPhilosopher::getHighestFork(Fork& fork1, Fork& fork2) const noexcept
{
    return fork1.getId() > fork2.getId() ? fork1 : fork2;
}
