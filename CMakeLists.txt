cmake_minimum_required(VERSION 3.21.4)

project(Jeus)

# Compile each files into an objects
add_executable(${PROJECT_NAME} main.cpp)

# You can build each object seperately into library and then link it at the end at the end

# Add a subdirectoy to the build list
# If the subdirectory has a CMakeList.txt, activate it too
add_subdirectory(Adder)

# CMake will make the main.cpp #include<> with this folder
# So we don't have to directly go into the folder in the main.cpp #include<>
target_include_directories(${PROJECT_NAME} PRIVATE Adder)

# Link the directory to your project
target_link_directories(${PROJECT_NAME} PRIVATE Adder)
# Add Private because you need to have a permission or sth ???? look into this more
# Private means you ALONE using this directory. If you have any
    # other project depends on you, they WILL NOT see this directory

# target_link_directories FOLLOWs the build/ folder.
    # so if anything bad happen, look into the build/ folder to see if you got the files directories looks correctly

# Link the library to our core project
# You can link multiple libraries to the Project, just put more libraries name
target_link_libraries(${PROJECT_NAME} adder)