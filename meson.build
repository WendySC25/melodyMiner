project('melodyMiner', 'cpp')

srcs = [
    'src/main.cpp',
    'src/Miner.cpp',
    'src/ID3Tag.cpp',
]

# TagLib
taglib_dep = dependency('taglib')

executable('melodyMiner', srcs, dependencies : taglib_dep)
