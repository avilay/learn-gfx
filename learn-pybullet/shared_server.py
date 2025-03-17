import pybullet as p
from snippets.color_printer import print_success, print_error


def main():
    p.connect(p.SHARED_MEMORY_SERVER)
    # p.connect(p.GUI_SERVER)
    if p.isConnected():
        print_success("Server started.")
    else:
        print_error("Unable to start server!")
        exit(1)
    p.setRealTimeSimulation(1)
    input("Press [ENTER] to stop simulation.")
    p.disconnect()


if __name__ == "__main__":
    main()
