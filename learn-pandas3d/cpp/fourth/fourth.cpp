#include <iostream>

#include "pandaFramework.h"
#include "pandaSystem.h"

#include "asyncTaskManager.h"
#include "genericAsyncTask.h"

#include "cIntervalManager.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"

PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
PT(ClockObject) globalClock = ClockObject::get_global_clock();
NodePath camera;

AsyncTask::DoneStatus spinCameraTask(GenericAsyncTask* task, void* data) {
  double time = globalClock->get_real_time();
  double angleDeg = time * 6.0;
  double angleRad = angleDeg * (3.14 / 180.0);
  camera.set_pos(20 * sin(angleRad), -20 * cos(angleRad), 3);
  camera.set_hpr(angleDeg, 0, 0);

  return AsyncTask::DS_cont;
}

int main(int argc, char** argv) {
  PandaFramework framework;
  framework.open_framework(argc, argv);
  framework.set_window_title("My Panda3D Window");

  WindowFramework* window = framework.open_window();
  camera = window->get_camera_group();

  NodePath scene =
      window->load_model(framework.get_models(), "models/environment");
  scene.reparent_to(window->get_render());
  scene.set_scale(0.25, 0.25, 0.25);
  scene.set_pos(-8, 42, 0);

  NodePath pandaActor =
      window->load_model(framework.get_models(), "models/panda-model");
  pandaActor.set_scale(0.005);
  pandaActor.reparent_to(window->get_render());
  window->load_model(pandaActor, "models/panda-walk4");
  window->loop_animations(0);

  // Create the lerp intervals needed to walk back and forth
  PT(CLerpNodePathInterval)
  pandaPosInterval1, pandaPosInterval2, pandaHprInterval1, pandaHprInterval2;

  pandaPosInterval1 = new CLerpNodePathInterval(
      "pandaPosInterval1", 13.0, CLerpInterval::BT_no_blend, true, false,
      pandaActor, NodePath());
  pandaPosInterval1->set_start_pos(LPoint3(0, 10, 0));
  pandaPosInterval1->set_end_pos(LPoint3(0, -10, 0));

  pandaPosInterval2 = new CLerpNodePathInterval(
      "pandaPosInterval2", 13.0, CLerpInterval::BT_no_blend, true, false,
      pandaActor, NodePath());
  pandaPosInterval2->set_start_pos(LPoint3(0, -10, 0));
  pandaPosInterval2->set_end_pos(LPoint3(0, 10, 0));

  pandaHprInterval1 = new CLerpNodePathInterval(
      "pandaHprInterval1", 3.0, CLerpInterval::BT_no_blend, true, false,
      pandaActor, NodePath());
  pandaHprInterval1->set_start_hpr(LPoint3(0, 0, 0));
  pandaHprInterval1->set_end_hpr(LPoint3(180, 0, 0));

  pandaHprInterval2 = new CLerpNodePathInterval(
      "pandaHprInterval2", 3.0, CLerpInterval::BT_no_blend, true, false,
      pandaActor, NodePath());
  pandaHprInterval2->set_start_hpr(LPoint3(180, 0, 0));
  pandaHprInterval2->set_end_hpr(LPoint3(0, 0, 0));

  PT(CMetaInterval) pandaPace;
  pandaPace = new CMetaInterval("pandaPace");
  pandaPace->add_c_interval(pandaPosInterval1, 0,
                            CMetaInterval::RS_previous_end);
  pandaPace->add_c_interval(pandaHprInterval1, 0,
                            CMetaInterval::RS_previous_end);
  pandaPace->add_c_interval(pandaPosInterval2, 0,
                            CMetaInterval::RS_previous_end);
  pandaPace->add_c_interval(pandaHprInterval2, 0,
                            CMetaInterval::RS_previous_end);
  pandaPace->loop();

  taskMgr->add(
      new GenericAsyncTask("Spins the camera", &spinCameraTask, nullptr));

  // Al alternate way to run the engine
  Thread* currThread = Thread::get_current_thread();
  while (framework.do_frame(currThread)) {
    CIntervalManager::get_global_ptr()->step();
  }

  framework.close_framework();
  return 0;
}
