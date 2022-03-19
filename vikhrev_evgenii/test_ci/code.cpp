#include <iostream>
#include <array>
#include <algorithm>
#include <stack>
#include <list>
#include <vector>
#include <queue>

g
#include <type_traits>
#include <tuple>


template<typename T, size_t N>
class my_array {
public:
    T& operator[](size_t index) { return data[index]; }
private:
    T data[N];
};


template<typename A, typename V, size_t N>
class LRUCache {
public:
    V get(A args) {
        auto found = std::find(data.begin(), data.end(), CacheNode{args, 0});
        if (found == data.end()) {
            throw std::out_of_range("Cache miss");
        } else {
            if (found != data.begin()) {
                data.push_front(*found);
                data.erase(found);
            }
            return found->value;
        }
    }

    void put(A args, V value) {
        data.push_front(CacheNode{args, value});
        if (data.size() > N) {
            data.pop_back();
        }
    }
private:
    struct CacheNode {
        A args;
        V value;
        bool operator==(const CacheNode& other) { return other.args == args; }
    };
    std::list<CacheNode> data;
};


struct Sqr {
    int operator()(int value) {
        return value * value;
    }
};


template <typename F, size_t N, typename... Args>
struct with_cache {
    with_cache(): f(), cache() {}

    F f;
    LRUCache<std::tuple<Args...>, std::invoke_result_t<F, Args...>, N> cache;

    std::invoke_result_t<F, Args...> operator()(Args... args) {
        try {
            auto temp = cache.get(std::make_tuple(args...));
            std::cout << "Hit!\n";
            return temp;
        } catch(std::out_of_range& e) {
            auto temp = f(args...);
            cache.put(std::make_tuple(args...), temp);
            std::cout << "Miss!\n";
            return temp;
        }
    }
};


int main() {
    auto cached_sqr = with_cache<Sqr, 3, int>();
    for (int i = 0; i < 10; ++i) {
        int temp;
        std::cin >> temp;
        cached_sqr(temp);
    }
}
