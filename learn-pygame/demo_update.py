import pygame as pg


DARK_GRAY = (70, 71, 74)
YELLOW = (222, 232, 28)
BLUE = (31, 182, 237)


def main():
    # Initialize pygame
    pg.init()
    screen = pg.display.set_mode((1000, 500))
    pg.display.set_caption("Scratch")

    # Build the yellow "sprite"
    # This will be static on the screen
    yellow = pg.Surface((100, 100))
    fill = pg.Surface(yellow.get_size())
    fill.convert()
    fill.fill(YELLOW)
    yellow.blit(fill, (0, 0))

    # Build the screen background
    # It is a gray block with the yellow sprite on it
    bg = pg.Surface(screen.get_size())
    bg.convert()
    bg.fill(DARK_GRAY)
    bg.blit(yellow, (100, 100))

    # Build the blue sprite
    # This will move diagonally on the screen
    blue = pg.Surface((100, 100))
    fill = pg.Surface(blue.get_size())
    fill.convert()
    fill.fill(BLUE)
    blue.blit(fill)

    # Draw the background on the screen
    screen.blit(bg, (0, 0))

    # "Draw" the blue sprite on the screen
    # This is what the Sprite.draw method internally
    blue_rect = blue.get_rect()
    screen.blit(blue, blue_rect.topleft)

    # Render the new screen
    pg.display.flip()

    clock = pg.time.Clock()
    terminate = False
    while not terminate:
        # Set the framerate to 30fps
        clock.tick(30)

        # Get any user input
        for event in pg.event.get():
            if event.type == pg.QUIT:
                terminate = True

        # "Erase" the existing blue sprite by replacing its current
        # position with whatever is in the background at these coords.
        screen.blit(bg, blue_rect.topleft, blue_rect)

        # Move the blue sprite
        blue_rect.topleft = blue_rect.topleft[0] + 1, blue_rect.topleft[1] + 1

        # Draw the blue sprite
        screen.blit(blue, blue_rect.topleft)

        # Render the new screen
        pg.display.flip()


if __name__ == "__main__":
    main()
