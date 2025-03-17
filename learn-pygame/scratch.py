import pygame as pg


class Alien(pg.sprite.Sprite):
    def __init__(self, name, screen_rect, *groups):
        super().__init__(*groups)
        self.name = name
        self.image = pg.image.load("./assets/alien1.gif")
        self.rect = self.image.get_rect()
        self._screen_rect = screen_rect
        self._direction = 1

    def update(self):
        self.rect.move_ip(self._direction * 5, 0)
        if not self._screen_rect.contains(self.rect):
            self._direction = -1 * self._direction
            self.rect.top = self.rect.top + 10
            self.rect = self.rect.clamp(self._screen_rect)


class Score(pg.sprite.Sprite):
    def __init__(self, screen_rect, *groups):
        super().__init__(*groups)
        self.font = pg.font.Font(None, 32)
        self.image = self.font.render("Score: 0", True, "black")
        self.rect = self.image.get_rect(topright=screen_rect.topright).move(-20, 20)
        self._score = 0
        self._to_update = True

    @property
    def score(self):
        return self._score

    @score.setter
    def score(self, val):
        print(f"Score.score: setting score to {val}")
        self._score = val
        self._to_update = True

    def update(self):
        if self._to_update:
            print(f"Score.update: score = {self._score}")
            self.image = self.font.render(f"Score: {self._score}", True, "black")
            self._to_update = False


def main():
    pg.init()

    screen = pg.display.set_mode([1280, 480])
    pg.display.set_caption("PyGame Main")
    background = pg.Surface(screen.get_size())
    background.convert()
    background.fill((255, 255, 255))
    screen.blit(background, (0, 0))
    pg.display.flip()

    sprites = pg.sprite.RenderUpdates()
    Alien("alien: 0", screen.get_rect(), sprites)
    score = Score(screen.get_rect(), sprites)

    terminate = False
    clock = pg.time.Clock()
    while not terminate:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                print("Terminating")
                terminate = True
                score.score = score.score + 5
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                print("Terminating")
                score.score = score.score + 5
                terminate = True
            if event.type == pg.MOUSEBUTTONDOWN:
                # score.score = score.score + 1
                score.score += 1

        sprites.clear(screen, background)
        sprites.update()
        dirty = sprites.draw(screen)
        pg.display.update(dirty)

        clock.tick(60)

    print("Ending screen")
    terminate = False
    clock = pg.time.Clock()
    while not terminate:
        pg.event.pump()
        for event in pg.event.get():
            if event.type == pg.QUIT:
                terminate = True
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                terminate = True

        clock.tick(10)


if __name__ == "__main__":
    main()
