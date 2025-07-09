#pragma once

#include "Strategy.h"

#include <memory>
#include <vector>

class AbstractPhilosopher;
class Fork;

using Forks = std::vector<std::unique_ptr<Fork>>;
using Philosophers = std::vector<std::unique_ptr<AbstractPhilosopher>>;

class PhilosophersFactory
{
public:
    PhilosophersFactory() = delete;
    ~PhilosophersFactory() = delete;

    PhilosophersFactory(const PhilosophersFactory&) = delete;
    PhilosophersFactory& operator=(const PhilosophersFactory&) = delete;
    PhilosophersFactory(PhilosophersFactory&&) = delete;
    PhilosophersFactory& operator=(PhilosophersFactory&&) = delete;

    [[nodiscard]] static Philosophers create(const Forks& forks, const Strategy strategy) noexcept;

private:
    [[nodiscard]] static std::unique_ptr<AbstractPhilosopher> createLeftHandedPhilosopher(const unsigned int id, const Forks& forks) noexcept;
    [[nodiscard]] static std::unique_ptr<AbstractPhilosopher> createOrderedPhilosopher(const unsigned int id, const Forks& forks) noexcept;
    [[nodiscard]] static std::unique_ptr<AbstractPhilosopher> createRightHandedPhilosopher(const unsigned int id, const Forks& forks) noexcept;

    [[nodiscard]] static std::pair<size_t, size_t> getPhilosopherForkIndices(const unsigned int philosopherId, const Forks& forks) noexcept;
};
