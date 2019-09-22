mixxx_sources += files([ 
    'audiosource.cpp',
    'audiosourcestereoproxy.cpp',
    'metadatasourcetaglib.cpp',
    'soundsource.cpp',
    'soundsourceflac.cpp',
    'soundsourceoggvorbis.cpp',
    'soundsourceproviderregistry.cpp',
    'soundsourceproxy.cpp',
    'soundsourcesndfile.cpp',
])

if has_mad
    mixxx_sources += files('soundsourcemp3.cpp')
endif

if host_machine.system() == 'windows'
    mixxx_sources += files('soundsourcemediafoundation.cpp')
endif

#@TODO
if has_coreaudio
    mixxx_sources += files('soundsourcecoreaudio.cpp')
endif

if has_modplug
    mixxx_sources += files('soundsourcemodplug.cpp')
endif

if has_faad
  mixxx_sources += files([
    'soundsourcem4a.cpp',
    'libfaadloader.cpp',
  ])
endif

if has_wavpack
    mixxx_sources += files('soundsourcewv.cpp')
endif

if has_opus
    mixxx_sources += files('soundsourceopus.cpp')
endif

if has_ffmpeg
  mixxx_sources += files('soundsourceffmpeg.cpp')
endif

subdir('v1')
