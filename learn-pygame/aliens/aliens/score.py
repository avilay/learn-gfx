import pygame as pg
from aliens.consts import SCREENRECT
import logging

logger = logging.getLogger(__name__)


class Score(pg.sprite.Sprite):
    def __init__(self, *groups):
        super().__init__(*groups)
        self.font = pg.font.Font(None, 32)
        self.font.set_italic(True)
        self.color = "white"
        self.image = self.font.render("Score: 0", True, self.color)
        self.rect = self.image.get_rect(topright=SCREENRECT.topright).move(-15, 15)
        self._score = 0
        self._to_update = True

    @property
    def score(self):
        return self._score

    @score.setter
    def score(self, val):
        logger.debug(f"Score.score: setting score to {val}")
        self._score = val
        self._to_update = True

    def update(self):
        if self._to_update:
            logger.debug(f"Score.update - {self._to_update} to {self.score}")
            self.image = self.font.render(f"Score: {self.score}", True, self.color)
            self._to_update = False
