from direct.directbase.DirectStart import base
from panda3d.core import Vec3
from panda3d.bullet import (
    BulletWorld,
    BulletPlaneShape,
    BulletRigidBodyNode,
    BulletBoxShape,
)

base.cam.setPos(0, -10, 0)
base.cam.lookAt(0, 0, 0)

world = BulletWorld()
world.setGravity(Vec3(0, 0, -9.81))

plane_shape = BulletPlaneShape(Vec3(0, 0, 1), 1)
ground_node = BulletRigidBodyNode("Ground")
ground_node.addShape(plane_shape)
rendered_ground_node = render.attachNewNode(ground_node)
rendered_ground_node.setPos(0, 0, -2)
world.attachRigidBody(ground_node)
ground_model = loader.loadModel("models/box.egg")
ground_model.flattenLight()
ground_model.reparentTo(rendered_ground_node)

box_shape = BulletBoxShape(Vec3(0.5, 0.5, 0.5))
box_node = BulletRigidBodyNode("Box")
box_node.setMass(1.0)
box_node.addShape(box_shape)
rendered_box_node = render.attachNewNode(box_node)
rendered_box_node.setPos(0, 0, 2)
world.attachRigidBody(box_node)
model = loader.loadModel("models/box.egg")
model.flattenLight()
model.reparentTo(rendered_box_node)


def update(task):
    dt = globalClock.getDt()
    world.doPhysics(dt)
    return task.cont


taskMgr.add(update, "update")
base.run()

