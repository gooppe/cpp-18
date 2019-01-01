subdir('server')
subdir('client')

executable(
    'server_benchmark',
    include_directories: src,
    sources: files(['benchmark.cc',
                    'server/server.cc',
                    'client/client.cc',
                    ]),
)