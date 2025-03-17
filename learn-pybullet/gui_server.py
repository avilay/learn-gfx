import time
import pybullet as p
from snippets.color_printer import print_success


def main():
    # client = p.connect(p.GUI_SERVER)
    p.connect(p.GRAPHICS_SERVER)
    if p.isConnected():
        print_success("Started the GUI Physics server")
    else:
        raise RuntimeError("Unable to start the Physics server!")
    t = 0
    while p.isConnected():
        try:
            t += 1
            if t % 10 == 0:
                print(f"Simulating time step {t}")
            p.stepSimulation()
            time.sleep(1.0 / 240)
        except KeyboardInterrupt:
            p.disconnect()


if __name__ == "__main__":
    main()
