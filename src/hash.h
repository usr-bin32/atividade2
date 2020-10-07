#include <cmath>
#include <functional>
#include <list>
#include <vector>

template <typename T>
struct HashNode {
    HashNode(unsigned int key, T const &data) {
        this->key = key;
        this->data = data;
    }

    unsigned int key;
    T data;
};

template <typename T>
class HashTable {
  public:
    HashTable(
        unsigned int m,
        std::function<unsigned int(unsigned int, unsigned int)> function
    ) {
        // create
        this->table.resize(m);
        this->hash_function = function;
    }

    T *insert(unsigned int key, T const &data) {
        unsigned int index = this->hash_function(key, table.size());

        T *data_ptr = lookup_index(key, index);
        if (data_ptr != nullptr) {
            *data_ptr = data;
        } else {
            this->table[index].emplace_front(key, data);
            data_ptr = &this->table[index].front().data;
        }

        return data_ptr;
    }

    T *lookup(unsigned int key) {
        unsigned int index = this->hash_function(key, table.size());
        return lookup_index(key, index);
    }

    unsigned int collisions() {
        unsigned int result = 0;
        for (auto const &list : this->table) {
            if (list.empty()) {
                continue;
            }
            result += list.size() - 1;
        }
        return result;
    }

    // destroy automático

  private:
    T *lookup_index(unsigned int key, unsigned int index) {
        T *data_ptr = nullptr;
        for (auto &node : this->table[index]) {
            if (node.key == key) {
                data_ptr = &node.data;
                break;
            }
        }

        return data_ptr;
    }

    std::vector<std::list<HashNode<T>>> table;
    std::function<unsigned int(unsigned int, unsigned int)> hash_function;
};

unsigned int division_hash(unsigned int key, unsigned int m) {
    return key % m;
}

unsigned int multi_hash(unsigned int key, unsigned int m) {
    double A = (sqrt(5) - 1) / 2;
    return floor(m * (fmod(key * A, 1)));
}

unsigned int minha_hash(unsigned int key, unsigned int m) {
    return (key % 1031) % m;
}
