gtest = dependency('gtest', main: true)
test(
    'vector',
    executable(
        'vector_test',
        sources: ['vector_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)

test(
    'message',
    executable(
        'message_test',
        sources: ['message_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)

test(
    'array2d',
    executable(
        'array2d_test',
        sources: ['array2d_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)

test(
    'ostream_iterator',
    executable(
        'ostream_iterator',
        sources: ['ostream_iterator_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)

test(
    'merge_sort',
    executable(
        'merge_sort',
        sources: ['merge_sort_test.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)

test(
    'user_manager',
    executable(
        'user_manager',
        include_directories: src,
        sources: files(['user_manager_test.cc',
                        '../project/user_manager.cc']),
        dependencies: [gtest]
    )
)

test(
    'line_number_buffer',
    executable(
        'line_number_buffer',
        include_directories: src,
        sources: files(['line_number_buffer_test.cc',
                        '../project/line_number_buffer.cc']),
        dependencies: [gtest]
    )
)

test(
    'merge_sort_mt',
    executable(
        'merge_sort_mt',
        sources: ['merge_sort_test.cc', 
                  '../project/merge_sort_mt.cc'],
        include_directories: src,
        dependencies: [gtest]
    )
)