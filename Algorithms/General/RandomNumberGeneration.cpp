#include <random>
#include <iostream>

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);

    for (int i=0; i<16; ++i)
        std::cout << dist(mt) << "\n";
}

//We use random_device once to seed the random number generator named mt. random_device() is slower than mt19937,
//but it does not need to be seeded because it requests random data from your operating system
//(which will source from various locations, like RdRand for example).

//uniform_real_distribution returns a number in the range [a, b), to get number in the range [a, b] :

std::uniform_real_distribution<double> dist(1, std::nextafter(10, DBL_MAX));
