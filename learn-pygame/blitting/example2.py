import pygame as pg


def main():
    pg.init()

    screen = pg.display.set_mode((1024, 1024))

    img = pg.image.load("./landscape.jpeg")
    # The original image is 1024 x 1024
    img = pg.transform.scale(img, (512, 512))
    img = img.convert()

    screen.blit(img, (100, 100))

    pg.display.update()

    terminate = False
    clock = pg.time.Clock()
    while not terminate:
        clock.tick(15)

        for event in pg.event.get():
            if event.type == pg.QUIT:
                terminate = True

        pg.event.pump()


if __name__ == "__main__":
    main()
