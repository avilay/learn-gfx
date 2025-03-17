import pygame as pg
import sys


class Alien(pg.sprite.Sprite):
    def __init__(self, *groups):
        super().__init__(groups)
        self.image = pg.image.load("./assets/alien1.gif")
        self.rect = self.image.get_rect()

    def update(self):
        self.rect.move_ip(10, 0)


def main():
    if len(sys.argv) != 2:
        print("Input a number between 1 and 4 inclusive.")
        sys.exit(1)
    step = int(sys.argv[1])
    pg.init()

    screen = pg.display.set_mode([1280, 480])
    pg.display.set_caption("Game Scratchpad")
    background = pg.Surface(screen.get_size())
    background = background.convert()
    background.fill((255, 255, 255))

    screen.blit(background, (0, 0))
    pg.display.flip()

    alien = Alien()
    grp = pg.sprite.RenderUpdates(alien)
    # dirty = grp.draw(screen)
    # pg.display.update(dirty)

    clock = pg.time.Clock()

    ctr = 0
    terminate = False
    while not terminate:
        for event in pg.event.get():
            match event.type:
                case pg.QUIT:
                    terminate = True
                case pg.MOUSEBUTTONDOWN:
                    if step == 1:
                        print("draw -> display dirty update")
                        dirty = grp.draw(screen)
                        pg.display.update(dirty)
                    elif step == 2:
                        if ctr % 2 == 0:
                            ctr += 1
                            print("draw -> display dirty update")
                            dirty = grp.draw(screen)
                            pg.display.update(dirty)
                        elif ctr % 2 == 1:
                            ctr += 1
                            print("clear -> display update")
                            grp.clear(screen, background)
                            pg.display.update()
                    elif step == 3:
                        # The most typical usage
                        if ctr == 0:
                            ctr += 1
                            print("draw -> display dirty update")
                            dirty = grp.draw(screen)
                            pg.display.update(dirty)
                        elif ctr >= 1:
                            ctr += 1
                            print(
                                "clear -> sprite update -> draw -> display dirty update"
                            )
                            grp.clear(screen, background)
                            grp.update()
                            dirty = grp.draw(screen)
                            pg.display.update(dirty)
        clock.tick(60)


if __name__ == "__main__":
    main()
