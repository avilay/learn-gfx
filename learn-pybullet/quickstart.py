import time
import pybullet as p
import pybullet_data
from snippets.color_printer import print_success, print_code


def main():
    client = p.connect(p.GUI)
    if p.getConnectionInfo(client)["isConnected"]:
        print_success("Connected to the GUI Physics server")
    else:
        raise RuntimeError("Unable to connect to the Physics server!")

    p.setAdditionalSearchPath(pybullet_data.getDataPath())
    print_success("Set assets search path")

    # Build the world
    p.setGravity(0, 0, -10)
    p.loadURDF("plane.urdf")
    start_pos = [0, 0, 2]
    start_orn = p.getQuaternionFromEuler([0, 0, 0])
    box_id = p.loadURDF("r2d2.urdf", start_pos, start_orn)
    p.resetBasePositionAndOrientation(box_id, start_pos, start_orn)
    for i in range(200):
        if i % 10 == 0:
            print(f"Simulating {i}")
        p.stepSimulation()
        time.sleep(1.0 / 240)
    end_pos, end_orn = p.getBasePositionAndOrientation(box_id)
    end_orn = p.getEulerFromQuaternion(end_orn)
    print_code(
        f"Position ({start_pos[0]:.3f}, {start_pos[1]:.3f}, {start_pos[2]:.3f}) --> ",
        end="",
    )
    print_code(f"({end_pos[0]:.3f}, {end_pos[1]:.3f}, {end_pos[2]:.3f})")
    print_code(
        f"Orientation ({start_orn[0]:.3f}, {start_orn[1]:3f}, {start_orn[2]:3f}) --> ",
        end="",
    )
    print_code(f"({end_orn[0]:.3f}, {end_orn[1]:3f}, {end_orn[2]:3f})")

    input("Press [ENTER] to shutdown simulation.")
    p.disconnect()


if __name__ == "__main__":
    main()
