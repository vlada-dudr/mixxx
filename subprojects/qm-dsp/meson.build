project('qm-dsp', 'cpp')
add_languages('c')
add_project_arguments([ '-Dkiss_fft_scalar=double' ], language: 'cpp')

if host_machine.system() != 'windows'
  add_project_arguments([ '-DUSE-PTHREADS' ], language: 'cpp')
endif

sources = [
  #'base/KaiserWindow.cpp',
  'base/Pitch.cpp',
  #'base/SincWindow.cpp',
  'dsp/chromagram/CQprecalc.cpp',
  'dsp/chromagram/Chromagram.cpp',
  'dsp/chromagram/ConstantQ.cpp',
  'dsp/keydetection/GetKeyMode.cpp',
  #'dsp/mfcc/MFCC.cpp',
  'dsp/onsets/DetectionFunction.cpp',
  'dsp/onsets/PeakPicking.cpp',
  'dsp/phasevocoder/PhaseVocoder.cpp',
  'dsp/rateconversion/Decimator.cpp',
  #'dsp/rateconversion/DecimatorB.cpp',
  #'dsp/rateconversion/Resampler.cpp',
  #'dsp/rhythm/BeatSpectrum.cpp',
  #'dsp/segmentation/ClusterMeltSegmenter.cpp',
  #'dsp/segmentation/Segmenter.cpp',
  #'dsp/segmentation/cluster_melt.c',
  #'dsp/segmentation/cluster_segmenter.c',
  'dsp/signalconditioning/DFProcess.cpp',
  'dsp/signalconditioning/FiltFilt.cpp',
  'dsp/signalconditioning/Filter.cpp',
  'dsp/signalconditioning/Framer.cpp',
  'dsp/tempotracking/DownBeat.cpp',
  'dsp/tempotracking/TempoTrack.cpp',
  'dsp/tempotracking/TempoTrackV2.cpp',
  'dsp/tonal/ChangeDetectionFunction.cpp',
  'dsp/tonal/TCSgram.cpp',
  'dsp/tonal/TonalEstimator.cpp',
  'dsp/transforms/FFT.cpp',
  #'dsp/wavelet/Wavelet.cpp',
  'ext/kissfft/kiss_fft.c',
  'ext/kissfft/kiss_fftr.c',
  #'hmm/hmm.c',
  'maths/Correlation.cpp',
  #'maths/CosineDistance.cpp',
  'maths/KLDivergence.cpp',
  'maths/MathUtilities.cpp',
  #'maths/pca/pca.c',
  #'thread/Thread.cpp'
]

qm_lib = static_library(
  'qm',
  sources: sources
)

qm_dep = declare_dependency(
  link_with: qm_lib,
  include_directories: include_directories('.')
)
