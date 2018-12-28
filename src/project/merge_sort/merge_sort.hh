/**
\file
*/
#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <algorithm>
#include <functional>

template <typename RandomAccessIterator, typename Compare>
void merge(RandomAccessIterator begin, RandomAccessIterator middle, RandomAccessIterator end, const Compare comp);

/**
\brief
Сортирует массив данных исользуя алгоритм сортировки слиянием.
\date 2018-12-28
\param[in] begin итератор, указывающий на начало массива.
\param[in] end итератор, указывающий на следующий за последним элемент.
\param[in] comp функция сравнения элементов массива.
\return void
*/
template <typename RandomAccessIterator, typename Compare>
void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, const Compare comp);

/**
\brief
Сортирует массив данных исользуя алгоритм сортировки слиянием. В качестве функции сравнения используется числовой оператор `меньше`.
\date 2018-12-28
\param[in] begin итератор, указывающий на начало массива.
\param[in] end итератор, указывающий на следующий за последним элемент.
\return void
*/
template <typename RandomAccessIterator>
void merge_sort(const RandomAccessIterator begin, const RandomAccessIterator end);

#endif