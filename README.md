# 2Q-Cache

In this repository you can find the 2q cache implementation. In this implementation it is assumed that input data consist of key and value, it is also assumed that if the same keys are received values that correspond to them would also be the same. If the last assumption is not fulfilled, the last retrieved value will be stored in the cache.

The 2q cache algorithm is based on three queues : A_in, A_out, A_main. When pair of key and value is obtained it is checked if it is already in any queue. If it is not in cache (cache miss) key and value are placed in A_in queue, if it is in A_in (cache hit) or A_out (note, that in A_out only keys are stored, therefore, if the element is found here, then it is cache miss) it is deleted and replaced to A_main. If key is found in A_main (cache hit) it is replaced in the beginning of it. A_in and A_out queues work by the FIFO (e. g. first in first out) rule, while A_main uses LRU (e. g. least recently used) algorithm. 

## Run the program
### Run
1) Clone the repository
```shell
git clone ...
```
2) Go to repository folder
```bash
cd 2Q-Cache
```
3) Create a build folder and go to it
```bash
mkdir build && cd build
```
4) Generate a file for assembly using cmake
```bash
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
```
5) Assemble the project
```bash
cmake --build .
```
6) Run the executable file of `2q cache`
```bash
./two_q_cache
```
7) Run `tests`
```bash
./cache_tests
```
### Project structure
```tree
2Q-Cache/
├── CMakeLists.txt
├── include
│   ├── cache.hpp 
├── main.cpp
└── tests
    ├── test_cache.cpp
```