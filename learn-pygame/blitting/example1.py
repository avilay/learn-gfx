import pygame as pg


def main():
    pg.init()

    screen = pg.display.set_mode((1024, 1024))

    image = pg.image.load("./landscape.jpeg")
    # The original image is 1024 x 1024
    image = pg.transform.scale(image, (512, 512))
    image = image.convert()
    rect = image.get_rect()
    print(f"Image rect: {rect}")

    # This will just paste the image to the top-left of the screen
    # screen.blit(image, (0, 0))
    screen.blit(image, rect)

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
