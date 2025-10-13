#include <iostream>
#include "include/cache.hpp"

int main () {

    int n_elements = 0;
    std::cin >> n_elements;

    int in_size = 0, out_size = 0, main_size = 0;
    std::cin >> in_size >> out_size >> main_size;
    TwoQCache<int, int> cache (in_size, out_size, main_size);

    int page_id;
    int page;

    for (int i = 0; i < n_elements; i++) {

        std::cin >> page_id >> page;
        cache.place_element (page_id, page);
    }
    
    std::size_t n_hit = 0;
    std::cin >> n_hit;
    std::cout << "N cache hit : " << cache.n_cache_hit << "/" << n_hit << std::endl;
    return 0;
}