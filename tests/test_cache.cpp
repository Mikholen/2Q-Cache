#include <gtest/gtest.h>
#include "cache.hpp"

TEST(TwoQCacheTest, Test1) {
    TwoQCache<int, int> cache(3, 3, 5);

    cache.place_element(1, 11);
    cache.place_element(2, 22);
    cache.place_element(3, 33);
    cache.place_element(4, 44);
    cache.place_element(5, 55);
    cache.place_element(1, 11);
    cache.place_element(2, 22);
    cache.place_element(6, 66);
    cache.place_element(3, 33);
    cache.place_element(7, 77);

    cache.place_element(2, 22);
    cache.place_element(8, 88);
    cache.place_element(1, 11);
    cache.place_element(9, 99);
    cache.place_element(3, 33);
    cache.place_element(4, 44);
    cache.place_element(10, 1010);
    cache.place_element(2, 22);
    cache.place_element(5, 55);
    cache.place_element(1, 11);

    EXPECT_EQ(cache.n_cache_hit, 5);
}

TEST(TwoQCacheTest, Test2) {
    TwoQCache<int, int> cache(20);

    cache.place_element(101, 345925);
    cache.place_element(305, 497311);
    cache.place_element(509, 976642);
    cache.place_element(999, 444444);
    cache.place_element(305, 497311);
    cache.place_element(888, 2002229);
    cache.place_element(101, 345925);
    cache.place_element(222, 66);
    cache.place_element(305, 497311);
    cache.place_element(509, 976642);

    cache.place_element(707, 9991294);
    cache.place_element(888, 2002229);
    cache.place_element(111, 6543211);
    cache.place_element(305, 497311);
    cache.place_element(222, 66);
    cache.place_element(999, 444444);
    cache.place_element(305, 497311);
    cache.place_element(101, 345925);
    cache.place_element(333, 55);
    cache.place_element(509, 976642);

    EXPECT_EQ(cache.n_cache_hit, 11);
}

TEST(TwoQCacheTest, Test3) {
    TwoQCache<int, int> cache(2, 2, 2);

    cache.place_element(10, 120); 
    cache.place_element(20, 210);
    cache.place_element(30, 310); 
    cache.place_element(40, 400);
    cache.place_element(50, 500);
    cache.place_element(10, 120);
    cache.place_element(60, 600);
    cache.place_element(20, 210);
    cache.place_element(70, 700);
    cache.place_element(30, 310);
    cache.place_element(10, 120);
    cache.place_element(40, 400);
    cache.place_element(80, 890);
    cache.place_element(50, 500);
    cache.place_element(20, 210);

    EXPECT_EQ(cache.n_cache_hit, 0);
}

TEST(TwoQCacheTest, Test4) {
    TwoQCache<int, int> cache(32);

    cache.place_element(111, 1110);
    cache.place_element(222, 2220);
    cache.place_element(333, 3330);
    cache.place_element(444, 4440);
    cache.place_element(555, 5550);
    cache.place_element(666, 6660);
    cache.place_element(111, 1110);
    cache.place_element(777, 7770);
    cache.place_element(888, 8880);
    cache.place_element(222, 2220);
    cache.place_element(333, 3330);
    cache.place_element(999, 9990);
    cache.place_element(444, 4440);
    cache.place_element(555, 5550);
    cache.place_element(1000, 10000);
    cache.place_element(222, 2220);
    cache.place_element(888, 8880);
    cache.place_element(666, 6660);
    cache.place_element(333, 3330);
    cache.place_element(777, 7770);
    cache.place_element(555, 5550);
    cache.place_element(111, 1110);
    cache.place_element(444, 4440);
    cache.place_element(888, 8880);
    cache.place_element(1000, 10000);

    EXPECT_EQ(cache.n_cache_hit, 15);
}

TEST(TwoQCacheTest, Test5) {
    TwoQCache<int, int> cache(4, 4, 4);

    cache.place_element(15, 150);
    cache.place_element(25, 250);
    cache.place_element(35, 350);
    cache.place_element(45, 450);
    cache.place_element(55, 550);
    cache.place_element(65, 650);
    cache.place_element(75, 750);
    cache.place_element(15, 150);
    cache.place_element(25, 250);
    cache.place_element(35, 350);
    cache.place_element(85, 850);
    cache.place_element(95, 950);
    cache.place_element(25, 250);
    cache.place_element(15, 150);
    cache.place_element(105, 1050);
    cache.place_element(115, 1150);
    cache.place_element(75, 750);
    cache.place_element(125, 1250);
    cache.place_element(85, 850);
    cache.place_element(25, 250);

    EXPECT_EQ(cache.n_cache_hit, 3);
}

TEST(TwoQCacheTest, Test6) {
    TwoQCache<int, int> cache(2, 2, 10);

    cache.place_element(15, 150);
    cache.place_element(25, 250);
    cache.place_element(35, 350);
    cache.place_element(45, 450);
    cache.place_element(55, 550);
    cache.place_element(65, 650);
    cache.place_element(75, 750);
    cache.place_element(15, 150);
    cache.place_element(25, 250);
    cache.place_element(35, 350);
    cache.place_element(85, 850);
    cache.place_element(95, 950);
    cache.place_element(25, 250);
    cache.place_element(15, 150);
    cache.place_element(105, 1050);
    cache.place_element(115, 1150);
    cache.place_element(75, 750);
    cache.place_element(125, 1250);
    cache.place_element(85, 850);
    cache.place_element(25, 250);

    EXPECT_EQ(cache.n_cache_hit, 1);
}

TEST(TwoQCacheTest, Test7) {
    TwoQCache<int, int> cache(10, 5, 5);

    cache.place_element(111, 1110);
    cache.place_element(222, 2220);
    cache.place_element(333, 3330); 
    cache.place_element(444, 4440);
    cache.place_element(555, 5550);
    cache.place_element(666, 6660);
    cache.place_element(111, 1110);
    cache.place_element(777, 7770);
    cache.place_element(888, 8880);
    cache.place_element(222, 2220);
    cache.place_element(333, 3330);
    cache.place_element(999, 9990);
    cache.place_element(444, 4440);
    cache.place_element(555, 5550);
    cache.place_element(1000, 10000);
    cache.place_element(222, 2220);
    cache.place_element(888, 8880);
    cache.place_element(666, 6660);
    cache.place_element(333, 3330);
    cache.place_element(777, 7770);
    cache.place_element(555, 5550);
    cache.place_element(111, 1110);
    cache.place_element(444, 4440);
    cache.place_element(888, 8880);
    cache.place_element(1000, 10000);

    EXPECT_EQ(cache.n_cache_hit, 12);
}

TEST(TwoQCacheTest, Test8) {
    TwoQCache<int, int> cache(100);

    cache.place_element(1, 100);
    cache.place_element(2, 200);
    cache.place_element(3, 300);
    cache.place_element(4, 400);
    cache.place_element(5, 500);
    cache.place_element(1, 100);
    cache.place_element(2, 200);
    cache.place_element(6, 600);
    cache.place_element(3, 300);
    cache.place_element(7, 700);

    EXPECT_EQ(cache.n_cache_hit, 3);
}

TEST(TwoQCacheTest, Test9) {
    TwoQCache<int, int> cache(3, 2, 5);

    cache.place_element(101, 1010);
    cache.place_element(305, 3050);
    cache.place_element(509, 5090);
    cache.place_element(888, 8880);
    cache.place_element(222, 2220);
    cache.place_element(305, 3050);
    cache.place_element(999, 9990);
    cache.place_element(101, 1010);
    cache.place_element(707, 7070);
    cache.place_element(509, 5090);

    EXPECT_EQ(cache.n_cache_hit, 0);
}

TEST(TwoQCacheTest, Test10) {
    TwoQCache<int, int> cache(10);

    cache.place_element(145, 1450);
    cache.place_element(312, 3120);
    cache.place_element(478, 4780);
    cache.place_element(256, 2560);
    cache.place_element(389, 3890);
    cache.place_element(145, 1450);
    cache.place_element(478, 4780);
    cache.place_element(190, 1900);
    cache.place_element(256, 2560);
    cache.place_element(312, 3120);

    EXPECT_EQ(cache.n_cache_hit, 0);
}