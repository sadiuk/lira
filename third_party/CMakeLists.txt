 ### GLFW ###
set(GLFW_LIB_NAME "glfw")
set(GLFW_INC_PATH ${GLFW_LIB_NAME}/include)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_LIB_NAME})

### GLAD ###
set(GLAD_LIB_NAME "glad")
set(GLAD_SRC_PATH "${GLAD_LIB_NAME}/src")
set(GLAD_INC_PATH "${GLAD_LIB_NAME}/include")

add_library( ${GLAD_LIB_NAME}
    STATIC
        "${GLAD_SRC_PATH}/glad.c"
)

target_include_directories(${GLAD_LIB_NAME}
    PUBLIC
        "${GLAD_INC_PATH}"
)


set(OBJ_LIB_NAME "OBJ-Loader")
set(OBJ_INCLUDE_PATH ${OBJ_LIB_NAME}/Source)


set(LIRA_THIRD_PARTY_SOURCES ${OBJ_INCLUDE_PATH}/OBJ_Loader.ixx)


target_include_directories(lira PUBLIC third_party/glad/include third_party/glfw/include include)

target_link_libraries(lira glad glfw)