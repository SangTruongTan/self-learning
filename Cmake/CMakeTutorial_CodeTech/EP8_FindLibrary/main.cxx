#include "ep8Config.h"
#ifdef USE_ADDER
#include "adder.h"
#endif
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


int main(int argc, const char **argv) {
    std::cout << argv[0] << " <== VERSION: " << EP8_VERSION_MAJOR << "."
              << EP8_VERSION_MINOR << "." << EP8_VERSION_PATCH << std::endl;
#ifdef USE_ADDER
    std::cout << "2 + 3 = " << mearlymath::add(2, 3) << std::endl;
#else
    std::cout << "Adder Library is disable" << std::endl;
#endif
    std::cout << "Episode 8: Find Library" << std::endl;
    GLFWwindow* window;
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }
    window = glfwCreateWindow( 300, 300, "Gears By Zeus", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return EXIT_SUCCESS;
}
