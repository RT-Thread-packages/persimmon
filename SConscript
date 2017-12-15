Import('rtconfig')
from building import *

cwd = GetCurrentDir()
src = []

CPPPATH = [cwd]

if GetDepend('BOARD_X1000_REALBOARD'):
    LIBPATH = [cwd + '/mips/x1000']
    if GetDepend('RT_USING_HARD_FLOAT'):
        LIBS = ['Persimmon_hard_gcc']
    else:
        LIBS = ['Persimmon_soft_gcc']
elif GetDepend('SOC_LPC54608'):
    LIBPATH = [cwd + '/arm/lpc54608']
    if rtconfig.CROSS_TOOL == 'gcc':
        LIBS = ['Persimmon_gcc']
    elif rtconfig.CROSS_TOOL == 'keil':
        LIBS = ['Persimmon_rvds']
    else :
        LIBS = []
elif GetDepend('SOC_IMXRT1052'):
    LIBPATH = [cwd + '/arm/imxrt1052']
    if rtconfig.CROSS_TOOL == 'gcc':
        LIBS = ['Persimmon_gcc']
    elif rtconfig.CROSS_TOOL == 'keil':
        LIBS = ['Persimmon_rvds']
    else :
        LIBS = []
else :
    LIBPATH = []
    LIBS = []

group = DefineGroup('Persimmon', src, depend = ['PKG_USING_PERSIMMON'], LIBS = LIBS, LIBPATH = LIBPATH, CPPPATH = CPPPATH)

group = group + SConscript('examples/SConscript')

Return('group')
