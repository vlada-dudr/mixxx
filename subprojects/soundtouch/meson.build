project('soundtouch', 'cpp', version: '2.1')

#add_project_arguments('-lomp', language: 'cpp')

omp_dep = dependency('openmp')

soundtouch_sources = [
  'AAFilter.cpp',
  'BPMDetect.cpp',
  'FIFOSampleBuffer.cpp',
  'FIRFilter.cpp',
  'InterpolateCubic.cpp',
  'InterpolateLinear.cpp',
  'InterpolateShannon.cpp',
  'PeakFinder.cpp',
  'RateTransposer.cpp',
  'SoundTouch.cpp',
  'TDStretch.cpp',
  # SoundTouch CPU optimizations are only for x86
  # architectures. SoundTouch automatically ignores these files
  # when it is not being built for an architecture that supports
  # them.
  'cpu_detect_x86.cpp',
  'mmx_optimized.cpp',
  'sse_optimized.cpp',
]

soundtouch_lib = static_library('soundtouch', sources: soundtouch_sources, dependencies: [ omp_dep ])

soundtouch_dep = declare_dependency(link_with: soundtouch_lib, include_directories: include_directories('.'))
