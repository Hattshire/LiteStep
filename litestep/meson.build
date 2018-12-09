exe_res = winresc.compile_resources('litestep.rc')

executable('litestep',
 'COMFactory.cpp',         'COMService.cpp',
 'DataStore.cpp',          'DDEService.cpp',
 'DDEStub.cpp',            'DDEWorker.cpp',
 'DesktopWallpaper.cpp',   'ExplorerService.cpp',
 'FullscreenMonitor.cpp',  'litestep.cpp',
 'MessageManager.cpp',     'Module.cpp',
 'ModuleManager.cpp',      'RecoveryMenu.cpp',
 'ShellDesktopTray.cpp',   'StartupRunner.cpp',
 'TaskbarListHandler.cpp', 'TrayNotifyIcon.cpp',
 'TrayService.cpp',        'Utility.cpp',
 'WinMain.cpp',
 exe_res,
 
 cpp_args : ['-DLSAPI_PRIVATE'],
 
 link_with : [ utility, lsapi ],
 link_args : [
	'-ladvapi32',     '-lkernel32',     '-lmsvcp60',
	'-lmsvcrt',       '-lole32',        '-lshlwapi',
	'-lshell32',      '-luser32',       '-luuid',
	'-luserenv',      '-municode'      
	]
)