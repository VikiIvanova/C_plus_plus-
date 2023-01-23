#pragma once

#include <iostream>
#include <vector>
#include <forward_list>

template <class Key, class Value, class Hash = std::hash<Key>>
class HashMap
{
public:
    HashMap();
    HashMap(size_t buckets);
    HashMap(const HashMap &) = default;
    HashMap &operator=(const HashMap &) = default;
    ~HashMap() = default;

    struct Data
    {
        Key key;
        Value value;
    };

    bool insert(const Key &key, const Value &value);
    bool insert(const Data &pair);
    bool erase(const Key &key);
    void clear();

    bool contains(const Key &key) const;
    Value &operator[](const Key &key);
    Value &at(const Key &key);
    const Value &at(const Key &key) const;

    size_t sizeFunc() const;
    size_t bucket_count() const;
    float load_factor() const;
    float max_load_factor() const;

    void max_load_factor(float factor);
    void rehash(size_t bucketsCaount);
    void reserve(size_t elemsCount);

    template <class Func>
    void for_each(Func func);

    template <class Func>
    void for_each(Func func) const;
    void print(std::ostream &out = std::cout) const;

private:
    size_t hash(const Key &key) const;
    const Data *find(const Key &key) const;
    Data *find(const Key &key);
    Data *add(const Key &key, const Value &value = {});
    Data *add(const Data &pair);

private:
    using HashRowArr = std::forward_list<Data>;
    using HashTableArr = std::vector<HashRowArr>;
    HashTableArr arr;
    size_t size;
    float maxLoadFactor;
};

template <class Key, class Value, class Hash>
std::ostream &operator<<(std::ostream &out, const HashMap<Key, Value, Hash> &map)
{
    map.print(out);
    return out;
}

const size_t DEFAULT_BUCKET_COUNT = 8;
const float DEFAULT_MAX_LOAD_FACTOR = 1;

template <class Key, class Value, class Hash>
inline HashMap<Key, Value, Hash>::HashMap() : arr(DEFAULT_BUCKET_COUNT),
                                              size(0),
                                              maxLoadFactor(DEFAULT_MAX_LOAD_FACTOR) {}

template <class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::insert(const Data &pair)
{
    return this->insert({key, value});
}

template <class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::insert(const Data &pair)
{
    if (this->contains(pair.key))
    {
        return false;
    }
    this->add(pair);
    return true;
}

template <class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::erase(const Key &key)
{
    size_t index = this->hash(key);
    typename HashRowArr::iterator eraseIt = arr[index].before_begin();
    typename HashRowArr::iterator compareIt = arr[index].begin();

    for (; compareIt != arr[index].end(); ++eraserIt, ++comparerIt)
    {
        if (compareIt->key == key)
        {
            arr[index].erase_after(eraserIt);
            --size;
            return true;
        }
    }
    return false;
}

template <class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::clear()
{
    arr.clear();
    size = 0;
}

template <class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::contains(const Key &key) const
{
    if (this->find(key))
        return true;

    return false;
}

template <class Key, class Value, class Hash>
inline Value &HashMap<Key, Value, Hash>::operator[](const Key &key)
{
    if (Data *found = this->find(key))
        return found->value;

    return this->add(key)->value;
}

template <class Key, class Value, class Hash>
inline Value &HashMap<Key, Value, Hash>::at(const Key &key)
{
    return const_cast<Value &>(((const HashMap<Key, Value, Hash> *)this)->at(key));
}

template <class Key, class Value, class Hash>
inline const Value &HashMap<Key, Value, Hash>::at(const Key &key) const
{
    if (Data *found = this->find(key))
        return found->value;

    throw std::out_of_range("HashMap: at(...) key not found in the hashmap!");
}

template<class Key, class Value, class Hash>
inline size_t HashMap<Key, Value, Hash>::sizeFunc() const
{
    return size;
}

template <class Key, class Value, class Hash>
inline size_t HashMap<Key, Value, Hash>::bucket_count() const
{
    return arr.size();
}

template <class Key, class Value, class Hash>
inline float HashMap<Key, Value, Hash>::load_factor() const
{
    return (float)this->size() / this->bucket_count();
}

template <class Key, class Value, class Hash>
inline float HashMap<Key, Value, Hash>::max_load_factor() const
{
    return maxLoadFactor;
}

template <class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::max_load_factor(float factor)
{
    maxLoadFactor = factor;
    size_t minBuckets = std::ceil(this->size() / this->max_load_factor());

    if (this->bucket_count() < minBuckets)
        this->rehash(minBuckets);
}

template <class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::rehash(size_t bucketsCount)
{
    size_t minBuckets = std::ceil(this->size() / this->max_load_factor());
    if (bucketsCount < minBuckets)
        bucketsCount = minBuckets;
    if (this->bucket_count() == bucketsCount)
        return;
    HashTableArr newArr(bucketsCount);
    std::swap(arr, newArr);
    size = 0;

    for (const std::forward_list<Data> &list : newArr)
        for (const Data &elem : list)
            this->insert(elem.key, elem.value);
}

template<class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::reserve(size_t elemsCount)
{
    this->rehash(std::ceil(elemsCount / this->max_load_factor()));
}

template<class Key, class Value, class Hash>
template<class Func>
inline void HashMap<Key, Value, Hash>::for_each(Func func) const
{
    for(const std::forward_list<Data>& list : arr)
       for(const Data& elem : list)
           func(elem);
}

template<class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::print(std::ostream& out) const
{
    this->for_each([&] (const Data& pair)
                   {
                    out << "(" << pair.key << "," << pair.value << ") ";
                   });
}

template<class Key, class Value, class Hash>
inline size_t HashMap<Key, Value, Hash>::hash(const Key& key) const
{
    return HashFunc(key) % this->bucket_count();
}

template<class Key, class Value, class Hash>
inline typename const HashMap<Key, Value, Hash>::Data*
HashMap<Key, Value, Hash>::find(const Key& key) const
{
    size_t index = this->hash(key);
    for(const Data& elem : arr[index])
       if(elem.key == key)
          return &elem;
    
    return nullptr;
}

template<class Key, class Value, class Hash>
inline typename HashMap<Key, Value, Hash>::Data*
                HashMap<Key, Value, Hash>::find(const Key& key)
{
    return const_cast<Data*>(((const HashMap<Key, Value, Hash>*) this) ->find(key));
}

template<class Key, class Value, class Hash>
inline typename HashMap<Key, Value, Hash>::Data*
HashMap<Key, Value, Hash>::add(const Key& key, const Value& value)
{
    return this->add(Data{key, value});
}

template<class Key, class Value, class Hash>
inline typename HashMap<Key, Value, Hash>::Data*
HashMap<Key, Value, Hash>::add(const Data& pair)
{
    size_t index = this->hash(pair.key);
    if((float) (this->size() + 1) / this->bucket_count() > this->max_load_factor())
       this->rehash(this->bucket_count() * 2);
    
    arr[index].push_front(pair);
    ++size;
    return &arr[index].front();
}
