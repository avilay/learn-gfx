import pygame as pg
import random
import logging
from aliens.utils import Direction
import aliens.consts as k

# from aliens.sprites import Direction

logger = logging.getLogger(__name__)


def load_images():
    return [
        pg.image.load(str(k.ASSETS_HOME / "alien1.gif")),
        pg.image.load(str(k.ASSETS_HOME / "alien2.gif")),
        pg.image.load(str(k.ASSETS_HOME / "alien3.gif")),
    ]


class Alien(pg.sprite.Sprite):
    # class properties true for all aliens spawned
    speed = 5
    animcycle = 12
    images: list[pg.Surface] = load_images()

    def __init__(self, *groups):
        super().__init__(*groups)
        self.image = Alien.images[0]
        self.rect = self.image.get_rect()
        self.direction = random.choice((Direction.LEFT, Direction.RIGHT))
        self.frame = 0

        # If the alien is facing right, then it should start from the top left.
        # There is nothing to do in this case because the default top left
        # of the rect is (0, 0). However, if the alien is facing left, then
        # it needs to start from the top right.
        if self.direction == Direction.LEFT:
            self.rect.right = k.SCREENRECT.right

    def update(self, *args, **kwargs):
        # Move the alien along the x-axis in whatever direction it is facing.
        # self.rect.move_ip(self.facing * Alien.speed, 0)
        self.rect.move_ip(self.direction.value * Alien.speed, 0)

        # Aliens that have gone off screen need to change direction
        # and come down (on the y-axis)
        if not k.SCREENRECT.contains(self.rect):
            self.direction = Direction.change(self.direction)
            self.rect.top = self.rect.bottom + 1
            self.rect = self.rect.clamp(k.SCREENRECT)

        # Animate the alien ship by swapping out the image every few frames
        self.frame = self.frame + 1
        self.image = self.images[self.frame // Alien.animcycle % 3]
