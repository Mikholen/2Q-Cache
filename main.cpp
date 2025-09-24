#include <iostream>
#include "include/cache.hpp"

int main () {

    int n_elements = 0;
    std::cin >> n_elements;

    int cache_size = 0;
    std::cin >> cache_size;
    TwoQCache<int, int> cache (cache_size);

    int page_id;
    int page;

    for (int i = 0; i < n_elements; i++) {

        std::cin >> page_id >> page;
        cache.place_element (page_id, page);
    }
    
    return 0;
}