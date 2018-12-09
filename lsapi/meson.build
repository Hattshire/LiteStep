lsapi_res = winresc.compile_resources('lsapi.rc')

lsapi = library('lsapi',
 'aboutbox.cpp',           'BangCommand.cpp',
 'BangManager.cpp',        'bangs.cpp',
 'graphics.cpp',           'lsapi.cpp',
 'lsapiInit.cpp',          'match.cpp',
 'MathEvaluate.cpp',       'MathParser.cpp',
 'MathScanner.cpp',        'MathToken.cpp',
 'MathValue.cpp',          'picopng.cpp',
 'png_support.cpp',        'settings.cpp',
 'SettingsFileParser.cpp', 'SettingsIterator.cpp',
 'settingsmanager.cpp',    'stubs.cpp',
 lsapi_res,
 
 cpp_args : [
	'-DLSAPI_PRIVATE',
	'-DLSAPI_INTERNAL'
	],

 name_prefix : '',

 link_with : utility,
 link_args : [
	'-ladvapi32', '-lgdi32', '-lkernel32',
	'-lmsvcrt',   '-lole32', '-lshell32',
	'-lshlwapi',  '-luser32'
	]
 )