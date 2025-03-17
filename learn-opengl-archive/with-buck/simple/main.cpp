/*
 * Install glew and glfw
 * $ brew install glew
 * $ brew install glfw
 *
 * Build this source as follows:
 * clang++ -g main.cpp -std=c++17 -o main -lglfw.3 -lGLEW.2.1 -framework OpenGL
 * -framework Cocoa -framework IOKit
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main() {
  cout << "Starting..." << endl;
  GLFWwindow* window;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    return -1;

  cout << "OpenGL ver=" << glGetString(GL_VERSION) << endl;

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
