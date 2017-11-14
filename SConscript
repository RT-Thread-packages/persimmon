Import('rtconfig')
from building import *

cwd = GetCurrentDir()
src = []

CPPPATH = [cwd]

if GetDepend('RT_USING_HARD_FLOAT'):
    LIBS = ['libPersimmon_hard_gcc']
else:
    LIBS = ['libPersimmon_soft_gcc']

if GetDepend('BOARD_X1000_REALBOARD'):
    LIBPATH = [cwd + '/mips/x1000']
else:
    LIBPATH = []

group = DefineGroup('Persimmon', src, depend = ['PKG_USING_PERSIMMON'], LIBS = LIBS, LIBPATH = LIBPATH, CPPPATH = CPPPATH)

Return('group')
