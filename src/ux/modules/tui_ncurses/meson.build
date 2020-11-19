# the name of the output
lib_name = 'uxdev_tui_ncurses'

# version numbers
lib_version_c=1
lib_version_r=0
lib_version_a=0

lib_formatted_version = 
  '@0@.@1@.@2@'.format((lib_version_c - lib_version_r),
    lib_version_a,
    lib_version_r)

project('libuxdev ' + lib_name,'c cpp',
  'GPL-3.0-or-later', version : lib_formatted_version)



# files included
lib_source_files = 
    ['tui_ncurses.cpp']

ncurses_dep = dependency('ncurses')
dl_dep = dependency('dl')

uxdev_lib_static = static_library(lib_name, 
  lib_source_files,
  dependencies : ncurses_dep,  
  version : lib_formatted_version,
  install : true)

uxdev_lib_shared = shared_library(lib_name,
  lib_source_files,
  dependencies : [ncurses_dep, dl_dep],
  version : lib_formatted_version,
  install : true)

