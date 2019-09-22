project('replaygain', 'cpp')
replaygain_lib = static_library(
  'replaygain',
  sources: 'replaygain.cpp'
)

replaygain_dep = declare_dependency(
  link_with: replaygain_lib,
  include_directories: '.'
)
