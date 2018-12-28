test(
    'merge_sort_mt',
    executable(
        'merge_sort_mt_test',
        sources: ['merge_sort_mt_test.cc',
                  '../../project/merge_sort_mt/merge_sort_mt.cc'],
        include_directories: src,
        dependencies: [gtest],
        link_args: '-pthread'
    )
)