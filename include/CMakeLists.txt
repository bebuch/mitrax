cmake_minimum_required (VERSION 2.8.11)

file(GLOB header "mitrax/**.hpp")
add_library(bebuch_mitrax STATIC ${header})

set_target_properties(bebuch_mitrax PROPERTIES LINKER_LANGUAGE CXX)
# set_target_properties(bebuch_mitrax PROPERTIES CXX_STANDARD 17)
