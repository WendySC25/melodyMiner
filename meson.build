project('melodyMiner', 'cpp',
    default_options : ['cpp_std=c++17'])


srcs = [
    'src/main.cpp',
    'src/mining/Miner.cpp',
    'src/utils/ID3Tag.cpp',
    'src/database/Database.cpp',
]

taglib_dep = dependency('taglib', required: true)
gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')
sqlite_dep = dependency('sqlite3', required: true)

executable('melodyMiner', srcs,
    dependencies : [taglib_dep, gtkmm_dep, sqlite_dep],
    link_args : ['-L/opt/homebrew/Cellar/taglib/1.13.1/lib', '-ltag', '-ltag_c']
)

simple_srcs = [
    'src/gui/simple.cpp',
]

# Ejecutable para el programa simple
executable('my_program', simple_srcs,
    dependencies: gtkmm_dep,
    win_subsystem: 'windows',
)




