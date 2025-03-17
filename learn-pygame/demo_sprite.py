import pygame as pg


class PlaceholderSprite(pg.sprite.Sprite):
    def __init__(self, length, color):
        super().__init__()
        self.image = pg.Surface((length, length)).convert()

        bg = pg.Surface(self.image.get_size()).convert()
        bg.fill(color)
        self.image.blit(bg, (0, 0))

        self.rect = self.image.get_rect()
        self.offset = (-length // 2, -length // 2)
        self.to_update = False

    def update(self):
        if self.to_update:
            pos = pg.mouse.get_pos()
            self.rect.topleft = pos
            self.rect.move_ip(self.offset)


def main():
    pg.init()

    screen = pg.display.set_mode([1280, 480])
    pg.display.set_caption("Game Scratchpad")
    # pg.mouse.set_visible(False)

    background = pg.Surface(screen.get_size())
    background = background.convert()
    background.fill((70, 71, 74))
    # background.set_alpha(0)

    font = pg.font.Font(None, 64)
    text = font.render("Game Scratchpad", True, (250, 250, 250))
    # textpos = text.get_rect(centerx=background.get_width() / 2, y=10)
    textpos = text.get_rect(x=100, y=10)
    background.blit(text, textpos)

    screen.blit(background, (0, 0))
    pg.display.flip()

    sprite = PlaceholderSprite(100, (222, 232, 28))
    allsprites = pg.sprite.Group(sprite)
    clock = pg.time.Clock()

    terminate = False
    while not terminate:
        clock.tick(60)

        for event in pg.event.get():
            match event.type:
                case pg.QUIT:
                    terminate = True
                case pg.KEYDOWN:
                    terminate = event.key == pg.K_ESCAPE
                case pg.MOUSEBUTTONDOWN:
                    sprite.to_update = True
                case pg.MOUSEBUTTONUP:
                    sprite.to_update = False

        allsprites.update()
        screen.blit(background, (0, 0))
        allsprites.draw(screen)
        pg.display.flip()

    pg.quit()


if __name__ == "__main__":
    main()
