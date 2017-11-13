Import('rtconfig')
from building import *

cwd = GetCurrentDir()
src = []

if not GetDepend('MIPS_HARD_FLOAT'):
    LIBS = Split[
        'libPersimmon_soft_gcc'
        ]
else:
    LIBS = Split[
        'libPersimmon_hard_gcc'
        ]

CPPPATH = [cwd + '/include']
LIBPATH = [cwd + '/' + rtconfig.ARCH + '/' + rtconfig.CPU]

group = DefineGroup('Persimmon', src, depend = ['RT_USING_PERSIMMON'], LIBS = LIBS, LIBPATH = LIBPATH, CPPPATH = CPPPATH)

Return('group')
