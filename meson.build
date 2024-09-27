project('melodyMiner', 'cpp',
        default_options : ['cpp_std=c++14'])


srcs = [
    'src/main.cpp',
    'src/Miner.cpp',
    'src/ID3Tag.cpp',
]

taglib_dep = dependency('taglib', required : true)

executable('melodyMiner', srcs, 
    dependencies : [taglib_dep],
    link_args : ['-L/opt/homebrew/Cellar/taglib/1.13.1/lib', '-ltag', '-ltag_c']
)
