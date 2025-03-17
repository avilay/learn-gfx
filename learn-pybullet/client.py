import pybullet as p
import pybullet_data
from snippets.color_printer import print_success, print_error  # , print_code


def main():
    # p.connect(p.SHARED_MEMORY)
    p.connect(p.GRAPHICS_SERVER_TCP)
    if p.isConnected():
        print_success("Connected to GUI server over shared memory.")
    else:
        print_error("Unable to get connection!")
        exit(1)
    p.setAdditionalSearchPath(pybullet_data.getDataPath())
    p.setGravity(0, 0, -10)
    p.loadURDF("plane.urdf")
    start_pos = [0, 0, 2]
    start_orn = p.getQuaternionFromEuler([0, 0, 0])
    box_id = p.loadURDF("r2d2.urdf", start_pos, start_orn)
    p.resetBasePositionAndOrientation(box_id, start_pos, start_orn)
    print_success("Loaded assets.")
    # p.setRealTimeSimulation(1)

    while p.isConnected():
        try:
            p.stepSimulation()
        except KeyboardInterrupt:
            p.disconnect()


if __name__ == "__main__":
    main()
