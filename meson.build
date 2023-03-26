project('libSAOCPPYield', 'cpp',
  version : '1.0.0',
  license : 'GPL-3.0-only',
  default_options : [
    'warning_level=1',
    'werror=true'
  ]
)

src = []

inc = [
  include_directories('include')
]

deps_for_build = []

lib = static_library('SAOCPPYield', src,
  include_directories : inc,
  dependencies : deps_for_build
)

deps_for_use = []

dep = declare_dependency(
  include_directories : inc,
  link_with : [
    lib
  ],
  dependencies : deps_for_use
)

subdir('test')
