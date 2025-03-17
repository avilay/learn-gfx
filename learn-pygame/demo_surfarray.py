import pygame as pg

# import numpy as np
import pygame.surfarray as sa


def main():
    pg.init()

    img = pg.image.load("./blitting/landscape.jpeg")
    imgarr = sa.array3d(img)
    print(imgarr.shape)


if __name__ == "__main__":
    main()
