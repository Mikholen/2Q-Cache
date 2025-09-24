#include <list>
#include <unordered_map>
#include <assert.h>

template <typename key_T, typename val_T>
class TwoQCache {

    using ListIt_key_val = typename std::list<std::pair<key_T, val_T>>::iterator;
    using ListIt_key = typename std::list<key_T>::iterator;

    size_t A1in_size_;
    size_t A1out_size_;
    size_t Am_size_;

    std::list<std::pair<key_T, val_T>> A1in_;
    std::unordered_map<key_T, ListIt_key_val> A1in_table_;

    std::list<key_T> A1out_;
    std::unordered_map<key_T, ListIt_key> A1out_table_;

    std::list<std::pair<key_T, val_T>> Am_;
    std::unordered_map<key_T, ListIt_key_val> Am_table_;

    template<typename list_T, typename map_T, typename iter_T>
    void delete_element (list_T &A, map_T &A_table, key_T key, iter_T iter) {
                
        A.erase (iter);
        A_table.erase (key);
    }

    template<typename list_T, typename map_T, typename el_T, typename iter_T>
    void add_element (list_T &A, map_T &A_table, key_T key, el_T element, iter_T iter) {

        A_table[key] = A.insert (iter, element);
    }

    template<typename list_T, typename map_T, typename el_T, typename iter_T>
    void insert_into_queue (list_T &A, map_T &A_table, size_t queue_size, 
                            key_T key_to_add, key_T key_to_delete, el_T element_to_add, 
                            iter_T iter_to_add, iter_T iter_to_delete) {

        if (A.size () < queue_size) {

            add_element (A, A_table, key_to_add, element_to_add, iter_to_add);
        }

        else {

            delete_element (A, A_table, key_to_delete, iter_to_delete);
            add_element (A, A_table, key_to_add, element_to_add, iter_to_add);
        }
    }

    template<typename el_T, typename iter_T>
    void insert_into_Ain (key_T key_to_add, key_T key_to_delete, el_T element_to_add, 
                          iter_T iter_to_add, iter_T iter_to_delete) {

        if (A1in_.size () < A1in_size_) {

            add_element (A1in_, A1in_table_, key_to_add, element_to_add, iter_to_add);
        }

        else {

            insert_into_queue (A1out_, A1out_table_, A1out_size_, key_to_delete, *A1out_.begin (),
                               key_to_delete, A1out_.end (), A1out_.begin ());

            delete_element (A1in_, A1in_table_, key_to_delete, iter_to_delete);
            add_element (A1in_, A1in_table_, key_to_add, element_to_add, iter_to_add);
        }
    }

public:

    explicit TwoQCache (size_t capacity) 
        : A1in_size_ (capacity / 4), 
          A1out_size_ (capacity / 4),
          Am_size_ (capacity - A1in_size_ - A1out_size_) {}

    void place_element (key_T key, val_T value) {

        assert (A1in_table_.count (key) + A1out_table_.count (key) + Am_table_.count (key) <= 1);

        if (A1in_table_.count (key) == 1) {
        
            delete_element (A1in_, A1in_table_, key, A1in_table_[key]);
            insert_into_queue (Am_, Am_table_, Am_size_, key, (*Am_.begin ()).first, 
                               std::make_pair (key, value), Am_.end (), Am_.begin ());
        }

        else if (A1out_table_.count (key) == 1) {

            delete_element (A1out_, A1out_table_, key, A1out_table_[key]);
            insert_into_queue (Am_, Am_table_, Am_size_, key, (*Am_.begin ()).first, 
                               std::make_pair (key, value), Am_.end (), Am_.begin ());           
        }

        else if (Am_table_.count (key) == 1) {

            Am_.erase (Am_table_[key]);
            Am_.insert (Am_.end (), std::make_pair (key, value));
        }

        else {

            insert_into_Ain (key, (*A1in_.begin ()).first, std::make_pair (key, value), A1in_.end (), A1in_.begin ());
        }
        
        std::cout << "A1in : ";

        for (auto iterator = A1in_.begin (); iterator != A1in_.end (); iterator++) {

            std::cout << (*iterator).first << "|" << (*iterator).second << " ";
        }

        std::cout << "\nA1out : ";
        
        for (auto iterator = A1out_.begin (); iterator != A1out_.end (); iterator++) {

            std::cout << *iterator << " ";
        }

        std::cout << "\nAm : ";
        
        for (auto iterator = Am_.begin (); iterator != Am_.end (); iterator++) {

            std::cout << (*iterator).first << "|" << (*iterator).second << " ";
        }

        std::cout << '\n';
    }
};