#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

class Vertex {
public:
  float x;
  float y;
  Vertex(float x, float y) : x(x), y(y) {}
};

class Window {
  int height;
  int width;
  string title;
  GLFWwindow *window;

public:
  Window(int height, int width, const string &title)
      : height(height), width(width), title(title){};
  void render();
  void drawTriange(Vertex a, Vertex b, Vertex c);
};
