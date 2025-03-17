import pygame as pg
import aliens.consts as k


class Shot(pg.sprite.Sprite):
    # class properties that are true for all shots
    speed = -11
    images: list[pg.Surface] = [pg.image.load(str(k.ASSETS_HOME / "shot.gif"))]

    def __init__(self, pos, *groups):
        super().__init__(*groups)
        self.image = self.images[0]
        self.rect = self.image.get_rect(midbottom=pos)

    def update(self):
        self.rect.move_ip(0, self.speed)
        if self.rect.top <= 0:
            self.kill()
