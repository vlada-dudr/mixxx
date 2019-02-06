project('fidlib', 'c')

if meson.get_compiler('c').get_id() == 'msvc'
  add_project_arguments([ '-DT_MSVC' ], language: 'c')
elif host_machine.system() == 'windows' ### windows but not MSVC -> MINGW
  add_project_arguments([ '-DT_MINGW' ], language: 'c')
else
  add_project_arguments([ '-DT_LINUX' ], language: 'c')
endif

fidlib = static_library(
  'fidlib',
  sources: 'fidlib.c'
)

fidlib_dep = declare_dependency(
  link_with: fidlib,
  include_directories: include_directories('.')
)
