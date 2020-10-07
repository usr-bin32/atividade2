#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "hash.h"

void randomize_vector(std::vector<unsigned int> &vector, unsigned int length);
void test(
    std::function<unsigned int(unsigned int, unsigned int)> function,
    std::vector<unsigned int> const &keys
);

int main() {
    std::vector<unsigned int> keys;
    randomize_vector(keys, 1000);

    std::cout << "DIVISION_HASH\n";
    test(division_hash, keys);

    std::cout << "MULTIPLICATION_HASH\n";
    test(multi_hash, keys);

    std::cout << "MINHA_HASH\n";
    test(minha_hash, keys);

    return 0;
}

void test(
    std::function<unsigned int(unsigned int, unsigned int)> function,
    std::vector<unsigned int> const &keys
) {
    unsigned int values_m[] = { 1021, 1024, 1000, 999 };

    for (auto m : values_m) {
        HashTable<int> table(m, function);

        for (auto k : keys) {
            int data = k * 2;
            table.insert(k, data);
        }

        std::cout
            << "m = "
            << m
            << ", collisions = "
            << table.collisions()
            << std::endl;
    }
}

void randomize_vector(std::vector<unsigned int> &vector, unsigned int length) {
    // preenche o vetor com números aleatórios sem repetição

    // preenche o container com 0, 1, 2, ..., 10000
    vector.resize(10000);
    std::iota(std::begin(vector), std::end(vector), 0);

    // randomiza o container e elimina os elementos após length.
    std::random_shuffle(std::begin(vector), std::end(vector));
    vector.resize(length);
}
