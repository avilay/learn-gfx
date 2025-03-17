#include "pandaFramework.h"
#include "pandaSystem.h"

int main(int argc, char* argv[]) {
  // Load the window and set its title
  PandaFramework framework;
  framework.open_framework(argc, argv);
  framework.set_window_title("My Panda 3D Window");
  WindowFramework* window = framework.open_window();

  // Uncomment to use mouse to navigate around the scene
  // window->setup_trackball();

  // Load the environment model
  NodePath scene =
      window->load_model(framework.get_models(), "models/environment");
  scene.reparent_to(window->get_render());
  scene.set_scale(0.25f, 0.25f, 0.25f);
  scene.set_pos(-8, 42, 0);

  // Run the engine
  framework.main_loop();
  framework.close_framework();
  return 0;
}
