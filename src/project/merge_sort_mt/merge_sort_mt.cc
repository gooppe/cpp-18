#include <project/merge_sort_mt/merge_sort_mt.hh>

template <typename RandomAccessIterator, typename Compare>
void merge_sort_mt(RandomAccessIterator begin, RandomAccessIterator end, const Compare comp)
{
    auto elements = std::distance(begin, end);
    auto n_threads = std::thread::hardware_concurrency();
    auto elem_per_thread = elements / n_threads;

    std::vector<std::future<void>> tasks;
    std::vector<std::thread> threads;

    for (uint i = 0; i < n_threads; i++)
    {
        std::packaged_task<void(RandomAccessIterator, RandomAccessIterator, Compare)> task(
            [](RandomAccessIterator start, RandomAccessIterator end, Compare c) { return merge_sort(start, end, c); });
        tasks.push_back(task.get_future());
        threads.push_back(std::thread(std::move(task), begin + i * elem_per_thread, begin + (i + 1) * elem_per_thread, comp));
    }
    std::packaged_task<void(RandomAccessIterator, RandomAccessIterator, Compare)> ltask(
        [](RandomAccessIterator start, RandomAccessIterator end, Compare c) { return merge_sort(start, end, c); });
    tasks.push_back(ltask.get_future());
    threads.push_back(std::thread(std::move(ltask), begin + n_threads * elem_per_thread, end, comp));

    for (auto &th : threads)
        th.join();

    std::vector<RandomAccessIterator> bounds;
    for (uint i = 0; i <= n_threads; i++)
        bounds.push_back(begin + i * elem_per_thread);
    if ((begin + n_threads * elem_per_thread) != end)
        bounds.push_back(end);

    while (bounds.size() > 2)
    {
        // |1|2|3|4|o|
        std::vector<std::future<void>> merge_tasks;
        std::vector<std::thread> merge_threads;
        for (uint i = 0; i < std::min(n_threads, ((uint)bounds.size() - 1) / 2); i++)
        {
            std::packaged_task<void(RandomAccessIterator, RandomAccessIterator, RandomAccessIterator, Compare)> merge_task(
                [](RandomAccessIterator start, RandomAccessIterator middle, RandomAccessIterator end, Compare c) { return merge(start, middle, end, c); });
            // merge_task(bounds[i], bounds[i + 1], bounds[i + 2], comp);
            merge_tasks.push_back(merge_task.get_future());
            merge_threads.push_back(std::thread(std::move(merge_task), bounds[i], bounds[i + 1], bounds[i + 2], comp));
            bounds.erase(bounds.begin() + i + 1);
        }
        for (auto &th : merge_threads)
        {
            th.join();
        }
    }
}

template <typename RandomAccessIterator>
void merge_sort_mt(const RandomAccessIterator begin, const RandomAccessIterator end)
{
    merge_sort_mt(begin, end, std::less<typename RandomAccessIterator::value_type>());
}
