#pragma once
#include <list>
#include <unordered_map>
#include <cassert>
#include <utility>

template <typename key_T, typename val_T>
class TwoQCache {

    using List_key_val   = typename std::list<std::pair<key_T, val_T>>;
    using ListIt_key_val = typename List_key_val::iterator;
    using ListIt_key     = typename std::list<key_T>::iterator;

    struct queue_with_value {

        std::size_t queue_size = 0;
        List_key_val A_list;
        std::unordered_map<key_T, ListIt_key_val> A_table;
    } queue_with_value;

    struct queue_no_value {

        std::size_t queue_size = 0;
        std::list<key_T> A_list;
        std::unordered_map<key_T, ListIt_key> A_table;
    } queue_no_value;

    queue_with_value A1in;
    queue_no_value A1out;
    queue_with_value Am;

    template<typename queue_T, typename el_T, typename iter_T>
    void insert_into_queue (queue_T &Queue, const key_T &key_to_add, const key_T &key_to_delete,
                            const el_T element_to_add, const iter_T iter_to_add, const iter_T iter_to_delete) ;

    template<typename el_T, typename iter_T>
    void insert_into_Ain (const key_T &key_to_add, const key_T &key_to_delete, const el_T element_to_add, 
                          const iter_T iter_to_add, const iter_T iter_to_delete);

    void print_all_queues ();

public:

    explicit TwoQCache (std::size_t size) 

        : A1in { .queue_size = size / 4}, A1out { .queue_size = size / 4}, 
          Am { .queue_size = size - (size / 4) * 2}, n_cache_hit(0) {}

    explicit TwoQCache (std::size_t in_size, std::size_t out_size, std::size_t main_size) 

        : A1in { .queue_size = in_size}, A1out { .queue_size = out_size}, 
          Am { .queue_size = main_size}, n_cache_hit(0) {}

    std::size_t n_cache_hit;

    void place_element (const key_T &key, const val_T &value);
    val_T get_element (const key_T &key);

    bool contains_element (const key_T &key) {

        return ((A1in.A_table.count (key) == 1) || (Am.A_table.count (key) == 1));
    }
};

template<typename key_T, typename val_T>
void TwoQCache<key_T, val_T>::place_element (const key_T &key, const val_T &value) {

    assert (A1in.A_table.count (key) + A1out.A_table.count (key) + Am.A_table.count (key) <= 1);

    if (A1in.A_table.count (key) == 1) {

        n_cache_hit++;    
        A1in.A_list.erase (A1in.A_table[key]);
        A1in.A_table.erase (key);    
        insert_into_queue (Am, key, (*(Am.A_list).begin ()).first, std::make_pair (key, value), Am.A_list.end (), Am.A_list.begin ());
    }

    else if (A1out.A_table.count (key) == 1) {

        A1out.A_list.erase (A1out.A_table[key]);
        A1out.A_table.erase (key);
        insert_into_queue (Am, key, (*(Am.A_list).begin ()).first, std::make_pair (key, value), Am.A_list.end (), Am.A_list.begin ());           
    }

    else if (Am.A_table.count (key) == 1) {

        n_cache_hit++;
        Am.A_list.erase (Am.A_table[key]);
        Am.A_list.insert (Am.A_list.end (), std::make_pair (key, value));
    }

    else {

        insert_into_Ain (key, (*(A1in.A_list).begin ()).first, std::make_pair (key, value), A1in.A_list.end (), A1in.A_list.begin ());
    }

    // print_all_queues ();
}

template<typename key_T, typename val_T>
val_T TwoQCache<key_T, val_T>::get_element (const key_T &key) {

    if (A1in.A_table.count (key)) {

        return (*(A1in.A_table[key])).second;
    }

    else if (Am.A_table.count (key)) {

        return (*(Am.A_table[key])).second;
    }

    return 0;
}

template <typename key_T, typename val_T>
void TwoQCache<key_T, val_T>::print_all_queues () {

    std::cout << "A1in : ";

    for (auto &[key, val] : A1in.A_list) {

        std::cout << key << "|" << val << " ";
    }

    std::cout << "\nA1out : ";
    
    for (auto elem : A1out.A_list) {

        std::cout << elem << " ";
    }

    std::cout << "\nAm : ";
    
    for (auto &[key, val] : Am.A_list) {

        std::cout << key << "|" << val << " ";
    }

    std::cout << '\n';
}

template<typename key_T, typename val_T>
template<typename el_T, typename iter_T>
void TwoQCache<key_T, val_T>::insert_into_Ain (const key_T &key_to_add, const key_T &key_to_delete, const el_T element_to_add, 
                                               const iter_T iter_to_add, const iter_T iter_to_delete) {

    if (A1in.A_list.size () < A1in.queue_size) {

        A1in.A_table[key_to_add] = Queue.A_list.insert (iter_to_add, element_to_add);
    }

    else {

        insert_into_queue (A1out, key_to_delete, *(A1out.A_list).begin (),
                            key_to_delete, A1out.A_list.end (), A1out.A_list.begin ());

        A1in.A_list.erase (iter_to_delete);
        A1in.A_table.erase (key_to_delete);
        A1in.A_table[key_to_add] = Queue.A_list.insert (iter_to_add, element_to_add);
    }
}

template<typename key_T, typename val_T>
template<typename queue_T, typename el_T, typename iter_T>
void TwoQCache<key_T, val_T>::insert_into_queue (queue_T &Queue, const key_T &key_to_add, const key_T &key_to_delete,
                        const el_T element_to_add, const iter_T iter_to_add, const iter_T iter_to_delete) {

    if (Queue.A_list.size () < Queue.queue_size) {

        Queue.A_table[key_to_add] = Queue.A_list.insert (iter_to_add, element_to_add);
    }

    else {

        Queue.A_list.erase (iter_to_delete);
        Queue.A_table.erase (key_to_delete);
        Queue.A_table[key_to_add] = Queue.A_list.insert (iter_to_add, element_to_add);
    }
}