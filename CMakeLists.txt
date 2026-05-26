cmake_minimum_required(VERSION 3.14)
project(BilliardsGame)

set(CMAKE_CXX_STANDARD 17)

# SFML'i internetten otomatik indirir (Kurulum derdini bitirir)
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

# Kendi dosyalarını buraya ekle
add_executable(BilliardsGame main.cpp Game.cpp Balls.cpp Table.cpp Cue.cpp)

# Kütüphaneleri bağla
target_link_libraries(BilliardsGame sfml-graphics sfml-window sfml-system sfml-audio)

# BU KISIM ÇOK ÖNEMLİ: DLL dosyalarını otomatik olarak .exe yanına kopyalar
if(WIN32)
    add_custom_command(TARGET BilliardsGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:BilliardsGame>
        $<TARGET_FILE_DIR:BilliardsGame>
        COMMAND_EXPAND_LISTS
    )

    # Masanın resmini otomatik olarak .exe yanına kopyalar
        add_custom_command(TARGET BilliardsGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/bilyardo_gelismis.jpeg"
            $<TARGET_FILE_DIR:BilliardsGame>
        )

        # Topların olduğu klasörü otomatik olarak .exe yanına kopyalar
      add_custom_command(TARGET BilliardsGame POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_SOURCE_DIR}/bil_top"
      "$<TARGET_FILE_DIR:BilliardsGame>/bil_top"
       )

       # Istaka resmini otomatik olarak .exe yanına kopyalar
    add_custom_command(TARGET BilliardsGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/cue.png" # Resmin adını buraya yaz
    "$<TARGET_FILE_DIR:BilliardsGame>"
      )

      file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Fonts
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()