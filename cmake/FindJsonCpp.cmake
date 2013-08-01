# Find module for JsonCpp

find_path(JsonCpp_INCLUDE_DIR json/json.h PATH_SUFFIXES jsoncpp)
find_library(JsonCpp_LIBRARY jsoncpp)

set(JsonCpp_LIBRARIES ${JsonCpp_LIBRARY})
set(JsonCpp_INCLUDE_DIRS ${JsonCpp_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JsonCpp DEFAULT_MSG JsonCpp_LIBRARY JsonCpp_INCLUDE_DIR)

mark_as_advanced(JsonCpp_INCLUDE_DIR JsonCpp_LIBRARY)
