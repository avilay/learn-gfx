from math import pi, sin, cos
from direct.showbase.ShowBase import ShowBase
from direct.task import Task
from direct.actor.Actor import Actor
from direct.interval.IntervalGlobal import Sequence
from panda3d.core import Point3


class MyApp(ShowBase):
    def __init__(self):
        super().__init__()
        self.scene = self.loader.loadModel("models/environment")
        self.scene.reparentTo(self.render)  # type: ignore
        self.scene.setScale(0.25, 0.25, 0.25)  # type: ignore
        self.scene.setPos(-8, 42, 0)  # type: ignore

        self.taskMgr.add(self.spin_camera_task, "SpinCameraTask")

        self.panda = Actor("models/panda-model", {"walk": "models/panda-walk4"})
        self.panda.setScale(0.005, 0.005, 0.005)
        self.panda.reparentTo(self.render)
        self.panda.loop("walk")
        pos_interval_1 = self.panda.posInterval(
            13, Point3(0, -10, 0), startPos=Point3(0, 10, 0)
        )
        pos_interval_2 = self.panda.posInterval(
            13, Point3(0, 10, 0), startPos=Point3(0, -10, 0)
        )
        hpr_interval_1 = self.panda.hprInterval(
            3, Point3(180, 0, 0), startHpr=Point3(0, 0, 0)
        )
        hpr_interval_2 = self.panda.hprInterval(
            3, Point3(0, 0, 0), startHpr=Point3(180, 0, 0)
        )
        self.panda_pace = Sequence(
            pos_interval_1,
            hpr_interval_1,
            pos_interval_2,
            hpr_interval_2,
            name="PandaPace",
        )
        self.panda_pace.loop()

    def spin_camera_task(self, task):
        angle_deg = task.time * 6.0
        angle_rad = angle_deg * (pi / 180.0)
        self.camera.setPos(20 * sin(angle_rad), -20 * cos(angle_rad), 3)
        self.camera.setHpr(angle_deg, 0, 0)
        return Task.cont


app = MyApp()
app.run()
