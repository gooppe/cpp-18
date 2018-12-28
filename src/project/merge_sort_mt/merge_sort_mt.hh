/**
\file
*/
#ifndef MERGE_SORT_MT_HH
#define MERGE_SORT_MT_HH

#include <mutex>
#include <functional>
#include <vector>
#include <future>
#include <thread>
#include <project/merge_sort/merge_sort.cc>

/**
\brief
Параллельно сортирует массив данных исользуя алгоритм сортировки слиянием.
Число потоков равно число доступных ядер.
\date 2018-12-28
\param[in] begin итератор, указывающий на начало массива.
\param[in] end итератор, указывающий на следующий за последним элемент.
\return void
*/
template <typename RandomAccessIterator, typename Compare>
void merge_sort_mt(RandomAccessIterator begin, RandomAccessIterator end, const Compare comp);

/**
\brief
Параллельно сортирует массив данных исользуя алгоритм сортировки слиянием.
В качестве функции сравнения используется числовой оператор `меньше`.
Число потоков равно число доступных ядер.
\date 2018-12-28
\param[in] begin итератор, указывающий на начало массива.
\param[in] end итератор, указывающий на следующий за последним элемент.
\return void
*/
template <typename RandomAccessIterator>
void merge_sort_mt(RandomAccessIterator begin, RandomAccessIterator end);

#endif