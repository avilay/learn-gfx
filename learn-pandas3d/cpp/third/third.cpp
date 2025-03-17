#include "pandaFramework.h"
#include "pandaSystem.h"

#include "asyncTaskManager.h"
#include "genericAsyncTask.h"

// Global stuff
PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
PT(ClockObject) globalClock = ClockObject::get_global_clock();
NodePath camera;

// Task to move camera
AsyncTask::DoneStatus spinCameraTask(GenericAsyncTask* task, void* data) {
  double time = globalClock->get_real_time();
  double angleDeg = time * 6.0;
  double angleRad = angleDeg * (3.14 / 180.0);
  camera.set_pos(20 * sin(angleRad), -20.0 * cos(angleRad), 3);
  camera.set_hpr(angleDeg, 0, 0);

  return AsyncTask::DS_cont;
}

int main(int argc, char** argv) {
  // Open a new window framework and set the title
  PandaFramework framework;
  framework.open_framework(argc, argv);
  framework.set_window_title("My Panda3D Window");

  // Open the window
  WindowFramework* window = framework.open_window();
  camera = window->get_camera_group();

  // Load the environment model
  NodePath scene =
      window->load_model(framework.get_models(), "models/environment");
  scene.reparent_to(window->get_render());
  scene.set_scale(0.25, 0.25, 0.25);
  scene.set_pos(-8, 42, 0);

  // Load our panda
  NodePath pandaActor =
      window->load_model(framework.get_models(), "models/panda-model");
  pandaActor.set_scale(0.005);
  pandaActor.reparent_to(window->get_render());

  // Load the walk animation
  window->load_model(pandaActor, "models/panda-walk4");
  window->loop_animations(0);

  // Add task to main loop
  taskMgr->add(
      new GenericAsyncTask("Spins the camera", &spinCameraTask, nullptr));

  // Run the engine
  framework.main_loop();
  framework.close_framework();
  return 0;
}