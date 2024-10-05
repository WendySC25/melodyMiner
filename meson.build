project('melodyMiner', 'cpp', 'c',
    default_options : ['cpp_std=c++17'])

# Components
mining_srcs = [
    'src/mining/Miner.cpp',
]

utils_srcs = [
    'src/utils/ID3Tag.cpp',
    'src/utils/ID3TagManager.cpp',
    'src/utils/ConfigurationFile.cpp',
]

database_srcs = [
    'src/database/Database.cpp',
    'src/database/daos/AlbumDAO.cpp',
    'src/database/models/Album.cpp',
    'src/database/daos/PerformerDAO.cpp',
    'src/database/models/Performer.cpp',
    'src/database/daos/GroupDAO.cpp',
    'src/database/models/Group.cpp',
    'src/database/daos/PersonDAO.cpp',
    'src/database/models/Person.cpp',
    'src/database/daos/RolaDAO.cpp',
    'src/database/models/Rola.cpp',
]

srcs = [
    'src/main.cpp',
] + mining_srcs + utils_srcs + database_srcs

# Define dependencies
taglib_dep = dependency('taglib', required: true)
gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')
sqlite_dep = dependency('sqlite3', required: true)

executable('melodyMiner', srcs,
    dependencies : [taglib_dep, gtkmm_dep, sqlite_dep],
    link_args : ['-L/opt/homebrew/Cellar/taglib/1.13.1/lib', '-ltag', '-ltag_c']
)

# agahsg
simple_srcs = [
    'src/gui/simple2.cpp',
]

executable('my_program', simple_srcs,
    dependencies: gtkmm_dep,
    win_subsystem: 'windows',
)

# Test
test_srcs = [
    'test/testQuery.c',
]

unity_srcs = [
    'third_party/unity/src/unity.c',
]

unity_lib = static_library('unity', unity_srcs)

test_exe = executable('test_my_code', test_srcs,
                      link_with: unity_lib)

test('unit_test', test_exe)