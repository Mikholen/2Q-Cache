#pragma once
#include <list>
#include <unordered_map>
#include <assert.h>

template <typename key_T, typename val_T>
class TwoQCache {

    using ListIt_key_val = typename std::list<std::pair<key_T, val_T>>::iterator;
    using ListIt_key     = typename std::list<key_T>::iterator;

    typedef struct queue_with_value {

        size_t queue_size_ = 0;
        std::list<std::pair<key_T, val_T>> A_list_;
        std::unordered_map<key_T, ListIt_key_val> A_table_;
    } queue_with_value;

    typedef struct queue_no_value {

        size_t queue_size_ = 0;
        std::list<key_T> A_list_;
        std::unordered_map<key_T, ListIt_key> A_table_;
    } queue_no_value;

    queue_with_value A1in_;
    queue_no_value A1out_;
    queue_with_value Am_;

    template<typename queue_T, typename iter_T>
    void delete_element (queue_T &Queue, const key_T &key, const iter_T iter) {
                
        Queue.A_list_.erase (iter);
        Queue.A_table_.erase (key);
    }

    template<typename queue_T, typename el_T, typename iter_T>
    void add_element (queue_T &Queue, const key_T &key, const el_T element, const iter_T iter) {

        Queue.A_table_[key] = Queue.A_list_.insert (iter, element);
    }

    template<typename queue_T, typename el_T, typename iter_T>
    void insert_into_queue (queue_T &Queue, const key_T &key_to_add, const key_T &key_to_delete,
                            const el_T element_to_add, const iter_T iter_to_add, const iter_T iter_to_delete) ;

    template<typename el_T, typename iter_T>
    void insert_into_Ain (const key_T &key_to_add, const key_T &key_to_delete, const el_T element_to_add, 
                          const iter_T iter_to_add, const iter_T iter_to_delete);

    void print_all_queues ();

public:

    explicit TwoQCache (size_t size) 

        : A1in_ { .queue_size_ = size / 4}, A1out_ { .queue_size_ = size / 4}, 
          Am_ { .queue_size_ = size - (size / 4) * 2}, n_cache_hit(0) {}

    explicit TwoQCache (size_t in_size, size_t out_size, size_t main_size) 

        : A1in_ { .queue_size_ = in_size}, A1out_ { .queue_size_ = out_size}, 
          Am_ { .queue_size_ = main_size}, n_cache_hit(0) {}

    std::size_t n_cache_hit;

    void place_element (const key_T key, const val_T value);
    val_T get_element (const key_T key);

    bool contains_element (const key_T key) {

        if ((A1in_.A_table_.count (key) == 1) || (Am_.A_table_.count (key) == 1))
            return true;
        
        else
            return false;
    }
};

template<typename key_T, typename val_T>
void TwoQCache<key_T, val_T>::place_element (const key_T key, const val_T value) {

    assert (A1in_.A_table_.count (key) + A1out_.A_table_.count (key) + Am_.A_table_.count (key) <= 1);

    if (A1in_.A_table_.count (key) == 1) {

        n_cache_hit++;        
        delete_element (A1in_, key, A1in_.A_table_[key]);
        insert_into_queue (Am_, key, (*(Am_.A_list_).begin ()).first, std::make_pair (key, value), Am_.A_list_.end (), Am_.A_list_.begin ());
    }

    else if (A1out_.A_table_.count (key) == 1) {

        delete_element (A1out_, key, A1out_.A_table_[key]);
        insert_into_queue (Am_, key, (*(Am_.A_list_).begin ()).first, std::make_pair (key, value), Am_.A_list_.end (), Am_.A_list_.begin ());           
    }

    else if (Am_.A_table_.count (key) == 1) {

        n_cache_hit++;
        Am_.A_list_.erase (Am_.A_table_[key]);
        Am_.A_list_.insert (Am_.A_list_.end (), std::make_pair (key, value));
    }

    else {

        insert_into_Ain (key, (*(A1in_.A_list_).begin ()).first, std::make_pair (key, value), A1in_.A_list_.end (), A1in_.A_list_.begin ());
    }

    // print_all_queues ();
}

template<typename key_T, typename val_T>
val_T TwoQCache<key_T, val_T>::get_element (const key_T key) {

    if (A1in_.A_table_.count (key)) {

        return (*(A1in_.A_table_[key])).second;
    }

    else if (Am_.A_table_.count (key)) {

        return (*(Am_.A_table_[key])).second;
    }

    return 0;
}

template <typename key_T, typename val_T>
void TwoQCache<key_T, val_T>::print_all_queues () {

    std::cout << "A1in : ";

    for (auto iterator = TwoQCache::A1in_.A_list_.begin (); iterator != TwoQCache::A1in_.A_list_.end (); iterator++) {

        std::cout << (*iterator).first << "|" << (*iterator).second << " ";
    }

    std::cout << "\nA1out : ";
    
    for (auto iterator = TwoQCache::A1out_.A_list_.begin (); iterator != TwoQCache::A1out_.A_list_.end (); iterator++) {

        std::cout << *iterator << " ";
    }

    std::cout << "\nAm : ";
    
    for (auto iterator = TwoQCache::Am_.A_list_.begin (); iterator != TwoQCache::Am_.A_list_.end (); iterator++) {

        std::cout << (*iterator).first << "|" << (*iterator).second << " ";
    }

    std::cout << '\n';
}

template<typename key_T, typename val_T>
template<typename el_T, typename iter_T>
void TwoQCache<key_T, val_T>::insert_into_Ain (const key_T &key_to_add, const key_T &key_to_delete, const el_T element_to_add, 
                                               const iter_T iter_to_add, const iter_T iter_to_delete) {

    if (A1in_.A_list_.size () < A1in_.queue_size_) {

        add_element (A1in_, key_to_add, element_to_add, iter_to_add);
    }

    else {

        insert_into_queue (A1out_, key_to_delete, *(A1out_.A_list_).begin (),
                            key_to_delete, A1out_.A_list_.end (), A1out_.A_list_.begin ());

        delete_element (A1in_, key_to_delete, iter_to_delete);
        add_element    (A1in_, key_to_add,    element_to_add, iter_to_add);
    }
}

template<typename key_T, typename val_T>
template<typename queue_T, typename el_T, typename iter_T>
void TwoQCache<key_T, val_T>::insert_into_queue (queue_T &Queue, const key_T &key_to_add, const key_T &key_to_delete,
                        const el_T element_to_add, const iter_T iter_to_add, const iter_T iter_to_delete) {

    if (Queue.A_list_.size () < Queue.queue_size_) {

        add_element (Queue, key_to_add, element_to_add, iter_to_add);
    }

    else {

        delete_element (Queue, key_to_delete, iter_to_delete);
        add_element    (Queue, key_to_add,    element_to_add, iter_to_add);
    }
}