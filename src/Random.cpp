#include "Random.hpp"

double Random::sample(const Distribution& dist) {
    return dist.sampler()(g);
}

std::vector<double> Random::sample(const Distribution& dist, int n) {
    std::vector<double> out(n);
    for (int i = 0; i < n; ++i) {
        out[i] = sample(dist);
    }
    return out;
}

void Random::init_gen() {
    g = gsl_rng_alloc(gsl_rng_mt19937);
}

// By default, seed with the current time
Random::Random() {
    init_gen();
    gsl_rng_set(g, time(nullptr));
}

Random::Random(unsigned long s) {
    init_gen();
    gsl_rng_set(g, s);
}

Random::~Random() {
    gsl_rng_free(g);
}

// Returns random number in [0,1)
double Random::uniform_real() {
    return gsl_rng_uniform(g);
}

long Random::uniform_int(unsigned long n) {
    return gsl_rng_uniform_int(g, n);
}

