project('mixxx','cpp',
    default_options : ['cpp_std=c++11', 'warning_level=2'],
    version: '2.3-alpha-pre'
)

#soundtouch_sub = subproject('soundtouch')

# fidlib... Maybe move it to subproject?
add_languages('c')

git = find_program('git')
git_run = run_command(git,'rev-parse', '--short', 'HEAD')
if git_run.returncode() == 0
    git_revision = git_run.stdout()
else
    git_revision = ''
endif



dependencies = [
    dependency('portaudio-2.0'),
    meson.get_compiler('cpp').find_library('porttime'),
    meson.get_compiler('cpp').find_library('portmidi'),
    meson.get_compiler('cpp').find_library('m', required: false),
    meson.get_compiler('cpp').find_library('rt', required: false),
    meson.get_compiler('cpp').find_library('libmp3lame'),
    dependency('sndfile'),
    dependency('flac'),
    dependency('vorbisfile'),
    dependency('vorbis'),
    dependency('vorbisenc'),
    dependency('ogg'),
    #dependency('gl'),
    #dependency('glu'),
    dependency('taglib'),
    dependency('protobuf-lite'),
    dependency('libchromaprint'),
    dependency('rubberband'),
    dependency('soundtouch'),
    dependency('threads'),
    # meson build extra
    dependency('gtest'),
    dependency('gmock')
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

elif host_machine.system() == 'darwin'
    # homebrew etc...
    includes += include_directories('/usr/local/lib')
endif


includes = [
    'src',
    'lib/qtscript-bytearray',
    'lib/portaudio',
    'lib/fidlib',
    'lib/replaygain',
    'lib/reverb'
]

mixxx_headers =    [
    'src/analyzer/analyzerqueue.h',
    'src/control/control.h',
    'src/control/controlaudiotaperpot.h',
    'src/control/controleffectknob.h',
    'src/control/controlencoder.h',
    'src/control/controlindicator.h',
    'src/control/controllinpotmeter.h',
    'src/control/controllogpotmeter.h',
    'src/control/controlpotmeter.h',
    'src/control/controlproxy.h',
    'src/control/controlpushbutton.h',
    'src/control/controlttrotary.h',
    'src/control/controlmodel.h',
    'src/control/controlobject.h',
    'src/control/controlobjectscript.h',
    'src/controllers/controller.h',
    'src/controllers/controllerengine.h',
    'src/controllers/controllerenumerator.h',
    'src/controllers/controllerinputmappingtablemodel.h',
    'src/controllers/controllerlearningeventfilter.h',
    'src/controllers/controlleroutputmappingtablemodel.h',
    'src/controllers/controllermanager.h',
    'src/controllers/controllermappingtablemodel.h',
    'src/controllers/controlpickermenu.h',
    'src/controllers/delegates/controldelegate.h',
    'src/controllers/delegates/midioptionsdelegate.h',
    'src/controllers/keyboard/keyboardeventfilter.h',
    'src/controllers/midi/midicontroller.h',
    'src/controllers/midi/midienumerator.h',
    'src/controllers/midi/midioutputhandler.h',
    'src/controllers/midi/portmidienumerator.h',
    'src/controllers/midi/portmidicontroller.h',
    'src/controllers/dlgcontrollerlearning.h',
    'src/controllers/dlgprefcontrollers.h',
    'src/database/mixxxdb.h',
    'src/controllers/dlgprefcontroller.h',
    'src/dialog/dlgabout.h',
    'src/dialog/dlgdevelopertools.h',
    'src/effects/builtin/builtinbackend.h',
    'src/effects/effect.h',
    'src/effects/effectbuttonparameterslot.h',
    'src/effects/effectchain.h',
    'src/effects/effectchainmanager.h',
    'src/effects/effectchainslot.h',
    'src/effects/effectparameter.h',
    'src/effects/effectparameterslot.h',
    'src/effects/effectparameterslotbase.h',
    'src/effects/effectrack.h',
    'src/effects/effectsbackend.h',
    'src/effects/effectslot.h',
    'src/effects/effectsmanager.h',
    'src/effects/lv2/lv2backend.h',
    'src/engine/bpmcontrol.h',
    'src/engine/cachingreader.h',
    'src/engine/cachingreaderworker.h',
    'src/engine/clockcontrol.h',
    'src/engine/cuecontrol.h',
    'src/engine/engineaux.h',
    'src/engine/enginebufferscale.h',
    'src/engine/enginebufferscalerubberband.h',
    'src/engine/enginebufferscalest.h',
    'src/engine/enginecontrol.h',
    'src/engine/enginedeck.h',
    'src/engine/enginedelay.h',
    'src/engine/enginefilter.h',
    'src/engine/enginefilterbessel4.h',
    'src/engine/enginefilterbessel8.h',
    'src/engine/enginefilterbiquad1.h',
    'src/engine/enginefilterbutterworth4.h',
    'src/engine/enginefilterbutterworth8.h',
    'src/engine/enginefilterlinkwitzriley4.h',
    'src/engine/enginefilterlinkwitzriley2.h',
    'src/engine/enginefilterlinkwitzriley8.h',
    'src/engine/enginefiltermoogladder4.h',
    'src/engine/enginemaster.h',
    'src/engine/enginemicrophone.h',
    'src/engine/engineobject.h',
    'src/engine/enginetalkoverducking.h',
    'src/engine/enginevumeter.h',
    'src/engine/engineworker.h',
    'src/engine/engineworkerscheduler.h',
    'src/engine/loopingcontrol.h',
    'src/engine/quantizecontrol.h',
    'src/engine/ratecontrol.h',
    'src/engine/sidechain/enginerecord.h',
    'src/engine/sidechain/enginesidechain.h',
    'src/engine/sync/internalclock.h',
    'src/engine/sync/synccontrol.h',
    'src/engine/enginebuffer.h',
    'src/engine/enginechannel.h',
    'src/engine/keycontrol.h',
    'src/errordialoghandler.h',
    'src/library/analysisfeature.h',
    'src/library/analysislibrarytablemodel.h',
    'src/library/autodj/autodjfeature.h',
    'src/library/autodj/autodjprocessor.h',
    'src/library/autodj/dlgautodj.h',
    'src/library/banshee/bansheeplaylistmodel.h',
    'src/library/banshee/bansheefeature.h',
    'src/library/baseexternallibraryfeature.h',
    'src/library/baseexternalplaylistmodel.h',
    'src/library/baseexternaltrackmodel.h',
    'src/library/basesqltablemodel.h',
    'src/library/basetrackcache.h',
    'src/library/browse/browsefeature.h',
    'src/library/baseplaylistfeature.h',
    'src/library/browse/browsethread.h',
    'src/library/browse/foldertreemodel.h',
    'src/library/browse/browsetablemodel.h',
    'src/library/columncache.h',
    'src/library/coverartdelegate.h',
    'src/library/coverartcache.h',
    'src/library/crate/cratefeature.h',
    'src/library/crate/cratefeaturehelper.h',
    'src/library/crate/cratetablemodel.h',
    'src/library/dao/autodjcratesdao.h',
    'src/library/dao/cue.h',
    'src/library/dao/playlistdao.h',
    'src/library/dao/trackdao.h',
    'src/library/export/trackexportwizard.h',
    'src/library/export/trackexportworker.h',
    'src/library/export/trackexportdlg.h',
    'src/library/hiddentablemodel.h',
    'src/library/itunes/itunesfeature.h',
    'src/library/library.h',
    'src/library/librarycontrol.h',
    'src/library/libraryfeature.h',
    'src/library/librarytablemodel.h',
    'src/library/missingtablemodel.h',
    'src/library/mixxxlibraryfeature.h',
    'src/library/parserm3u.h',
    'src/library/parserpls.h',
    'src/library/playlistfeature.h',
    'src/library/playlisttablemodel.h',
    'src/library/previewbuttondelegate.h',
    'src/library/parsercsv.h',
    'src/library/recording/recordingfeature.h',
    'src/library/rhythmbox/rhythmboxfeature.h',
    'src/library/scanner/importfilestask.h',
    'src/library/recording/dlgrecording.h',
    'src/library/scanner/libraryscanner.h',
    'src/library/scanner/libraryscannerdlg.h',
    'src/library/scanner/recursivescandirectorytask.h',
    'src/library/scanner/scannertask.h',
    'src/library/setlogfeature.h',
    'src/library/songdownloader.h',
    'src/library/sidebarmodel.h',
    'src/library/stardelegate.h',
    'src/library/stareditor.h',
    'src/library/tableitemdelegate.h',
    'src/library/trackcollection.h',
    'src/library/traktor/traktorfeature.h',
    'src/library/treeitemmodel.h',
    'src/library/bpmdelegate.h',
    'src/library/dlganalysis.h',
    'src/library/dlgcoverartfullsize.h',
    'src/library/dlghidden.h',
    'src/library/dlgtagfetcher.h',
    'src/library/dlgmissing.h',
    'src/library/dlgtrackinfo.h',
    'src/library/dlgtrackmetadataexport.h',
    'src/mixer/auxiliary.h',
    'src/mixer/baseplayer.h',
    'src/mixer/basetrackplayer.h',
    'src/mixer/deck.h',
    'src/mixer/microphone.h',
    'src/mixer/playerinfo.h',
    'src/mixer/previewdeck.h',
    'src/mixer/sampler.h',
    'src/mixer/samplerbank.h',
    'src/mixer/playermanager.h',
    'src/mixxx.h',
    'src/musicbrainz/acoustidclient.h',
    'src/mixxxapplication.h',
    'src/musicbrainz/chromaprinter.h',
    'src/musicbrainz/musicbrainzclient.h',
    'src/musicbrainz/network.h',
    'src/musicbrainz/tagfetcher.h',
    'src/preferences/broadcastprofile.h',
    'src/preferences/broadcastsettings.h',
    'src/preferences/broadcastsettingsmodel.h',
    'src/preferences/dialog/dlgprefmodplug.h',
    'src/preferences/dialog/dlgprefautodj.h',
    'src/preferences/dialog/dlgprefbeats.h',
    'src/preferences/dialog/dlgprefeffects.h',
    'src/preferences/dialog/dlgprefeq.h',
    'src/preferences/dialog/dlgprefdeck.h',
    'src/preferences/dialog/dlgpreferences.h',
    'src/preferences/dialog/dlgprefinterface.h',
    'src/preferences/dialog/dlgprefkey.h',
    'src/preferences/dialog/dlgpreflibrary.h',
    'src/preferences/dialog/dlgprefrecord.h',
    'src/preferences/dialog/dlgprefreplaygain.h',
    'src/preferences/dialog/dlgprefsound.h',
    'src/preferences/dialog/dlgprefsounditem.h',
    'src/preferences/dialog/dlgprefwaveform.h',
    'src/preferences/dlgpreferencepage.h',
    'src/preferences/effectsettingsmodel.h',
    'src/preferences/settingsmanager.h',
    'src/preferences/dialog/dlgprefcrossfader.h',
    'src/recording/recordingmanager.h',
    'src/skin/launchimage.h',
    'src/skin/legacyskinparser.h',
    'src/skin/tooltips.h',
    'src/soundio/sounddevicenetwork.h',
    'src/soundio/soundmanager.h',
    #'src/test/trackexport_test.h',
    'src/track/globaltrackcache.h',
    'src/track/track.h',
    'src/track/beatgrid.h',
    'src/track/beatmap.h',
    'src/util/battery/battery.h',
    'src/util/sleepableqthread.h',
    'src/util/statsmanager.h',
    'src/util/tapfilter.h',
    'src/util/task.h',
    'src/util/widgethider.h',
    'src/util/statmodel.h',
    'src/util/timer.h',
    'src/util/widgetrendertimer.h',
    'src/waveform/renderers/glslwaveformrenderersignal.h',
    'src/waveform/renderers/waveformrendermark.h',
    'src/waveform/visualplayposition.h',
    'src/waveform/vsyncthread.h',
    'src/waveform/waveformwidgetfactory.h',
    'src/waveform/widgets/emptywaveformwidget.h',
    'src/waveform/widgets/glrgbwaveformwidget.h',
    'src/waveform/widgets/glslwaveformwidget.h',
    'src/waveform/widgets/glsimplewaveformwidget.h',
    'src/waveform/widgets/glvsynctestwidget.h',
    'src/waveform/widgets/glwaveformwidget.h',
    'src/waveform/widgets/hsvwaveformwidget.h',
    'src/waveform/widgets/qtsimplewaveformwidget.h',
    'src/waveform/widgets/qtwaveformwidget.h',
    'src/waveform/widgets/rgbwaveformwidget.h',
    'src/waveform/widgets/softwarewaveformwidget.h',
    'src/waveform/guitick.h',
    'src/widget/wbattery.h',
    'src/widget/wcombobox.h',
    'src/widget/wcoverart.h',
    'src/widget/wcoverartlabel.h',
    'src/widget/wcoverartmenu.h',
    'src/widget/wdisplay.h',
    'src/widget/weffect.h',
    'src/widget/weffectbuttonparameter.h',
    'src/widget/weffectchain.h',
    'src/widget/weffectparameter.h',
    'src/widget/weffectparameterbase.h',
    'src/widget/weffectparameterknob.h',
    'src/widget/weffectparameterknobcomposed.h',
    'src/widget/weffectpushbutton.h',
    'src/widget/weffectselector.h',
    'src/widget/wkey.h',
    'src/widget/wlabel.h',
    'src/widget/wlibrary.h',
    'src/widget/wlibrarysidebar.h',
    'src/widget/wlibrarytableview.h',
    'src/widget/wlibrarytextbrowser.h',
    'src/widget/wmainmenubar.h',
    'src/widget/wnumber.h',
    'src/widget/wnumberdb.h',
    'src/widget/wnumberpos.h',
    'src/widget/woverview.h',
    'src/widget/wpushbutton.h',
    'src/widget/wrecordingduration.h',
    'src/widget/wsearchlineedit.h',
    'src/widget/wsizeawarestack.h',
    'src/widget/wsingletoncontainer.h',
    'src/widget/wspinny.h',
    'src/widget/wsplitter.h',
    'src/widget/wstarrating.h',
    'src/widget/wstatuslight.h',
    'src/widget/wtime.h',
    'src/widget/wtracktableview.h',
    'src/widget/wtracktext.h',
    'src/widget/wtrackproperty.h',
    'src/widget/wvumeter.h',
    'src/widget/wwaveformviewer.h',
    'src/widget/wwidget.h',
    'src/widget/wwidgetgroup.h',
    'src/widget/wtracktableviewheader.h',
    'src/widget/controlwidgetconnection.h',
    'src/widget/wbeatspinbox.h',
    'src/widget/wknob.h',
    'src/widget/wknobcomposed.h',
    'src/widget/wnumberrate.h',
    'src/widget/wslidercomposed.h',
    'src/widget/wwidgetstack.h',

    # QtScript Bytearray
    'lib/qtscript-bytearray/bytearrayclass.h',
    'lib/qtscript-bytearray/bytearrayprototype.h'
]

mixxx_sources =    [
    'src/control/control.cpp',
    'src/control/controlaudiotaperpot.cpp',
    'src/control/controlbehavior.cpp',
    'src/control/controleffectknob.cpp',
    'src/control/controlindicator.cpp',
    'src/control/controllinpotmeter.cpp',
    'src/control/controllogpotmeter.cpp',
    'src/control/controlmodel.cpp',
    'src/control/controlobject.cpp',
    'src/control/controlobjectscript.cpp',
    'src/control/controlpotmeter.cpp',
    'src/control/controlproxy.cpp',
    'src/control/controlpushbutton.cpp',
    'src/control/controlttrotary.cpp',
    'src/control/controlencoder.cpp',

    'src/controllers/dlgcontrollerlearning.cpp',
    'src/controllers/dlgprefcontroller.cpp',
    'src/controllers/dlgprefcontrollers.cpp',
    'src/dialog/dlgabout.cpp',
    'src/dialog/dlgdevelopertools.cpp',

    'src/preferences/configobject.cpp',
    'src/preferences/dialog/dlgprefautodj.cpp',
    'src/preferences/dialog/dlgprefdeck.cpp',
    'src/preferences/dialog/dlgprefcrossfader.cpp',
    'src/preferences/dialog/dlgprefeffects.cpp',
    'src/preferences/dialog/dlgprefeq.cpp',
    'src/preferences/dialog/dlgpreferences.cpp',
    'src/preferences/dialog/dlgprefinterface.cpp',
    'src/preferences/dialog/dlgpreflibrary.cpp',
    'src/preferences/dialog/dlgprefrecord.cpp',
    'src/preferences/dialog/dlgprefreplaygain.cpp',
    'src/preferences/dialog/dlgprefsound.cpp',
    'src/preferences/dialog/dlgprefsounditem.cpp',
    'src/preferences/dialog/dlgprefwaveform.cpp',
    'src/preferences/settingsmanager.cpp',
    'src/preferences/replaygainsettings.cpp',
    'src/preferences/broadcastsettings.cpp',
    'src/preferences/broadcastsettings_legacy.cpp',
    'src/preferences/broadcastsettingsmodel.cpp',
    'src/preferences/effectsettingsmodel.cpp',
    'src/preferences/broadcastprofile.cpp',
    'src/preferences/upgrade.cpp',
    'src/preferences/dlgpreferencepage.cpp',

    'src/effects/effectmanifest.cpp',
    'src/effects/effectmanifestparameter.cpp',

    'src/effects/effectchain.cpp',
    'src/effects/effect.cpp',
    'src/effects/effectparameter.cpp',

    'src/effects/effectrack.cpp',
    'src/effects/effectchainslot.cpp',
    'src/effects/effectslot.cpp',
    'src/effects/effectparameterslotbase.cpp',
    'src/effects/effectparameterslot.cpp',
    'src/effects/effectbuttonparameterslot.cpp',
    'src/effects/effectsmanager.cpp',
    'src/effects/effectchainmanager.cpp',
    'src/effects/effectsbackend.cpp',

    'src/effects/builtin/builtinbackend.cpp',
    'src/effects/builtin/bitcrushereffect.cpp',
    'src/effects/builtin/balanceeffect.cpp',
    'src/effects/builtin/linkwitzriley8eqeffect.cpp',
    'src/effects/builtin/bessel4lvmixeqeffect.cpp',
    'src/effects/builtin/bessel8lvmixeqeffect.cpp',
    'src/effects/builtin/threebandbiquadeqeffect.cpp',
    'src/effects/builtin/biquadfullkilleqeffect.cpp',
    'src/effects/builtin/loudnesscontoureffect.cpp',
    'src/effects/builtin/graphiceqeffect.cpp',
    'src/effects/builtin/parametriceqeffect.cpp',
    'src/effects/builtin/flangereffect.cpp',
    'src/effects/builtin/filtereffect.cpp',
    'src/effects/builtin/moogladder4filtereffect.cpp',
    'src/effects/builtin/reverbeffect.cpp',
    'src/effects/builtin/echoeffect.cpp',
    'src/effects/builtin/autopaneffect.cpp',
    'src/effects/builtin/phasereffect.cpp',
    'src/effects/builtin/metronomeeffect.cpp',
    'src/effects/builtin/tremoloeffect.cpp',

    'src/engine/effects/engineeffectsmanager.cpp',
    'src/engine/effects/engineeffectrack.cpp',
    'src/engine/effects/engineeffectchain.cpp',
    'src/engine/effects/engineeffect.cpp',

    'src/engine/sync/basesyncablelistener.cpp',
    'src/engine/sync/enginesync.cpp',
    'src/engine/sync/synccontrol.cpp',
    'src/engine/sync/internalclock.cpp',

    'src/engine/engineworker.cpp',
    'src/engine/engineworkerscheduler.cpp',
    'src/engine/enginebuffer.cpp',
    'src/engine/enginebufferscale.cpp',
    'src/engine/enginebufferscalelinear.cpp',
    'src/engine/enginefilterbiquad1.cpp',
    'src/engine/enginefiltermoogladder4.cpp',
    'src/engine/enginefilterbessel4.cpp',
    'src/engine/enginefilterbessel8.cpp',
    'src/engine/enginefilterbutterworth4.cpp',
    'src/engine/enginefilterbutterworth8.cpp',
    'src/engine/enginefilterlinkwitzriley2.cpp',
    'src/engine/enginefilterlinkwitzriley4.cpp',
    'src/engine/enginefilterlinkwitzriley8.cpp',
    'src/engine/enginefilter.cpp',
    'src/engine/engineobject.cpp',
    'src/engine/enginepregain.cpp',
    'src/engine/enginechannel.cpp',
    'src/engine/enginemaster.cpp',
    'src/engine/enginedelay.cpp',
    'src/engine/enginevumeter.cpp',
    'src/engine/enginesidechaincompressor.cpp',
    'src/engine/sidechain/enginesidechain.cpp',
    'src/engine/sidechain/networkoutputstreamworker.cpp',
    'src/engine/sidechain/networkinputstreamworker.cpp',
    'src/engine/enginexfader.cpp',
    'src/engine/enginemicrophone.cpp',
    'src/engine/enginedeck.cpp',
    'src/engine/engineaux.cpp',
    'src/engine/channelmixer_autogen.cpp',

    'src/engine/enginecontrol.cpp',
    'src/engine/ratecontrol.cpp',
    'src/engine/positionscratchcontroller.cpp',
    'src/engine/loopingcontrol.cpp',
    'src/engine/bpmcontrol.cpp',
    'src/engine/keycontrol.cpp',
    'src/engine/cuecontrol.cpp',
    'src/engine/quantizecontrol.cpp',
    'src/engine/clockcontrol.cpp',
    'src/engine/readaheadmanager.cpp',
    'src/engine/enginetalkoverducking.cpp',
    'src/engine/cachingreader.cpp',
    'src/engine/cachingreaderchunk.cpp',
    'src/engine/cachingreaderworker.cpp',

    'src/analyzer/analyzerqueue.cpp',
    'src/analyzer/analyzerwaveform.cpp',
    'src/analyzer/analyzergain.cpp',
    'src/analyzer/analyzerebur128.cpp',

    'src/controllers/controller.cpp',
    'src/controllers/controllerdebug.cpp',
    'src/controllers/controllerengine.cpp',
    'src/controllers/controllerenumerator.cpp',
    'src/controllers/controllerlearningeventfilter.cpp',
    'src/controllers/controllermanager.cpp',
    'src/controllers/controllerpresetfilehandler.cpp',
    'src/controllers/controllerpresetinfo.cpp',
    'src/controllers/controllerpresetinfoenumerator.cpp',
    'src/controllers/controlpickermenu.cpp',
    'src/controllers/controllermappingtablemodel.cpp',
    'src/controllers/controllerinputmappingtablemodel.cpp',
    'src/controllers/controlleroutputmappingtablemodel.cpp',
    'src/controllers/delegates/controldelegate.cpp',
    'src/controllers/delegates/midichanneldelegate.cpp',
    'src/controllers/delegates/midiopcodedelegate.cpp',
    'src/controllers/delegates/midibytedelegate.cpp',
    'src/controllers/delegates/midioptionsdelegate.cpp',
    'src/controllers/learningutils.cpp',
    'src/controllers/midi/midimessage.cpp',
    'src/controllers/midi/midiutils.cpp',
    'src/controllers/midi/midicontroller.cpp',
    'src/controllers/midi/midicontrollerpresetfilehandler.cpp',
    'src/controllers/midi/midienumerator.cpp',
    'src/controllers/midi/midioutputhandler.cpp',
    'src/controllers/softtakeover.cpp',
    'src/controllers/keyboard/keyboardeventfilter.cpp',

    'src/mixxx.cpp',
    'src/mixxxapplication.cpp',
    'src/errordialoghandler.cpp',

    'src/sources/audiosource.cpp',
    'src/sources/audiosourcestereoproxy.cpp',
    'src/sources/metadatasourcetaglib.cpp',
    'src/sources/soundsource.cpp',
    'src/sources/soundsourceproviderregistry.cpp',
    'src/sources/soundsourceproxy.cpp',

    'src/widget/controlwidgetconnection.cpp',
    'src/widget/wbasewidget.cpp',
    'src/widget/wwidget.cpp',
    'src/widget/wwidgetgroup.cpp',
    'src/widget/wwidgetstack.cpp',
    'src/widget/wsizeawarestack.cpp',
    'src/widget/wlabel.cpp',
    'src/widget/wtracktext.cpp',
    'src/widget/wnumber.cpp',
    'src/widget/wbeatspinbox.cpp',
    'src/widget/wnumberdb.cpp',
    'src/widget/wnumberpos.cpp',
    'src/widget/wnumberrate.cpp',
    'src/widget/wknob.cpp',
    'src/widget/wknobcomposed.cpp',
    'src/widget/wdisplay.cpp',
    'src/widget/wvumeter.cpp',
    'src/widget/wpushbutton.cpp',
    'src/widget/weffectpushbutton.cpp',
    'src/widget/wslidercomposed.cpp',
    'src/widget/wstatuslight.cpp',
    'src/widget/woverview.cpp',
    'src/widget/woverviewlmh.cpp',
    'src/widget/woverviewhsv.cpp',
    'src/widget/woverviewrgb.cpp',
    'src/widget/wspinny.cpp',
    'src/widget/wskincolor.cpp',
    'src/widget/wsearchlineedit.cpp',
    'src/widget/wpixmapstore.cpp',
    'src/widget/paintable.cpp',
    'src/widget/wimagestore.cpp',
    'src/widget/hexspinbox.cpp',
    'src/widget/wtrackproperty.cpp',
    'src/widget/wstarrating.cpp',
    'src/widget/weffectchain.cpp',
    'src/widget/weffect.cpp',
    'src/widget/weffectselector.cpp',
    'src/widget/weffectparameter.cpp',
    'src/widget/weffectparameterknob.cpp',
    'src/widget/weffectparameterknobcomposed.cpp',
    'src/widget/weffectbuttonparameter.cpp',
    'src/widget/weffectparameterbase.cpp',
    'src/widget/wtime.cpp',
    'src/widget/wrecordingduration.cpp',
    'src/widget/wkey.cpp',
    'src/widget/wbattery.cpp',
    'src/widget/wcombobox.cpp',
    'src/widget/wsplitter.cpp',
    'src/widget/wcoverart.cpp',
    'src/widget/wcoverartlabel.cpp',
    'src/widget/wcoverartmenu.cpp',
    'src/widget/wsingletoncontainer.cpp',
    'src/widget/wmainmenubar.cpp',

    'src/musicbrainz/network.cpp',
    'src/musicbrainz/tagfetcher.cpp',
    'src/musicbrainz/gzip.cpp',
    'src/musicbrainz/crc.c',
    'src/musicbrainz/acoustidclient.cpp',
    'src/musicbrainz/chromaprinter.cpp',
    'src/musicbrainz/musicbrainzclient.cpp',

    'src/widget/wtracktableview.cpp',
    'src/widget/wtracktableviewheader.cpp',
    'src/widget/wlibrarysidebar.cpp',
    'src/widget/wlibrary.cpp',
    'src/widget/wlibrarytableview.cpp',
    'src/widget/wanalysislibrarytableview.cpp',
    'src/widget/wlibrarytextbrowser.cpp',

    'src/database/mixxxdb.cpp',
    'src/database/schemamanager.cpp',

    'src/library/trackcollection.cpp',
    'src/library/basesqltablemodel.cpp',
    'src/library/basetrackcache.cpp',
    'src/library/columncache.cpp',
    'src/library/librarytablemodel.cpp',
    'src/library/searchquery.cpp',
    'src/library/searchqueryparser.cpp',
    'src/library/analysislibrarytablemodel.cpp',
    'src/library/missingtablemodel.cpp',
    'src/library/hiddentablemodel.cpp',
    'src/library/proxytrackmodel.cpp',
    'src/library/coverart.cpp',
    'src/library/coverartcache.cpp',
    'src/library/coverartutils.cpp',

    'src/library/crate/cratestorage.cpp',
    'src/library/crate/cratefeature.cpp',
    'src/library/crate/cratefeaturehelper.cpp',
    'src/library/crate/cratetablemodel.cpp',

    'src/library/playlisttablemodel.cpp',
    'src/library/libraryfeature.cpp',
    'src/library/analysisfeature.cpp',
    'src/library/autodj/autodjfeature.cpp',
    'src/library/autodj/autodjprocessor.cpp',
    'src/library/dao/directorydao.cpp',
    'src/library/mixxxlibraryfeature.cpp',
    'src/library/baseplaylistfeature.cpp',
    'src/library/playlistfeature.cpp',
    'src/library/setlogfeature.cpp',
    'src/library/autodj/dlgautodj.cpp',
    'src/library/dlganalysis.cpp',
    'src/library/dlgcoverartfullsize.cpp',
    'src/library/dlghidden.cpp',
    'src/library/dlgmissing.cpp',
    'src/library/dlgtagfetcher.cpp',
    'src/library/dlgtrackinfo.cpp',
    'src/library/dlgtrackmetadataexport.cpp',

    'src/library/browse/browsetablemodel.cpp',
    'src/library/browse/browsethread.cpp',
    'src/library/browse/browsefeature.cpp',
    'src/library/browse/foldertreemodel.cpp',

    'src/library/export/trackexportdlg.cpp',
    'src/library/export/trackexportwizard.cpp',
    'src/library/export/trackexportworker.cpp',

    'src/library/recording/recordingfeature.cpp',
    'src/library/recording/dlgrecording.cpp',
    'src/recording/recordingmanager.cpp',
    'src/engine/sidechain/enginerecord.cpp',

    # External Library Features
    'src/library/baseexternallibraryfeature.cpp',
    'src/library/baseexternaltrackmodel.cpp',
    'src/library/baseexternalplaylistmodel.cpp',
    'src/library/rhythmbox/rhythmboxfeature.cpp',

    'src/library/banshee/bansheefeature.cpp',
    'src/library/banshee/bansheeplaylistmodel.cpp',
    'src/library/banshee/bansheedbconnection.cpp',

    'src/library/itunes/itunesfeature.cpp',
    'src/library/traktor/traktorfeature.cpp',

    'src/library/sidebarmodel.cpp',
    'src/library/library.cpp',

    'src/library/scanner/libraryscanner.cpp',
    'src/library/scanner/libraryscannerdlg.cpp',
    'src/library/scanner/scannertask.cpp',
    'src/library/scanner/importfilestask.cpp',
    'src/library/scanner/recursivescandirectorytask.cpp',

    'src/library/dao/cuedao.cpp',
    'src/library/dao/cue.cpp',
    'src/library/dao/trackdao.cpp',
    'src/library/dao/playlistdao.cpp',
    'src/library/dao/libraryhashdao.cpp',
    'src/library/dao/settingsdao.cpp',
    'src/library/dao/analysisdao.cpp',
    'src/library/dao/autodjcratesdao.cpp',

    'src/library/librarycontrol.cpp',
    'src/library/songdownloader.cpp',
    'src/library/starrating.cpp',
    'src/library/stardelegate.cpp',
    'src/library/stareditor.cpp',
    'src/library/bpmdelegate.cpp',
    'src/library/previewbuttondelegate.cpp',
    'src/library/coverartdelegate.cpp',
    'src/library/tableitemdelegate.cpp',

    'src/library/treeitemmodel.cpp',
    'src/library/treeitem.cpp',

    'src/library/parser.cpp',
    'src/library/parserpls.cpp',
    'src/library/parserm3u.cpp',
    'src/library/parsercsv.cpp',

    'src/widget/wwaveformviewer.cpp',

    'src/waveform/sharedglcontext.cpp',
    'src/waveform/waveform.cpp',
    'src/waveform/waveformfactory.cpp',
    'src/waveform/waveformwidgetfactory.cpp',
    'src/waveform/vsyncthread.cpp',
    'src/waveform/guitick.cpp',
    'src/waveform/visualplayposition.cpp',
    'src/waveform/renderers/waveformwidgetrenderer.cpp',
    'src/waveform/renderers/waveformrendererabstract.cpp',
    'src/waveform/renderers/waveformrenderbackground.cpp',
    'src/waveform/renderers/waveformrendermark.cpp',
    'src/waveform/renderers/waveformrendermarkrange.cpp',
    'src/waveform/renderers/waveformrenderbeat.cpp',
    'src/waveform/renderers/waveformrendererendoftrack.cpp',
    'src/waveform/renderers/waveformrendererpreroll.cpp',

    'src/waveform/renderers/waveformrendererfilteredsignal.cpp',
    'src/waveform/renderers/waveformrendererhsv.cpp',
    'src/waveform/renderers/waveformrendererrgb.cpp',
    'src/waveform/renderers/qtwaveformrendererfilteredsignal.cpp',
    'src/waveform/renderers/qtwaveformrenderersimplesignal.cpp',

    'src/waveform/renderers/waveformsignalcolors.cpp',

    'src/waveform/renderers/waveformrenderersignalbase.cpp',
    'src/waveform/renderers/waveformmark.cpp',
    'src/waveform/renderers/waveformmarkproperties.cpp',
    'src/waveform/renderers/waveformmarkset.cpp',
    'src/waveform/renderers/waveformmarkrange.cpp',
    'src/waveform/renderers/glwaveformrenderersimplesignal.cpp',
    'src/waveform/renderers/glwaveformrendererrgb.cpp',
    'src/waveform/renderers/glwaveformrendererfilteredsignal.cpp',
    'src/waveform/renderers/glslwaveformrenderersignal.cpp',
    'src/waveform/renderers/glvsynctestrenderer.cpp',

    'src/waveform/widgets/waveformwidgetabstract.cpp',
    'src/waveform/widgets/emptywaveformwidget.cpp',
    'src/waveform/widgets/softwarewaveformwidget.cpp',
    'src/waveform/widgets/hsvwaveformwidget.cpp',
    'src/waveform/widgets/rgbwaveformwidget.cpp',
    'src/waveform/widgets/qtwaveformwidget.cpp',
    'src/waveform/widgets/qtsimplewaveformwidget.cpp',
    'src/waveform/widgets/glwaveformwidget.cpp',
    'src/waveform/widgets/glsimplewaveformwidget.cpp',
    'src/waveform/widgets/glvsynctestwidget.cpp',

    'src/waveform/widgets/glslwaveformwidget.cpp',

    'src/waveform/widgets/glrgbwaveformwidget.cpp',

    'src/skin/imginvert.cpp',
    'src/skin/imgloader.cpp',
    'src/skin/imgcolor.cpp',
    'src/skin/skinloader.cpp',
    'src/skin/legacyskinparser.cpp',
    'src/skin/colorschemeparser.cpp',
    'src/skin/tooltips.cpp',
    'src/skin/skincontext.cpp',
    'src/skin/svgparser.cpp',
    'src/skin/pixmapsource.cpp',
    'src/skin/launchimage.cpp',

    'src/track/beatfactory.cpp',
    'src/track/beatgrid.cpp',
    'src/track/beatmap.cpp',
    'src/track/beatutils.cpp',
    'src/track/beats.cpp',
    'src/track/bpm.cpp',
    'src/track/keyfactory.cpp',
    'src/track/keys.cpp',
    'src/track/keyutils.cpp',
    'src/track/playcounter.cpp',
    'src/track/replaygain.cpp',
    'src/track/track.cpp',
    'src/track/globaltrackcache.cpp',
    'src/track/trackmetadata.cpp',
    'src/track/trackmetadatataglib.cpp',
    'src/track/tracknumbers.cpp',
    'src/track/albuminfo.cpp',
    'src/track/trackinfo.cpp',
    'src/track/trackrecord.cpp',
    'src/track/trackref.cpp',

    'src/mixer/auxiliary.cpp',
    'src/mixer/baseplayer.cpp',
    'src/mixer/basetrackplayer.cpp',
    'src/mixer/deck.cpp',
    'src/mixer/microphone.cpp',
    'src/mixer/playerinfo.cpp',
    'src/mixer/playermanager.cpp',
    'src/mixer/previewdeck.cpp',
    'src/mixer/sampler.cpp',
    'src/mixer/samplerbank.cpp',

    'src/soundio/sounddevice.cpp',
    'src/soundio/sounddevicenetwork.cpp',
    'src/engine/sidechain/enginenetworkstream.cpp',
    'src/soundio/soundmanager.cpp',
    'src/soundio/soundmanagerconfig.cpp',
    'src/soundio/soundmanagerutil.cpp',

    'src/encoder/encoder.cpp',
    'src/encoder/encodermp3.cpp',
    'src/encoder/encodervorbis.cpp',
    'src/encoder/encoderwave.cpp',
    'src/encoder/encodersndfileflac.cpp',
    'src/encoder/encodermp3settings.cpp',
    'src/encoder/encodervorbissettings.cpp',
    'src/encoder/encoderwavesettings.cpp',
    'src/encoder/encoderflacsettings.cpp',
    'src/encoder/encoderbroadcastsettings.cpp',

    'src/util/sleepableqthread.cpp',
    'src/util/statsmanager.cpp',
    'src/util/stat.cpp',
    'src/util/statmodel.cpp',
    'src/util/duration.cpp',
    'src/util/time.cpp',
    'src/util/timer.cpp',
    'src/util/performancetimer.cpp',
    'src/util/threadcputimer.cpp',
    'src/util/version.cpp',
    'src/util/rlimit.cpp',
    'src/util/battery/battery.cpp',
    'src/util/valuetransformer.cpp',
    'src/util/sandbox.cpp',
    'src/util/file.cpp',
    'src/util/mac.cpp',
    'src/util/task.cpp',
    'src/util/experiment.cpp',
    'src/util/xml.cpp',
    'src/util/tapfilter.cpp',
    'src/util/movinginterquartilemean.cpp',
    'src/util/console.cpp',
    'src/util/db/dbconnection.cpp',
    'src/util/db/dbconnectionpool.cpp',
    'src/util/db/dbconnectionpooler.cpp',
    'src/util/db/dbconnectionpooled.cpp',
    'src/util/db/dbid.cpp',
    'src/util/db/fwdsqlquery.cpp',
    'src/util/db/fwdsqlqueryselectresult.cpp',
    'src/util/db/sqllikewildcardescaper.cpp',
    'src/util/db/sqlqueryfinisher.cpp',
    'src/util/db/sqlstringformatter.cpp',
    'src/util/db/sqltransaction.cpp',
    'src/util/sample.cpp',
    'src/util/samplebuffer.cpp',
    'src/util/readaheadsamplebuffer.cpp',
    'src/util/rotary.cpp',
    'src/util/logger.cpp',
    'src/util/logging.cpp',
    'src/util/cmdlineargs.cpp',
    'src/util/audiosignal.cpp',
    'src/util/widgethider.cpp',
    'src/util/autohidpi.cpp',
    'src/util/screensaver.cpp',
    'src/util/indexrange.cpp',
    'src/util/desktophelper.cpp',
    'src/util/widgetrendertimer.cpp',

    #portmidi
    'src/controllers/midi/portmidienumerator.cpp',
    'src/controllers/midi/portmidicontroller.cpp',

    #portaudio
    'src/soundio/sounddeviceportaudio.cpp',

    #soundtouch
    'src/engine/enginebufferscalest.cpp',

    #ruberband
    'src/engine/enginebufferscalerubberband.cpp',

    #flac
    'src/sources/soundsourceflac.cpp',

    #ogg
    'src/sources/soundsourceoggvorbis.cpp',

    #sndfile
    'src/sources/soundsourcesndfile.cpp',

    ## LIBS
    'lib/fidlib/fidlib.c',
    'lib/replaygain/replaygain.cpp',
    'lib/reverb/Reverb.cc',
    'lib/portaudio/pa_ringbuffer.c',
    'lib/qtscript-bytearray/bytearrayclass.cpp',
    'lib/qtscript-bytearray/bytearrayprototype.cpp'
]

mixxx_ui =         [
    'src/controllers/dlgcontrollerlearning.ui',
    'src/controllers/dlgprefcontrollerdlg.ui',
    'src/controllers/dlgprefcontrollersdlg.ui',
    'src/dialog/dlgaboutdlg.ui',
    'src/dialog/dlgdevelopertoolsdlg.ui',
    'src/library/autodj/dlgautodj.ui',
    'src/library/dlganalysis.ui',
    'src/library/dlgcoverartfullsize.ui',
    'src/library/dlghidden.ui',
    'src/library/dlgmissing.ui',
    'src/library/dlgtagfetcher.ui',
    'src/library/dlgtrackinfo.ui',
    'src/library/export/dlgtrackexport.ui',
    'src/library/recording/dlgrecording.ui',
    'src/preferences/dialog/dlgprefautodjdlg.ui',
    'src/preferences/dialog/dlgprefbeatsdlg.ui',
    'src/preferences/dialog/dlgprefcrossfaderdlg.ui',
    'src/preferences/dialog/dlgprefdeckdlg.ui',
    'src/preferences/dialog/dlgprefeqdlg.ui',
    'src/preferences/dialog/dlgpreferencesdlg.ui',
    'src/preferences/dialog/dlgprefinterfacedlg.ui',
    'src/preferences/dialog/dlgprefkeydlg.ui',
    'src/preferences/dialog/dlgpreflibrarydlg.ui',
    'src/preferences/dialog/dlgprefrecorddlg.ui',
    'src/preferences/dialog/dlgprefreplaygaindlg.ui',
    'src/preferences/dialog/dlgprefsounddlg.ui',
    'src/preferences/dialog/dlgprefsounditem.ui',
    'src/preferences/dialog/dlgprefeffectsdlg.ui',
    'src/preferences/dialog/dlgprefwaveformdlg.ui'
]

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

### not on linux
if get_option('hss1394').enabled()
    add_project_arguments('-D__HSS1394__', language: 'cpp')
    mixxx_sources += [
        'src/controllers/midi/hss1394controller.h',
        'src/controllers/midi/hss1394enumerator.h'
    ]
    # @TODO: will this work?
    dependencies += dependency('hss1394')
endif

if get_option('hid').enabled()
    add_project_arguments('-D__HID__', language: 'cpp')

    # @TODO: fallback to internal
    dependencies += dependency('hidapi-libusb')
    dependencies += dependency('libusb-1.0')
    mixxx_headers += 'src/controllers/hid/hidcontroller.h'
    mixxx_sources += [
        'src/controllers/hid/hidcontroller.cpp',
        'src/controllers/hid/hidenumerator.cpp',
        'src/controllers/hid/hidcontrollerpresetfilehandler.cpp'
    ]
endif

if get_option('bulk').enabled()
    add_project_arguments('-D__BULK__', language: 'cpp')

    # @TODO: already in hid...
    dependencies += dependency('libusb-1.0')
    mixxx_headers += 'src/controllers/bulk/bulkcontroller.h'
    mixxx_sources += [
        'src/controllers/bulk/bulkcontroller.cpp',
        'src/controllers/bulk/bulkenumerator.cpp'
    ]
    if get_option('hid').enabled()
        mixxx_sources += 'src/controllers/hid/hidcontrollerpresetfilehandler.cpp'
    endif
endif

if get_option('mad').enabled()
    add_project_arguments('-D__MAD__', language: 'cpp')

    dependencies += [ dependency('mad'), dependency('id3tag') ]
    mixxx_sources += [
        'src/sources/soundsourcemp3.cpp'
    ]
endif

#@TODO
if get_option('coreaudio').enabled()
    if host_machine.system() != 'darwin'
        error('Coreaudio is available only on Darwin platform')
    endif

    add_project_arguments('-D__COREAUDIO__', language: 'cpp')

    mixxx_sources += [
        'src/sources/soundsourcecoreaudio.cpp',
        'src/sources/v1/legacyaudiosourceadapter.cpp'
    ]
    #lib/apple/CAStreamBasicDescription.cpp
endif

if get_option('vinylcontrol').enabled()

    add_project_arguments('-D__VINYLCONTROL__', language: 'cpp')

    includes += [
        'lib/xwax',
        'src'
    ]

    mixxx_ui += 'src/preferences/dialog/dlgprefvinyldlg.ui'

    mixxx_headers += [
        'src/preferences/dialog/dlgprefvinyl.h',
        'src/engine/vinylcontrolcontrol.h',
        'src/vinylcontrol/vinylcontrolmanager.h',
        'src/vinylcontrol/vinylcontrolsignalwidget.h',
        'src/vinylcontrol/vinylcontrolprocessor.h',
    ]

    mixxx_sources += [
        'src/vinylcontrol/steadypitch.cpp',
        'src/engine/vinylcontrolcontrol.cpp',
        'src/vinylcontrol/vinylcontrol.cpp',
        'src/vinylcontrol/vinylcontrolmanager.cpp',
        'src/vinylcontrol/vinylcontrolprocessor.cpp',
        'src/vinylcontrol/vinylcontrolsignalwidget.cpp',
        'src/vinylcontrol/vinylcontrolxwax.cpp',
        'src/preferences/dialog/dlgprefvinyl.cpp',
    ]

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
else
    mixxx_ui += 'src/preferences/dialog/dlgprefnovinyldlg.ui'
    mixxx_sources += 'src/preferences/dialog/dlgprefnovinyl.cpp'
    mixxx_headers += 'src/preferences/dialog/dlgprefnovinyl.h'
endif

if get_option('vamp').enabled()
    add_project_arguments('-D__VAMP__', language: 'cpp')

    dependencies += [
        dependency('vamp-hostsdk'),
        dependency('fftw3'), # really? i guess it is necessary only when we self build vamp
        meson.get_compiler('cpp').find_library('dl')
    ]

    ### seems it is not used anywhere
    #add_project_arguments('-DHAVE_FFTW3', language: 'cpp')

    mixxx_sources += [
        'src/analyzer/vamp/vampanalyzer.cpp',
        'src/analyzer/vamp/vamppluginadapter.cpp',
        'src/analyzer/analyzerbeats.cpp',
        'src/analyzer/analyzerkey.cpp',
        'src/preferences/dialog/dlgprefbeats.cpp',
        'src/preferences/dialog/dlgprefkey.cpp'
    ]
endif

if get_option('modplug').enabled()
    add_project_arguments('-D__MODPLUG__', language: 'cpp')
    dependencies += [
        dependency('modplug')
    ]

    mixxx_sources += [
        'src/sources/soundsourcemodplug.cpp',
        'src/preferences/dialog/dlgprefmodplug.cpp'
    ]

    mixxx_ui += [
        'src/preferences/dialog/dlgprefmodplugdlg.ui'
    ]
endif

if get_option('faad').enabled()
    add_project_arguments('-D__FAAD__', language: 'cpp')
    add_project_arguments('-D__MP4V2__', language: 'cpp')
    dependencies += [
        meson.get_compiler('cpp').find_library('faad'),
        meson.get_compiler('cpp').find_library('libmp4v2'),
    ]

    mixxx_sources += [
        'src/sources/soundsourcem4a.cpp',
    ]

endif

if get_option('wv').enabled()
    add_project_arguments('-D__WV__', language: 'cpp')
    dependencies += [
        dependency('wavpack')
    ]

    mixxx_sources += [
        'src/sources/soundsourcewv.cpp',
    ]

endif

if get_option('opus').enabled()
    add_project_arguments('-D__OPUS__', language: 'cpp')
    dependencies += [
        dependency('opusfile')
    ]

    mixxx_sources += [
        'src/sources/soundsourceopus.cpp',
    ]

endif

if get_option('battery').enabled()
    add_project_arguments('-D__BATTERY__', language: 'cpp')


    if host_machine.system() == 'windows'
        mixxx_sources += 'src/util/battery/batterywindows.cpp'

    elif host_machine.system() == 'linux'
        mixxx_sources += 'src/util/battery/batterylinux.cpp'
        dependencies += dependency('upower-glib')

    elif host_machine.system() == 'darwin'
        mixxx_sources += 'src/util/battery/batterymac.cpp'
        dependencies += dependency('appleframeworks', modules: 'IOKit')

    endif

endif

if get_option('lilv').enabled()
    add_project_arguments('-D__LILV__', language: 'cpp')
    dependencies += [
        dependency('lilv-0')
    ]

    mixxx_headers += 'src/preferences/dialog/dlgpreflv2.h'

    mixxx_ui += 'src/preferences/dialog/dlgpreflv2dlg.ui'

    mixxx_sources += [
        'src/effects/lv2/lv2backend.cpp',
        'src/effects/lv2/lv2effectprocessor.cpp',
        'src/effects/lv2/lv2manifest.cpp',
        'src/preferences/dialog/dlgpreflv2.cpp'
    ]

endif

if get_option('broadcast').enabled()
    add_project_arguments('-D__BROADCAST__', language: 'cpp')
    dependencies += [
        dependency('shout')
    ]

    mixxx_ui += 'src/preferences/dialog/dlgprefbroadcastdlg.ui'

    mixxx_headers += [
        'src/broadcast/broadcastmanager.h',
        'src/engine/sidechain/shoutconnection.h',
        'src/preferences/dialog/dlgprefbroadcast.h',
    ]

    mixxx_sources += [
        'src/preferences/dialog/dlgprefbroadcast.cpp',
        'src/broadcast/broadcastmanager.cpp',
        'src/engine/sidechain/shoutconnection.cpp'
    ]

endif

if get_option('localecompare').enabled()
    if get_option('qt_sqlite_plugin').enabled()
        error('Options localecompare and qt_sqlite_plugin are incompatible')
    endif
    add_project_arguments('-D__SQLITE3__', language: 'cpp')
    dependencies += [
        dependency('sqlite3')
    ]
endif

#if get_option('qt_sqlite_plugin').enabled()
    #qt5modules += 'Sql'
#endif

#if meson.get_compiler('cpp').get_define('-ffast-math')
    mixxx_sources += 'src/util/fpclassify.cpp'
#endif

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
    add_project_arguments(['-ffast-math', '-funroll-loops'], language: 'cpp')
endif

add_project_arguments(
    '-DSETTINGS_PATH=".mixxx"',
    '-DSETTINGS_FILE="mixxx.cfg"',
    #'-D__SNDFILE__',
    #'-DSFC_SUPPORTS_SET_COMPRESSION_LEVEL',
    #'-Dkiss_fft_scalar=double',
    language: 'cpp')

add_project_arguments(
    # fidlib... but making it proper subproject is good idea I think
    '-DT_LINUX',
    language: 'c'
)

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

prep = qt5.preprocess(
    moc_headers : mixxx_headers,
    ui_files : mixxx_ui,
    include_directories: include_directories(includes)
)

qrc = qt5.preprocess(
    qresources: 'res/mixxx.qrc'
)

libmixxx = static_library(
    'mixxx',
    sources : [mixxx_sources, prep, protos ],
    dependencies : [qt5dep, dependencies ],
    include_directories: include_directories(includes),
    install : false
)

mixxx = executable(
    'mixxx',
    dependencies : [dependency('gl'), qt5dep],
    sources : ['src/main.cpp', qrc, protos],
    include_directories: include_directories(includes),
    link_with : [ libmixxx],
    install : true
)

install_subdir('res/controllers',  install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/skins',        install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/fonts',        install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/keyboard',     install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)
install_subdir('res/translations', install_dir : join_paths(get_option('datadir'),meson.project_name()), strip_directory : false)

