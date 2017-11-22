Import('rtconfig')
from building import *

cwd = GetCurrentDir()
src = []

CPPPATH = [cwd]

if GetDepend('BOARD_X1000_REALBOARD'):
    LIBPATH = [cwd + '/mips/x1000']
    if GetDepend('RT_USING_HARD_FLOAT'):
        LIBS = ['libPersimmon_hard_gcc']
    else:
        LIBS = ['libPersimmon_soft_gcc']
elif GetDepend('SOC_LPC54608'):
    LIBPATH = [cwd + '/arm/lpc54608']
    if rtconfig.CROSS_TOOL == 'gcc':
        LIBS = ['libPersimmon_gcc.a']
    elif rtconfig.CROSS_TOOL == 'keil':
        LIBS = ['Persimmon_rvds.lib']
    else :
        LIBS = []
else :
    LIBPATH = []
    LIBS = []

group = DefineGroup('Persimmon', src, depend = ['PKG_USING_PERSIMMON'], LIBS = LIBS, LIBPATH = LIBPATH, CPPPATH = CPPPATH)

Return('group')
