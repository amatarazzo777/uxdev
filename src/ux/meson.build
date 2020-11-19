# the name of the output
lib_name = 'uxdev'

# files included
runtime_sources = 
    ['data_layer.cpp',
    'document_management.cpp",
    "element_object.cpp',
    'event_dispatcher.cpp',
    'platform_module.cpp',
    'window.cpp']

# version numbers
libruntime_lt_c=1
libruntime_lt_r=0
libruntime_lt_a=0

uxdev_lib_static = static_library(lib_name, runtime_sources, install : true)

libruntime_so_version = '@0@.@1@.@2@'.format((libruntime_lt_c - libruntime_lt_a),
                                              libruntime_lt_a,
                                              libruntime_lt_r)

uxdev_lib_shared = shared_library(lib_name,
                            runtime_sources,
                            version : libruntime_so_version,
                            install : true)

subdir('modules')

