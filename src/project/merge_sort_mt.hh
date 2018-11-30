#ifndef MERGE_SORT_MT_HH
#define MERGE_SORT_MT_HH

#include <mutex>
#include <functional>
#include <vector>
#include <future>
#include <thread>
#include "merge_sort.cc"

template <typename RandomAccessIterator, typename Compare>
void merge_sort_mt(RandomAccessIterator begin, RandomAccessIterator end, const Compare comp);

template <typename RandomAccessIterator>
void merge_sort_mt(RandomAccessIterator begin, RandomAccessIterator end);

#endif