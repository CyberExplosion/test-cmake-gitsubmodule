cmake_minimum_required(VERSION 3.21.4)

project(Jeus)

# Compile each files into an objects
add_executable(${PROJECT_NAME} main.cpp)

# You can build each object seperately into library and then link it at the end at the end

# Add a subdirectoy to the build list
# If the subdirectory has a CMakeList.txt, activate it too
add_subdirectory(Adder)

## Download all the Submodules
find_package(Git QUIET) # The quiet disable the message saying that git not found yada yada
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")  # This is different than the build folder, check if there's a .git init folder
    option (GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")  # The first arg for message tell which mode should the message be displayed in
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive   # The command tag tell it's a command we running, with what arguments
            # GIT_EXECUTABLE is built in to CMAKE and some Git related funcitons. Look online for more
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}   # The tag tells that the next arg is the directory to run the previous commands on
                        RESULT_VARIABLE GIT_SUBMOD_RESULT   # The tag says to store the result of the previous command into what variable. Commands usually result in 0 for pass and 1 for fail in Linux Shell
        )
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT), please checkout submodules")
        endif()
    endif()
endif()
### All submodules should be downloaded

## Check if all the Submodules is downloaded and exist
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")    # See if the CMakeList.txt exist in our submodule so we can build the project that depends on it
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed.")
endif()

# Do the same thing for the the GLFW
add_subdirectory(external/glfw)

# CMake will make the main.cpp #include<> with this folder
# So we don't have to directly go into the folder in the main.cpp #include<>
target_include_directories(${PROJECT_NAME}
    PRIVATE Adder
    PRIVATE external/glfw/include
)

# Link the directory to your project
target_link_directories(${PROJECT_NAME} 
    PRIVATE Adder
    PRIVATE external/glfw/src
)
# Add Private because you need to have a permission or sth ???? look into this more
# Private means you ALONE using this directory. If you have any
    # other project depends on you, they WILL NOT see this directory

# target_link_directories FOLLOWs the build/ folder.
    # so if anything bad happen, look into the build/ folder to see if you got the files directories looks correctly
# The linker will use this to find the source file, the finished building product
    # If use git submodule, it should be their build/src folder

# Link the library to our core project
# You can link multiple libraries to the Project, just put more libraries name
target_link_libraries(${PROJECT_NAME} adder glfw)
# C++ and C library starts with the lib___, therefore the library name is minus the *lib* part in their filename. .a is static, .so is dynamic
