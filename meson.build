project('melodyMiner', 'c')

# Dependency
id3tag_dep = dependency('id3tag')

# Source directories
src = files('src/main.c', 'src/miner.c', 'src/ID3Tag.c')

# Excutable
executable('music_miner', src, dependencies: id3tag_dep)    