#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "armadillo" for configuration "Debug"
set_property(TARGET armadillo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(armadillo PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libarmadillo.so.9.900.2"
  IMPORTED_SONAME_DEBUG "libarmadillo.so.9"
  )

list(APPEND _IMPORT_CHECK_TARGETS armadillo )
list(APPEND _IMPORT_CHECK_FILES_FOR_armadillo "${_IMPORT_PREFIX}/lib/libarmadillo.so.9.900.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
