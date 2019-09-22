mixxx_sources += files([ 
    'dlgprefautodj.cpp',
    'dlgprefbeats.cpp',
    'dlgprefcrossfader.cpp',
    'dlgprefdeck.cpp',
    'dlgprefeffects.cpp',
    'dlgprefeq.cpp',
    'dlgpreferences.cpp',
    'dlgprefinterface.cpp',
    'dlgprefkey.cpp',
    'dlgpreflibrary.cpp',
    'dlgprefrecord.cpp',
    'dlgprefreplaygain.cpp',
    'dlgprefsound.cpp',
    'dlgprefsounditem.cpp',
    'dlgprefwaveform.cpp',
])

mixxx_headers += files([ 
    'dlgprefautodj.h',
    'dlgprefbeats.h',
    'dlgprefcrossfader.h',
    'dlgprefdeck.h',
    'dlgprefeffects.h',
    'dlgprefeq.h',
    'dlgpreferences.h',
    'dlgprefinterface.h',
    'dlgprefkey.h',
    'dlgpreflibrary.h',
    'dlgprefrecord.h',
    'dlgprefreplaygain.h',
    'dlgprefsound.h',
    'dlgprefsounditem.h',
    'dlgprefwaveform.h',
])

mixxx_ui += files([ 
    'dlgprefautodjdlg.ui',
    'dlgprefbeatsdlg.ui',
    'dlgprefcrossfaderdlg.ui',
    'dlgprefdeckdlg.ui',
    'dlgprefeffectsdlg.ui',
    'dlgprefeqdlg.ui',
    'dlgpreferencesdlg.ui',
    'dlgprefinterfacedlg.ui',
    'dlgprefkeydlg.ui',
    'dlgpreflibrarydlg.ui',
    'dlgprefrecorddlg.ui',
    'dlgprefreplaygaindlg.ui',
    'dlgprefsounddlg.ui',
    'dlgprefsounditem.ui',
    'dlgprefwaveformdlg.ui',
])

if has_broadcast
  mixxx_headers += files('dlgprefbroadcast.h')
  mixxx_sources += files('dlgprefbroadcast.cpp')
  mixxx_ui += files('dlgprefbroadcastdlg.ui')
endif

if has_lilv
  mixxx_headers += files('dlgpreflv2.h')
  mixxx_sources += files('dlgpreflv2.cpp')
  mixxx_ui += files('dlgpreflv2dlg.ui')
endif

if has_modplug
  mixxx_headers += files('dlgprefmodplug.h')
  mixxx_sources += files('dlgprefmodplug.cpp')
  mixxx_ui += files('dlgprefmodplugdlg.ui')
endif

if has_vinylcontrol
  mixxx_headers += files('dlgprefvinyl.h')
  mixxx_sources += files('dlgprefvinyl.cpp')
  mixxx_ui += files('dlgprefvinyldlg.ui')
else
  mixxx_headers += files('dlgprefnovinyl.h')
  mixxx_sources += files('dlgprefnovinyl.cpp')
  mixxx_ui += files('dlgprefnovinyldlg.ui')
endif
