project('mixxx','cpp',
    default_options : ['cpp_std=c++14', 'warning_level=2'],
    version: '2.3-alpha-pre'
)
cpp = meson.get_compiler('cpp')

#soundtouch_sub = subproject('soundtouch')


cdata = configuration_data()
git = find_program('git')
git_run = run_command(git,'log', '--pretty=oneline', '--first-parent')
if git_run.returncode() == 0
    git_revision = git_run.stdout().split('\n').length()
    cdata.set_quoted('BUILD_REV', '@0@'.format(git_revision))
else
    git_revision = ''
endif

git_run = run_command(git,'rev-parse', '--abbrev-ref', 'HEAD')
if git_run.returncode() == 0
    git_branch = git_run.stdout().split('\n').get(0).strip()
    if not git_branch.startswith('release')
      cdata.set_quoted('BUILD_BRANCH', git_branch)
    endif
else
    git_branch = ''
endif

config_file = configure_file(configuration: cdata, output: 'build.h')

#error('BRANCH: @0@ REV: @1@'.format(git_branch, git_revision))
#+' REV: '+git_revision)

if get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized'
    add_project_arguments( '-DMIXXX_BUILD_DEBUG', language: 'cpp')
elif get_option('buildtype') == 'release'
    add_project_arguments( '-DMIXXX_BUILD_RELEASE', '-DNDEBUG', language: 'cpp')

    if host_machine.system() == 'windows'
        add_project_arguments('-DQ_ASSERT(x)=qt_noop()', language: 'cpp')
    else
        add_project_arguments('-DQ_ASSERT(x)=static_cast<void>(false&&(x))', language: 'cpp')
    endif
endif

if get_option('buildtype') == 'release' or get_option('buildtype') == 'debugoptimized'
  if cpp.has_argument('-ffast-math')
    add_project_arguments('-ffast-math', language: 'cpp')
  endif
  if cpp.has_argument('-funroll-loops')
    add_project_arguments('-funroll-loops', language: 'cpp')
  endif
endif

add_project_arguments(
    '-DSETTINGS_PATH=".mixxx"',
    '-DSETTINGS_FILE="mixxx.cfg"',
    '-D__SNDFILE__',
    #'-DSFC_SUPPORTS_SET_COMPRESSION_LEVEL',
    #'-Dkiss_fft_scalar=double',
    language: 'cpp')

fidlib_sub = subproject('fidlib')
qm_sub = subproject('qm-dsp') # Queen Mary beattracker
replaygain_sub = subproject('replaygain')

dependencies = [
    dependency('portaudio-2.0'),
    cpp.find_library('porttime'),
    cpp.find_library('portmidi'),
    cpp.find_library('m', required: false),
    cpp.find_library('rt', required: false),
    cpp.find_library('libmp3lame'),
    #dependency('libmp3lame', fallback: ['lame', 'lame_dep']),
    dependency('sndfile'),
    dependency('flac'),
    dependency('ogg',       fallback: ['ogg',    'ogg_dep']),
    dependency('vorbisfile',fallback: ['vorbis', 'vorbisfile_dep']),
    dependency('vorbis',    fallback: ['vorbis', 'vorbis_dep']),
    dependency('vorbisenc', fallback: ['vorbis', 'vorbisenc_dep']),
    #dependency('gl'),
    #dependency('glu'),
    dependency('taglib'),
    dependency('protobuf-lite', fallback: ['protobuf', 'protobuf_lite_dep']),
    dependency('libchromaprint'),
    dependency('rubberband'),
    dependency('soundtouch', fallback: ['soundtouch', 'soundtouch_dep']),
    dependency('threads'),
    dependency('zlib'),
    qm_sub.get_variable('qm_dep'), # Queen Mary beattracker
    fidlib_sub.get_variable('fidlib_dep'),
    replaygain_sub.get_variable('replaygain_dep'),
    dependency('gtest', fallback: ['gtest', 'gtest_dep']),
    dependency('gmock', fallback: ['gtest', 'gmock_dep'])
]

if host_machine.system() == 'darwin'
    dependencies += dependency('appleframeworks', modules:[
        'Security', #The iOS/OS X security framework is used to implement sandboxing.
        'CoreServices'
        ])
endif

qt5modules = [
    'Core',
    'Gui',
    'Widgets',
    'Network',
    'Test',
    'DBus',
    'OpenGL',
    'Script',
    'ScriptTools',
    'Svg',
    'Sql',
    'Xml',
    'Concurrent'
]

if cpp.has_header_symbol('sndfile.h', 'SFC_SET_COMPRESSION_LEVEL')
  add_project_arguments(
    '-DSFC_SUPPORTS_SET_COMPRESSION_LEVEL',
    language: 'cpp')
endif

# i removed bsd... Maybe we could support it again!
if host_machine.system() == 'windows'
    #improve!
    # I kicked out _ATL_XP_TARGETING
    add_project_arguments([
        '-D__WINDOWS__',
        '-D_ATL_MIN_CRT',
        '-DNOMINMAX',
        '-DUNICODE',
        # should be here for 32-bit builds?
        '-DWIN64',
        '-D_USE_MATH_DEFINES' ],
        language: 'cpp'
    )

elif host_machine.system() == 'linux'
    add_project_arguments([
        '-D__LINUX__',
        '-D__UNIX__',
        '-DUNIX_SHARE_PATH="'+join_paths(get_option('prefix'),get_option('datadir'),meson.project_name())+'"',
        '-DUNIX_LIB_PATH="'+join_paths(get_option('prefix'),get_option('libdir'),meson.project_name())+'"',
        ],
        language: 'cpp'
    )
    dependencies += dependency('x11')
    qt5modules += 'X11Extras'
endif



if host_machine.system() == 'darwin'
    # homebrew etc...
    includes += include_directories('/usr/local/lib')
endif

includes = []
mixxx_headers = []
mixxx_sources = []
mixxx_ui = []

ebur_dep = dependency('libebur128', required: false)

if ebur_dep.found()
    dependencies += ebur_dep
else
    mixxx_sources += 'lib/libebur128/ebur128/ebur128.c'
    includes += include_directories('lib/libebur128/ebur128/')
endif

if get_option('opengles').enabled()
    add_project_arguments('-D__OPENGLES__', language: 'cpp')
endif

has_bulk = false
libusb_dep = dependency('libusb-1.0', required: get_option('bulk'))
if libusb_dep.found()
  has_bulk = true
  message('BULK feature enabled')
  add_project_arguments('-D__BULK__', language: 'cpp')
  dependencies += libusb_dep
endif

has_hid = false
hidapi_dep = dependency('hidapi-libusb', required: get_option('hid'))
if hidapi_dep.found()
  # libusb is used also in hid, so might be found already
  if not libusb_dep.found()
    libusb_dep = dependency('libusb-1.0', required: get_option('hid'))
    dependencies += libusb_dep
  endif

  if libusb_dep.found()
    has_hid = true
    message('HID feature enabled')
    add_project_arguments('-D__HID__', language: 'cpp')

    # @TODO: fallback to internal
    dependencies += hidapi_dep
  endif
endif


has_vinylcontrol = false
if get_option('vinylcontrol').enabled()
  has_vinylcontrol = true
  message('VINYLCONTROL feature enabled')

  add_project_arguments('-D__VINYLCONTROL__', language: 'cpp')

    includes += include_directories([
        'lib/xwax',
    ])

    if host_machine.system() == 'windows'
        mixxx_sources += [
            'lib/xwax/timecoder_win32.cpp',
            'lib/xwax/lut_win32.cpp'
        ]
    else
        mixxx_sources += [
            'lib/xwax/timecoder.c',
            'lib/xwax/lut.c',
        ]
    endif
endif

has_modplug = false
modplug_dep = dependency('modplug', required: get_option('modplug'))
if modplug_dep.found()
  has_modplug = true
  message('MODPLUG feature enabled')
  add_project_arguments('-D__MODPLUG__', language: 'cpp')
  dependencies += modplug_dep
endif

has_mad = false
mad_dep = dependency('mad', required: get_option('mad'))
if mad_dep.found()
  has_mad = true
  message('MAD feature enabled')
  add_project_arguments('-D__MAD__', language: 'cpp')

    dependencies += [ mad_dep, dependency('id3tag') ]
endif

has_faad = false
faad_dep = cpp.find_library('faad', required: get_option('faad'))
libmp4v2_dep = cpp.find_library('libmp4v2', required: get_option('faad'))
if faad_dep.found() and libmp4v2_dep.found()
  has_faad = true
  message('FAAD feature enabled')
  add_project_arguments('-D__FAAD__', language: 'cpp')
  add_project_arguments('-D__MP4V2__', language: 'cpp')
  dependencies += [ faad_dep, libmp4v2_dep ]
endif

has_wavpack = false
wavpack_dep = dependency('wavpack', required:get_option('wv'))
if wavpack_dep.found()
  has_wavpack = true
  message('WV feature enabled')
  add_project_arguments('-D__WV__', language: 'cpp')
  dependencies += wavpack_dep
endif


has_opus = false
opusfile_dep = dependency('opusfile', required: get_option('opus'))
opus_dep = dependency('opus', required: get_option('opus'))
if opus_dep.found() and opusfile_dep.found()
  has_opus = true
  message('OPUS feature enabled')
  add_project_arguments('-D__OPUS__', language: 'cpp')
  dependencies += [opus_dep, opusfile_dep]
endif

has_ffmpeg = false
ffmpeg_dep = dependency('ffmpeg', required: get_option('ffmpeg'))
if ffmpeg_dep.found()
  has_ffmpeg = true
  message('FFMPEG feature enabled')
  add_project_arguments('-D__FFMPEG__', language: 'cpp')
  dependencies += ffmpeg_dep
endif

#@TODO
has_coreaudio = false
if get_option('coreaudio').enabled() or (get_option('coreaudio').auto() and host_machine.system() == 'darwin')
  if host_machine.system() != 'darwin'
    error('Coreaudio is available only on Darwin platform')
  endif
  has_coreaudio = true
  dependencies += dependency('appleframeworks', 'audiotoolbox', 'corefoundation')
  message('COREAUDIO feature enabled')
  add_project_arguments('-D__COREAUDIO__', language: 'cpp')
endif


has_battery = false
if host_machine.system() == 'windows' and not get_option('battery').disabled()
  has_battery = true
elif host_machine.system() == 'linux'
  battery_dep = dependency('upower-glib', required: get_option('battery'))
elif host_machine.system() == 'darwin'
  ## is it correct?
  battery_dep = dependency('appleframeworks', modules: 'IOKit', required: get_option('battery'))
endif

if battery_dep.found() or has_battery
  has_battery = true
  message('BATTERY feature enabled')
  add_project_arguments('-D__BATTERY__', language: 'cpp')
  if is_variable('battery_dep')
    dependencies += battery_dep
  endif

endif

has_lilv = false
lilv_dep = dependency('lilv-0', required: get_option('lilv'))
if lilv_dep.found()
  has_lilv = true
  add_project_arguments('-D__LILV__', language: 'cpp')
  dependencies += lilv_dep
endif

has_broadcast = false
shout_dep = dependency('shout', required: get_option('broadcast').enabled())
if shout_dep.found()
  has_broadcast = true
    add_project_arguments('-D__BROADCAST__', language: 'cpp')
    dependencies += shout_dep
endif

has_hss1394 = false
#@TODO

if get_option('localecompare').enabled()
    if get_option('qt_sqlite_plugin').enabled()
        error('Options localecompare and qt_sqlite_plugin are incompatible')
    endif
    add_project_arguments('-D__SQLITE3__', language: 'cpp')
    dependencies += [
        dependency('sqlite3', fallback: [ 'sqlite', 'sqlite_dep' ])
    ]
endif

#@TODO
#if get_option('qt_sqlite_plugin').enabled()
    #qt5modules += 'Sql'
#endif

#@TODO
#if meson.get_compiler('cpp').get_define('-ffast-math')
    mixxx_sources += 'src/util/fpclassify.cpp'
#endif


protobuf_files = [
    'src/proto/beats.proto',
    'src/proto/headers.proto',
    'src/proto/keys.proto',
    'src/proto/skin.proto',
    'src/proto/waveform.proto'
]

protoc = find_program('protoc')
proto_gen = generator(protoc,
  output    : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h'],
  arguments : ['--proto_path=@SOURCE_DIR@/src/proto', '--cpp_out=@BUILD_DIR@/proto', '@INPUT@'])

protos = []

foreach pb_file : protobuf_files
    protos += proto_gen.process(pb_file, preserve_path_from: meson.current_source_dir()+'/src/')
endforeach

qt5 = import('qt5')
qt5dep = dependency('qt5', modules : qt5modules)

subdir('src')
subdir('lib')

prep = qt5.preprocess(
    moc_headers : mixxx_headers,
    ui_files : mixxx_ui,
    include_directories: includes
)

qrc = qt5.preprocess(
    qresources: 'res/mixxx.qrc'
)

libmixxx = static_library(
    'mixxx',
    sources : [mixxx_sources, prep, protos ],
    dependencies : [qt5dep, dependencies ],
    include_directories: includes,
    install : false
)

mixxx = executable(
    'mixxx',
    dependencies : [dependency('gl'), qt5dep],
    sources : ['src/main.cpp', qrc, protos],
    include_directories: includes,
    link_with : [ libmixxx],
    install : true
)

install_subdir('res/controllers',  install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/skins',        install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/fonts',        install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/keyboard',     install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/translations', install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)

#subdir('src/test')
