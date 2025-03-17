import time
import pybullet as p
from snippets.color_printer import print_success, print_error, print_code
from snippets.log_config import configure_logger
import logging


def main():
    configure_logger()

    p.connect(p.SHARED_MEMORY)
    if p.isConnected():
        print_success("Connected to shared memory server.")
    else:
        print_error("Unable to connect to shared memory server!")
        exit(1)

    p.setAdditionalSearchPath("/Users/avilayparekh/projects/cloned/bullet3/data")
    p.setGravity(0, 0, -10)
    p.loadURDF("plane.urdf")

    start_pos = [0, 0, 100]
    start_orn = p.getQuaternionFromEuler([0, 0, 0])
    cube = p.loadURDF("./urdfs/cube.urdf", start_pos, start_orn)

    p.setRealTimeSimulation(1)
    while p.isConnected():
        time.sleep(1)
        pos, orn = p.getBasePositionAndOrientation(cube)
        orn = p.getEulerFromQuaternion(orn)
        logging.info(
            f"Position: ({pos[0]:.3f}, {pos[1]:.3f}, {pos[2]:.3f}), Orientation: ({orn[0]:.3f}, {orn[1]:.3f}, {orn[2]:.3f})"
        )


if __name__ == "__main__":
    main()
