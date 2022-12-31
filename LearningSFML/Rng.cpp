#include <random>
#include "Rng.h"

double randomnumber() {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static std::default_random_engine rng;

    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    return dist(rng);
}