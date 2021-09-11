#ifndef _RANDOM
#define _RANDOM

#include <vector>
#include <functional>

#include <ctime>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

// A Sampler takes a random number generator and produces a real number
typedef std::function<double(const gsl_rng*)> Sampler;

// A statistical distribution that can be sampled
class Distribution {
public:
    virtual Sampler sampler() const = 0;
};

// Pseudorandom number generator
class Random {
public:
    Random();
    Random(unsigned long s); // seed
    ~Random();

    // Draw a random uniform real number or integer
    double uniform_real(); // [0,1)
    long uniform_int(unsigned long n); // [0,n)

    // Samples one or many random variates from distribution
    double sample(const Distribution& dist);
    std::vector<double> sample(const Distribution& dist, int n);

    // Selects or reorders random elements of type T
    template <class T> void shuffle(std::vector<T>& lst);
    template <class T> std::vector<T> choose(const std::vector<T>& lst, int r);
private:
    void init_gen();
    gsl_rng* g;
};

template <class T>
std::vector<T> Random::choose(const std::vector<T>& lst, int r) {
    std::vector<T> out(r);
    gsl_ran_choose(g, &out[0], r, &lst[0], lst.size(), sizeof(T));
    return out;
}

template <class T>
void Random::shuffle(std::vector<T>& lst) {
    gsl_ran_shuffle(g, &lst[0], lst.size(), sizeof(T));
}

#endif
