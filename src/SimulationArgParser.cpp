#include "SimulationArgParser.h"

#include "SimulationConfig.h"
#include "Strategy.h"

#include <print>
#include <stdexcept>
#include <thread>

std::optional<SimulationConfig> SimulationArgParser::parse(int argc, char* argv[])
{
    if (argc > (NUM_ARGS * 2) + 1) // number of arguments, each with a value + 1 for the program name
    {
        throw std::invalid_argument("Too many arguments provided.");
    }

    auto config = SimulationConfig();

    // ignore the first argument (program name)
    std::vector<std::string_view> args(argv + 1, argv + argc);
    for (size_t i = 0; i < args.size(); ++i)
    {
        const auto& arg = args[i];
        if (arg == NUM_PHILOSOPHERS_ARG)
        {
            config.numPhilosophers = parseNumPhilosophersArg(args, ++i);
        }
        else if (arg == STRATEGY_ARG)
        {
            config.strategy = parseStrategyArg(args, ++i);
        }
        else if (arg == TOTAL_RUNTIME_ARG)
        {
            config.totalRunTime = parseTotalRunTimeArg(args, ++i);
        }
        else if (arg == HELP_ARG)
        {
            std::println("{}", HELP_MESSAGE);
            return std::nullopt;
        }
        else
        {
            throw std::invalid_argument("Unknown argument: " + std::string(arg));
        }
    }

    return config;
}

size_t SimulationArgParser::parseNumPhilosophersArg(const std::vector<std::string_view>& args, const size_t i)
{
    size_t numPhilosophers = 0;

    if (i >= args.size() || args[i].empty())
    {
        throw std::invalid_argument("Missing value for " + std::string(NUM_PHILOSOPHERS_ARG) + " argument.");
    }
    try
    {
        numPhilosophers = static_cast<size_t>(std::stoull(std::string(args[i])));
        const size_t maxNumPhilosophers = std::min(static_cast<size_t>(std::thread::hardware_concurrency()), MAX_PHILOSOPHERS);
        if (numPhilosophers > maxNumPhilosophers)
        {
            throw std::invalid_argument("Number of philosophers exceeds maximum allowed value.");
        }
        if (numPhilosophers < MIN_PHILOSOPHERS)
        {
            throw std::invalid_argument(std::format("Number of philosophers must be at least {}.", MIN_PHILOSOPHERS));
        }
    }
    catch (const std::invalid_argument& e)
    {
        throw std::invalid_argument("Invalid value for " + std::string(NUM_PHILOSOPHERS_ARG) + ": " + std::string(args[i]) + "\n" + e.what());
    }

    return numPhilosophers;
}

Strategy SimulationArgParser::parseStrategyArg(const std::vector<std::string_view>& args, const size_t i)
{
    Strategy strategy = Strategy::Hierarchical;

    if (i >= args.size() || args[i].empty())
    {
        throw std::invalid_argument("Missing value for " + std::string(STRATEGY_ARG) + " argument.");
    }
    try
    {
        strategy = parseStrategy(std::string(args[i]));
    }
    catch (const std::invalid_argument& e)
    {
        throw std::invalid_argument("Invalid value for " + std::string(STRATEGY_ARG) + ": " + std::string(args[i]) + "\n" + e.what());
    }

    return strategy;
}

int SimulationArgParser::parseTotalRunTimeArg(const std::vector<std::string_view>& args, const size_t i)
{
    int totalRunTime = 0;

    if (i >= args.size() || args[i].empty())
    {
        throw std::invalid_argument("Missing value for " + std::string(TOTAL_RUNTIME_ARG) + " argument.");
    }
    try
    {
        totalRunTime = std::stoi(std::string(args[i]));
        if (totalRunTime < MIN_TOTAL_RUNTIME)
        {
            throw std::invalid_argument(std::format("The minimum total runtime is {} ms.", MIN_TOTAL_RUNTIME));
        }
        if (totalRunTime > MAX_TOTAL_RUNTIME)
        {
            throw std::invalid_argument(std::format("The maximum total runtime is {} ms.", MAX_TOTAL_RUNTIME));
        }
    }
    catch (const std::invalid_argument& e)
    {
        throw std::invalid_argument("Invalid value for " + std::string(TOTAL_RUNTIME_ARG) + ": " + std::string(args[i]) + "\n" + e.what());
    }

    return totalRunTime;
}
