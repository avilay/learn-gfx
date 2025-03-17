import pygame as pg


def main():
    pg.init()

    screen = pg.display.set_mode((1280, 480))
    font = pg.font.Font(None, 64)
    text = font.render("Pummel The Chimp and Win $$$", True, (255, 255, 255))
    rect = text.get_rect()
    print(f"initial rect = {rect}, centerx = {rect.centerx}")
    rect.centerx = 1280 / 2
    rect.y = 10
    print(f"final rect = {rect}, centerx = {rect.centerx}")
    screen.blit(text, rect)
    pg.display.update()

    terminate = False
    while not terminate:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                terminate = True

        pg.event.pump()


if __name__ == "__main__":
    main()
