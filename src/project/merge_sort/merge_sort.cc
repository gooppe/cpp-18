#include <project/merge_sort/merge_sort.hh>

template <typename RandomAccessIterator, typename Compare>
void merge(RandomAccessIterator begin, RandomAccessIterator middle, RandomAccessIterator end, const Compare comp)
{
    std::vector<typename RandomAccessIterator::value_type> buffer;

    auto left_iter = begin;
    auto right_iter = middle;

    while (left_iter != middle && right_iter != end)
        buffer.push_back(comp(*left_iter, *right_iter) ? *left_iter++ : *right_iter++);
    buffer.insert(buffer.end(), left_iter, middle);
    buffer.insert(buffer.end(), right_iter, end);

    std::move(buffer.begin(), buffer.end(), begin);
}

template <typename RandomAccessIterator, typename Compare>
void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, const Compare comp)
{
    auto size = std::distance(begin, end);
    if (size < 2)
        return;

    auto middle = std::next(begin, size / 2);
    merge_sort(begin, middle, comp);
    merge_sort(middle, end, comp);

    merge(begin, middle, end, comp);
}

template <typename RandomAccessIterator>
void merge_sort(const RandomAccessIterator begin, const RandomAccessIterator end)
{
    merge_sort(begin, end, std::less<typename RandomAccessIterator::value_type>());
}