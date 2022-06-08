# donwload boost
include(ExternalProject)
set(BOOST_VERSION 1.79.0)

message (STATUS "Setup Boost ${BOOST_VERSION} into ${CMAKE_INSTALL_PREFIX}.")
if (WIN32)
     set (BOOST_BOOTSTRAP_CMD ${BOOST_GIT_REPO_DIR}/bootstrap.bat)
     # It was bjam at one point; it is now b2
    set (BOOST_BUILD_CMD ${BOOST_GIT_REPO_DIR}/b2.exe)
elseif (UNIX)
    set (BOOST_BOOTSTRAP_CMD ./${BOOST_GIT_REPO_DIR}/bootstrap.sh)
    set (BOOST_BUILD_CMD ./${BOOST_GIT_REPO_DIR}/b2)
endif ()

ExternalProject_Add (
    boost
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-${BOOST_VERSION}
    GIT_PROGRESS 1
    BUILD_IN_SOURCE 1
    UPDATE_COMMAND ${BOOST_BOOTSTRAP_CMD}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${BOOST_BUILD_CMD} toolset=clang cxxflags=-stdlib=libc++ linkflags=-stdlib=libc++ --with-system --with-filesystem --with-thread --with-regex --with-iostreams link=static install --prefix=${CMAKE_INSTALL_PREFIX}
    INSTALL_COMMAND ""
    LOG_DOWNLOAD 1
    LOG_UPDATE 1
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
    )

# add the library that runs
add_library(LibA liba.cpp)
add_dependencies(LibA boost)
target_link_libraries(LibA PRIVATE boost_system) 

# state that anybody linking to us needs to include the current source dir
# to find liba.h, while we don't.
target_include_directories(
            LibA
            SYSTEM
            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
            PUBLIC ${CMAKE_INSTALL_PREFIX}/include
          )
target_link_directories(
            LibA
            PUBLIC
            ${CMAKE_INSTALL_PREFIX}/lib
          )
#add option for library
option(USE_LIBA "Use LibA" ON)
if(USE_LIBA)

endif()

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
target_compile_definitions(LibA PRIVATE "EXPORTING_MYMATH")

# install rules
set(installable_libs LibA)
install(TARGETS ${installable_libs} DESTINATION lib)
install(FILES liba.h DESTINATION include/liba)