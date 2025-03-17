import time
import pybullet as p
from snippets.color_printer import print_code
from snippets.log_config import configure_logger
import logging


def main():
    configure_logger()

    p.connect(p.GUI)
    r2d2 = p.loadURDF("movable.urdf")

    t = 0
    while p.isConnected():
        try:
            time.sleep(1.0 / 240)
            p.stepSimulation()
        except KeyboardInterrupt:
            p.disconnect()


if __name__ == "__main__":
    main()
