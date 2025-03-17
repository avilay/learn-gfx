import aliens.consts as k
import pygame as pg

from aliens.utils import Direction
import logging

logger = logging.getLogger(__name__)


def load_images():
    img = pg.image.load(str(k.ASSETS_HOME / "player1.gif"))
    flipped_img = pg.transform.flip(img, flip_x=True, flip_y=False)
    return [img, flipped_img]


class Player(pg.sprite.Sprite):
    # class properties that are true everytime player is spawned
    speed = 3
    bounce = 24
    gun_offset = -11
    images: list[pg.Surface] = load_images()

    def __init__(self, *groups):
        super().__init__(*groups)
        self.image = self.images[0]
        self.rect = self.image.get_rect(midbottom=k.SCREENRECT.midbottom)
        self.origtop = self.rect.top
        self.direction = Direction.LEFT
        self.reloading = False

    def move(self, direction):
        if direction == Direction.STILL:
            return
        self.direction = direction
        self.rect.move_ip(direction.value * Player.speed, 0)
        self.rect = self.rect.clamp(k.SCREENRECT)
        if direction == Direction.LEFT:
            self.image = Player.images[0]
        else:
            self.image = Player.images[1]

        # Give the tank a little bounce to simulate rough ground by moving
        # its rectangle a little bit
        self.rect.top = self.origtop - (self.rect.left // Player.bounce % 2)

    def gunpos(self):
        pos = self.direction.value * Player.gun_offset + self.rect.centerx
        return pos, self.rect.top
