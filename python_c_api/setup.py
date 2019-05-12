from distutils.core import setup, Extension

module1 = Extension('combinatorics', sources = ['combinatorics.c'])

setup (name = 'combinatorics',
       version = '1.0',
       description = 'Модуль для решения комбинаторных задач',
       ext_modules = [module1])
