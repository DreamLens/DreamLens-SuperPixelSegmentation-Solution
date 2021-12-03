include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVL_DISABLE_SSE2")

add_library(libQuickShift generic.c host.c quickshift.c random.c)
#target_link_libraries(libQuickShift m pthrea