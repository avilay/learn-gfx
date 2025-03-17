from direct.showbase.ShowBase import ShowBase


class MyApp(ShowBase):
    def __init__(self):
        super().__init__()
        self.scene = self.loader.loadModel("models/environment")
        self.scene.reparentTo(self.render)  # type: ignore
        self.scene.setScale(0.25, 0.25, 0.25)  # type: ignore
        self.scene.setPos(-8, 42, 0)  # type: ignore


app = MyApp()
app.run()
