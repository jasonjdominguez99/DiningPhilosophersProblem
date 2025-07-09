#include "PhilosophersFactory.h"

#include "LeftHandedPhilosopher.h"
#include "OrderedPhilosopher.h"
#include "RightHandedPhilosopher.h"

#include <stddef.h>

Philosophers PhilosophersFactory::create(const Forks& forks, const Strategy strategy) noexcept
{
    const size_t numPhilosophers = forks.size();
    Philosophers philosophers;
    philosophers.reserve(numPhilosophers);
    switch (strategy)
    {
    case Strategy::Asymmetric:
        for (size_t i = 0; i < numPhilosophers; ++i)
        {
            if (i % 2 == 0)
            {
                philosophers.emplace_back(createLeftHandedPhilosopher(i + 1, forks));
            }
            else
            {
                philosophers.emplace_back(createRightHandedPhilosopher(i + 1, forks));
            }
        }
        break;

    case Strategy::Hierarchical:
        for (size_t i = 0; i < numPhilosophers; ++i)
        {
            philosophers.emplace_back(createOrderedPhilosopher(i + 1, forks));
        }
        break;

    case Strategy::Naive:
        for (size_t i = 0; i < numPhilosophers; ++i)
        {
            philosophers.emplace_back(createLeftHandedPhilosopher(i + 1, forks));
        }
        break;
    }

    return philosophers;
}

std::unique_ptr<AbstractPhilosopher> PhilosophersFactory::createLeftHandedPhilosopher(const unsigned int id, const Forks& forks) noexcept
{
    const auto [leftForkIndex, rightForkIndex] = getPhilosopherForkIndices(id, forks);
    return std::make_unique<LeftHandedPhilosopher>(*forks[leftForkIndex], *forks[rightForkIndex], id);
}

std::unique_ptr<AbstractPhilosopher> PhilosophersFactory::createOrderedPhilosopher(const unsigned int id, const Forks& forks) noexcept
{
    const auto [fork1Index, fork2Index] = getPhilosopherForkIndices(id, forks);
    return std::make_unique<OrderedPhilosopher>(*forks[fork1Index], *forks[fork2Index], id);
}

std::unique_ptr<AbstractPhilosopher> PhilosophersFactory::createRightHandedPhilosopher(const unsigned int id, const Forks& forks) noexcept
{
    const auto [leftForkIndex, rightForkIndex] = getPhilosopherForkIndices(id, forks);
    return std::make_unique<RightHandedPhilosopher>(*forks[leftForkIndex], *forks[rightForkIndex], id);
}

std::pair<size_t, size_t> PhilosophersFactory::getPhilosopherForkIndices(const unsigned int philosopherId, const Forks& forks) noexcept
{
    const size_t leftForkIndex = philosopherId % forks.size();
    const size_t rightForkIndex = (philosopherId - 1) % forks.size();
    return { leftForkIndex, rightForkIndex };
}
