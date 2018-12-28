#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <algorithm>
#include <functional>

template <typename RandomAccessIterator, typename Compare>
void merge(RandomAccessIterator begin, RandomAccessIterator middle, RandomAccessIterator end, const Compare comp);

template <typename RandomAccessIterator, typename Compare>
void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, const Compare comp);

template <typename RandomAccessIterator>
void merge_sort(const RandomAccessIterator begin, const RandomAccessIterator end);

#endif