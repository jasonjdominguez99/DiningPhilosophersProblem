#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <string_view>

enum class Strategy
{
    Asymmetric,
    Hierarchical,
    Naive
};

constexpr std::string_view getStrategyOptions()
{
    return "asymmetric|hierarchical|naive";
}

inline Strategy parseStrategy(const std::string& strategy)
{
    // Convert to lowercase for case-insensitive comparison
    std::string lowerCaseStrategy = strategy;
    std::transform(lowerCaseStrategy.begin(), lowerCaseStrategy.end(), lowerCaseStrategy.begin(), ::tolower);

    if (lowerCaseStrategy == "asymmetric")
    {
        return Strategy::Asymmetric;
    }
    else if (lowerCaseStrategy == "hierarchical")
    {
        return Strategy::Hierarchical;
    }
    else if (lowerCaseStrategy == "naive")
    {
        return Strategy::Naive;
    }
    else
    {
        throw std::invalid_argument("Invalid strategy: " + std::string(strategy));
    }
}
