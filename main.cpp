#include <iostream>

#include "adder.h"
//You don't want to add as path, lest do the include thing in CMake
// #include "external/glfw/include"
#include "GLFW/glfw3.h"

using namespace std;

int main () {
    cout << "Hello Man" << endl;

    cout << add (72.1, 73.8) << '\n';

    GLFWwindow* window;
    if (!glfwInit ())
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }
    
    window = glfwCreateWindow (300, 300, "Gears", NULL, NULL);
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
//         // Draw gears
//         draw();
// 
//         // Update animation
//         animate();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
}