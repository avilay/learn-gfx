import pygame as pg


def main():
    pg.init()

    screen = pg.display.set_mode((1024, 1024))

    img = pg.image.load("./landscape.jpeg")
    # The original image is 1024 x 1024
    img = pg.transform.scale(img, (512, 512))
    img = img.convert()

    img_rect = img.get_rect(x=128, y=128, width=200, height=300)

    screen.blit(img, (0, 0), img_rect)

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
