from direct.showbase.ShowBase import ShowBase
from panda3d.core import WindowProperties


class Game(ShowBase):
    def __init__(self):
        super().__init__()
        win_props = WindowProperties()
        win_props.setSize(1000, 750)
        self.win.requestProperties(win_props)
        self.disableMouse()


game = Game()
game.run()
