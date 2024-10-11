project('melodyMiner', 'cpp',
    default_options : ['cpp_std=c++17'])

# Components
mining_srcs = [
    'src/mining/Miner.cpp',
]

utils_srcs = [
    'src/utils/ID3Tag.cpp',
    'src/utils/ID3TagManager.cpp',
    'src/utils/ConfigurationFile.cpp',
    'src/utils/QueryProcessor.cpp',  
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
    link_args : ['-ltag', '-ltag_c']
)

# agahsg
gui_srcs = [
    'src/gui/main.cc',
    'src/gui/melodyMinerWindow.cc',
    'src/gui/RolaDetailview.cc',   
    'src/gui/MinerDialog.cc',  
    'src/gui/dialog/FormatEditRola.cc',
    'src/gui/dialog/RolaController.cc',
]

all_src = gui_srcs + utils_srcs + database_srcs + mining_srcs

executable('my_program', all_src,
    dependencies: [gtkmm_dep, sqlite_dep, taglib_dep],
    win_subsystem: 'windows',
    link_args : ['-ltag', '-ltag_c']
)

# Test
test_srcs = [
    'test/testQuery.cpp',
    'src/utils/QueryProcessor.cpp',  

]

# Dependencia de Google Test
gtest_dep = dependency('gtest', required: true)

# Crear el ejecutable para las pruebas
test_exe = executable('test_my_code', test_srcs, dependencies: [gtest_dep])

# Definir el test en Meson
test('unit_test', test_exe)