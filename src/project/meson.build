project_src = files([
    'main.cc',
    'merge_sort_mt.cc'
])

executable(
    'project',
    include_directories: src,
    sources: project_src,
    dependencies: [],
    install: true
)

executable(
    'line_enum',
    include_directories: src,
    sources: files(['line_enum.cc',
                    'line_number_buffer.cc']),
    dependencies: []
    
)