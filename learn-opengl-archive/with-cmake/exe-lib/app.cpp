#include <gfx.h>
#include <iostream>

using namespace std;

int main() {
  cout << "Starting..." << endl;

  Window window(480, 640, "Hello World");
  window.render();
  window.drawTriange(Vertex(-0.5f, -0.5f), Vertex(0.0f, 0.5f),
                     Vertex(0.5f, -0.5f));
}
