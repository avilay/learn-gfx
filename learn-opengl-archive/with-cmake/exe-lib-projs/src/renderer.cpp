#include <gfx/gfx.h>

void Window::render() {
  if (!glfwInit())
    throw "Initialization failed!";
  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw "Unable to create window!";
  }
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK)
    throw "Initialization failed!";
}

void Window::drawTriange(Vertex a, Vertex b, Vertex c) {
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
