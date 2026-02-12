#pragma once

#include <random>
#include <chrono>
#include <system_error>
#include <cstdint>

auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 rng(seed);

uint32_t
GetRandomU32(uint32_t min, uint32_t max)
{
    std::uniform_int_distribution<uint32_t> dist(min, max);
    return dist(rng);
}

int32_t
GetRandom32(int32_t min, int32_t max)
{
    std::uniform_int_distribution<int32_t> dist(min, max);
    return dist(rng);
}
