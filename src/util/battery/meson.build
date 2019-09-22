if has_battery
  mixxx_sources += files('battery.cpp')

  mixxx_headers += files( 'battery.h')

  if host_machine.system() == 'windows'
    mixxx_sources += files('batterywindows.cpp')

  elif host_machine.system() == 'linux'
    mixxx_sources += files('batterylinux.cpp')

  elif host_machine.system() == 'darwin'
    mixxx_sources += files('batterymac.cpp')

  endif
endif
