#include <iostream>
#include <unordered_map>
#include "HashMap.hpp"

int main()
{
    HashMap<std::string, int> hash;
    
    hash[ "one"   ] = 1;
    hash[ "two"   ] = 2;
    hash[ "three" ] = 3;
    hash[ "four"  ] = 4;
    hash[ "five"  ] = 5;
    hash[ "six"   ] = 6;
    hash[ "seven" ] = 7;
    hash[ "eight" ] = 8;

    std::cout << "Original hashmap: \n" << hash;
    std::cout << "\nBuckets: " << hash.bucket_count() << ", Load factor: " << hash.load_factor() << ", Size: " << hash.sizeFunc();

    float mlf = 0.5;
    hash.max_load_factor( mlf );

    std::cout << "\n\nChanged max load factor to " << mlf << ":\n" << hash;
    std::cout << "\nBuckets: " << hash.bucket_count() << ", Load factor: " << hash.load_factor() << ", Size: " << hash.sizeFunc();

    size_t resCount = 12;
    hash.reserve( resCount );

    std::cout << "\n\nreserve(" << resCount << "):\n" << hash;
    std::cout << "\nBuckets: " << hash.bucket_count() << ", Load factor: " << hash.load_factor() << ", Size: " << hash.sizeFunc();

    std::string eraseKey = "four";
    hash.erase( eraseKey );

    std::cout << "\n\nerase(" << eraseKey << "):\n" << hash;
    std::cout << "\nBuckets: " << hash.bucket_count() << ", Load factor: " << hash.load_factor() << ", Size: " << hash.sizeFunc();

    hash.clear();
    std::cout << "\n\nclear():" << hash;
    std::cout << "\nBuckets: " << hash.bucket_count() << ", Load factor: " << hash.load_factor() << ", Size: " << hash.sizeFunc();

    std::cout << "\n";

    return 0;