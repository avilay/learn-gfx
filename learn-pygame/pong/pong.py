"""
The game play turned out to be terrible. But keeping this code as it has a bunch
of good API calls that I need to familiarize myself with.
"""

import math
from pathlib import Path

import pygame as pg

rootdir = Path("/home/avilay/projects/bitbucket/learn/learn-gfx/learn-pygame/pong")
assetsdir = rootdir / "assets"


def radians_to_degrees(angle):
    return angle * 180 / math.pi


def degrees_to_radians(angle):
    return angle * math.pi / 180


class Ball(pg.sprite.Sprite):
    def __init__(self, vector):
        super().__init__()

        image = pg.image.load(assetsdir / "ball.gif")
        self.image = image.convert_alpha() if image.get_alpha() else image.convert()
        self.rect = self.image.get_rect()

        screen = pg.display.get_surface()
        self.area = screen.get_rect()
        self.vector = vector
        self.hit = False

    def update(self):
        newpos = self.calcnewpos(self.rect, self.vector)
        self.rect = newpos
        (angle, z) = self.vector

        if not self.area.contains(newpos):
            tl = not self.area.collidepoint(newpos.topleft)
            tr = not self.area.collidepoint(newpos.topright)
            bl = not self.area.collidepoint(newpos.bottomleft)
            br = not self.area.collidepoint(newpos.bottomright)
            if (tr and tl) or (br and bl):
                angle = -angle
            if tl and bl:
                angle = math.pi - angle
            if tr and br:
                angle = math.pi - angle
        else:
            player1.rect.inflate(-3, -3)
            player2.rect.inflate(-3, -3)

            if self.rect.colliderect(player1.rect) and not self.hit:
                angle = math.pi - angle
                self.hit = not self.hit
            elif self.rect.colliderect(player2.rect) and self.hit:
                angle = math.pi - angle
                self.hit = not self.hit
            elif self.hit:
                self.hit = not self.hit

        self.vector = (angle, z)

    def calcnewpos(self, rect, vector):
        (angle, z) = vector
        (dx, dy) = (z * math.cos(angle), z * math.sin(angle))
        return rect.move(dx, dy)


class Bat(pg.sprite.Sprite):
    def __init__(self, side):
        super().__init__()

        image = pg.image.load(assetsdir / "bat.png")
        self.image = image.convert_alpha() if image.get_alpha() else image.convert()
        self.rect = self.image.get_rect()

        screen = pg.display.get_surface()
        self.area = screen.get_rect()
        self.side = side
        self.speed = 10
        self.state = "still"
        self.reinit()

    def reinit(self):
        self.state = "still"
        self.movepos = [0, 0]
        if self.side == "left":
            self.rect.midleft = self.area.midleft
        elif self.side == "right":
            self.rect.midright = self.area.midright

    def update(self):
        newpos = self.rect.move(self.movepos)
        if self.area.contains(newpos):
            self.rect = newpos
        pg.event.pump()

    def moveup(self):
        self.movepos[1] = self.movepos[1] - self.speed
        self.state = "moveup"

    def movedown(self):
        self.movepos[1] = self.movepos[1] + self.speed
        self.state = "movedown"


def run_game_loop(bg, ball, ballsprite, batsprites):
    clock = pg.time.Clock()
    screen = pg.display.get_surface()

    while True:
        clock.tick(60)

        for event in pg.event.get():
            match event.type:
                case pg.QUIT:
                    return
                case pg.KEYDOWN:
                    if event.key == pg.K_UP:
                        player2.moveup()
                    elif event.key == pg.K_DOWN:
                        player2.movedown()
                    elif event.key == pg.K_a:
                        player1.moveup()
                    elif event.key == pg.K_z:
                        player1.movedown()
                case pg.KEYUP:
                    if event.key == pg.K_UP or event.key == pg.K_DOWN:
                        player2.movepos = [0, 0]
                        player2.state = "still"
                    elif event.key == pg.K_a or event.key == pg.K_z:
                        player1.movepos = [0, 0]
                        player1.state = "still"

        screen.blit(bg, ball.rect, ball.rect)
        screen.blit(bg, player1.rect, player1.rect)
        screen.blit(bg, player2.rect, player2.rect)
        ballsprite.update()
        batsprites.update()
        ballsprite.draw(screen)
        batsprites.draw(screen)

        pg.display.flip()


def main():
    pg.init()
    screen = pg.display.set_mode((640, 480), pg.SCALED)
    pg.display.set_caption("Pong")

    bg = pg.Surface(screen.get_size())
    bg = bg.convert()
    bg.fill((0, 0, 0))

    global player1
    global player2
    player1 = Bat("left")
    player2 = Bat("right")

    speed = 13
    ball = Ball((0.47, speed))

    batsprites = pg.sprite.Group(player1, player2)
    ballsprite = pg.sprite.Group(ball)

    screen.blit(bg, (0, 0))
    pg.display.flip()

    run_game_loop(bg, ball, ballsprite, batsprites)
    pg.quit()


if __name__ == "__main__":
    main()
