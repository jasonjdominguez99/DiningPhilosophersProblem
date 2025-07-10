#pragma once

#include "SimulationConfig.h"

#include <array>
#include <cstddef>
#include <format>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

class SimulationArgParser
{
public:
    SimulationArgParser() = delete;
    ~SimulationArgParser() = delete;

    SimulationArgParser(const SimulationArgParser&) = delete;
    SimulationArgParser& operator=(const SimulationArgParser&) = delete;
    SimulationArgParser(SimulationArgParser&&) = delete;
    SimulationArgParser& operator=(SimulationArgParser&&) = delete;

    static std::optional<SimulationConfig> parse(int argc, char* argv[]);

private:
    static size_t   parseNumPhilosophersArg(const std::vector<std::string_view>& args, const size_t i);
    static Strategy parseStrategyArg(const std::vector<std::string_view>& args, const size_t i);
    static int      parseTotalRunTimeArg(const std::vector<std::string_view>& args, const size_t i);

private:
    static constexpr size_t MIN_PHILOSOPHERS = 2;
    static constexpr size_t MAX_PHILOSOPHERS = 20;

    static constexpr int MIN_TOTAL_RUNTIME = 1'000; // milliseconds
    static constexpr int MAX_TOTAL_RUNTIME = 60'000; // milliseconds

    static constexpr int              NUM_ARGS = 3;
    static constexpr std::string_view NUM_PHILOSOPHERS_ARG = "--num-philosophers";
    static constexpr std::string_view STRATEGY_ARG = "--strategy";
    static constexpr std::string_view TOTAL_RUNTIME_ARG = "--total-run-time";

    static constexpr std::string_view HELP_ARG = "--help";

public:
    static inline const std::string HELP_MESSAGE = std::format(
        "Usage: DiningPhilosophersProblem [{}] [{}] [{}]",
        std::string(NUM_PHILOSOPHERS_ARG) + " <number>",
        std::string(STRATEGY_ARG) + " " + std::string(getStrategyOptions()),
        std::string(TOTAL_RUNTIME_ARG) + " <milliseconds>");
};
