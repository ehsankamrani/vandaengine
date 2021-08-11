# Generated by Boost 1.73.0

# address-model=32

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "32 bit, need 64")
  return()
endif()

# python=2.7

if(Boost_PYTHON_VERSION)
  string(REGEX REPLACE "([0-9]+[.][0-9]+)([.].*)?" "\\1" __boost_pyver ${Boost_PYTHON_VERSION})
  if(NOT __boost_pyver VERSION_EQUAL "2.7")
    _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "2.7, Boost_PYTHON_VERSION=${Boost_PYTHON_VERSION}")
    return()
  endif()
endif()

if(Boost_PYTHON_VERSION_MAJOR)
  if(NOT "2.7" MATCHES "^${Boost_PYTHON_VERSION_MAJOR}[.]")
    _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "2.7, Boost_PYTHON_VERSION_MAJOR=${Boost_PYTHON_VERSION_MAJOR}")
    return()
  endif()
endif()

# layout=versioned

# toolset=vc120

if(Boost_COMPILER)
  if(NOT Boost_COMPILER STREQUAL "vc120" AND NOT Boost_COMPILER STREQUAL "-vc120")
    _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "vc120, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "vc120")
    _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "vc120, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=static

if(NOT Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "static runtime, Boost_USE_STATIC_RUNTIME not ON")
  return()
endif()

# runtime-debugging=off

if(Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "release runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=release

if(NOT "${Boost_USE_RELEASE_LIBS}" STREQUAL "" AND NOT Boost_USE_RELEASE_LIBS)
  _BOOST_SKIPPED("libboost_python27-vc120-mt-s-x32-1_73.lib" "release, Boost_USE_RELEASE_LIBS=${Boost_USE_RELEASE_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_python27-vc120-mt-s-x32-1_73.lib")
endif()

if(NOT Boost_PYTHON_VERSION)
  if(Boost_DEBUG)
    message(STATUS "  Setting Boost_PYTHON_VERSION to 2.7")
  endif()
  set(Boost_PYTHON_VERSION "2.7")
endif()

# Create imported target Boost::python

if(NOT TARGET Boost::python)
  add_library(Boost::python STATIC IMPORTED)

  set_target_properties(Boost::python PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB"
  )
endif()

# Target file name: libboost_python27-vc120-mt-s-x32-1_73.lib

get_target_property(__boost_imploc Boost::python IMPORTED_LOCATION_RELEASE)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::python already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/libboost_python27-vc120-mt-s-x32-1_73.lib'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::python APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)

set_target_properties(Boost::python PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE CXX
  IMPORTED_LOCATION_RELEASE "${_BOOST_LIBDIR}/libboost_python27-vc120-mt-s-x32-1_73.lib"
  )

set_target_properties(Boost::python PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

list(APPEND _BOOST_PYTHON_DEPS headers)
