function(build_physics_simulation)
    message("Building physics_simulation...")

    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

    include(FetchContent)
    FetchContent_Declare(
      physics_backend
      GIT_REPOSITORY https://github.com/hayesHowYaDoin/physics_backend.git
      GIT_TAG        v0.2.0
    )
    FetchContent_MakeAvailable(physics_backend)

    set(TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/physics_simulation_en_US.ts)

    set(PROJECT_SOURCES
            ${TS_FILES}
    )

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/physics_simulation)

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(physics_simulation
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET physics_simulation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    else()
        if(ANDROID)
            add_library(physics_simulation SHARED
                ${PROJECT_SOURCES}
            )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        else()
            add_executable(physics_simulation
                ${PROJECT_SOURCES}
            )
        endif()

        qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()

    target_link_libraries(physics_simulation
        PRIVATE
            Qt${QT_VERSION_MAJOR}::Widgets
            physics_backend
    )

    # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
    # If you are developing for iOS or macOS you should consider setting an
    # explicit, fixed bundle identifier manually though.
    if(${QT_VERSION} VERSION_LESS 6.1.0)
      set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.physics_simulation)
    endif()
    set_target_properties(physics_simulation PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

    include(GNUInstallDirs)
    install(TARGETS physics_simulation
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(physics_simulation)
    endif()

endfunction()
