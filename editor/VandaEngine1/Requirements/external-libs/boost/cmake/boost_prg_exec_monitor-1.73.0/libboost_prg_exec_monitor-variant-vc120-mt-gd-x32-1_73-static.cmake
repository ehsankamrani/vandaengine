# Generated by Boost 1.73.0

# address-model=32

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "32 bit, need 64")
  return()
endif()

# layout=versioned

# toolset=vc120

if(Boost_COMPILER)
  if(NOT Boost_COMPILER STREQUAL "vc120" AND NOT Boost_COMPILER STREQUAL "-vc120")
    _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "vc120, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "vc120")
    _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "vc120, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=shared

if(Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "shared runtime, Boost_USE_STATIC_RUNTIME=${Boost_USE_STATIC_RUNTIME}")
  return()
endif()

# runtime-debugging=on

if(NOT "${Boost_USE_DEBUG_RUNTIME}" STREQUAL "" AND NOT Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "debug runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=debug

if(NOT "${Boost_USE_DEBUG_LIBS}" STREQUAL "" AND NOT Boost_USE_DEBUG_LIBS)
  _BOOST_SKIPPED("libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib" "debug, Boost_USE_DEBUG_LIBS=${Boost_USE_DEBUG_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib")
endif()

# Create imported target Boost::prg_exec_monitor

if(NOT TARGET Boost::prg_exec_monitor)
  add_library(Boost::prg_exec_monitor STATIC IMPORTED)

  set_target_properties(Boost::prg_exec_monitor PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB"
  )
endif()

# Target file name: libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib

get_target_property(__boost_imploc Boost::prg_exec_monitor IMPORTED_LOCATION_DEBUG)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::prg_exec_monitor already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::prg_exec_monitor APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)

set_target_properties(Boost::prg_exec_monitor PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG CXX
  IMPORTED_LOCATION_DEBUG "${_BOOST_LIBDIR}/libboost_prg_exec_monitor-vc120-mt-gd-x32-1_73.lib"
  )

list(APPEND _BOOST_PRG_EXEC_MONITOR_DEPS headers)
