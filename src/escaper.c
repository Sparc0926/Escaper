#include <escaper.h>
#include <stdio.h>
#include <glew.h>
#include <glfw3.h>

int main()
{
    GLFWwindow* window;
    // initialize GLFW
    if (!glfwInit()) {
        printf("GLFW initialization falied!\n");
        return -1;
    }
    // Set OpenGL version and profile hints (core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // create window and its OpenGL context
    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Escaper", NULL, NULL);
    if (!window) {
		printf("Window creation failed!\n");
        glfwTerminate();
        return -1;
    }
    // make the window's context current
    glfwMakeContextCurrent(window);
    // initialize GLEW
    glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("GLEW initialization failed!\n");
		return -1;
	}
    // main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(SKY_BLUE);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    } glfwTerminate();
	return 0;
}
