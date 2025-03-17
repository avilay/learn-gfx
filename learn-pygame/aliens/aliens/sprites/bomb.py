import pygame as pg
import aliens.consts as k


def load_explosion_images():
    img = pg.image.load(str(k.ASSETS_HOME / "explosion1.gif"))
    flipped_img = pg.transform.flip(img, flip_x=True, flip_y=True)
    return [img, flipped_img]


class Explosion(pg.sprite.Sprite):
    # class properties true for all explosions
    default_life = 12
    anim_cycle = 3
    images = load_explosion_images()

    def __init__(self, actor, *groups):
        super().__init__(*groups)
        self.image = Explosion.images[0]
        self.rect = self.image.get_rect(center=actor.rect.center)
        self.life = Explosion.default_life

    def update(self):
        self.life -= 1
        self.image = self.images[self.life // Explosion.anim_cycle % 2]
        if self.life <= 0:
            self.kill()


class Bomb(pg.sprite.Sprite):
    # class properties true for all bombs
    speed = 2
    images = [pg.image.load(str(k.ASSETS_HOME / "bomb.gif"))]

    def __init__(self, alien, explosion_group, *groups):
        super().__init__(*groups)
        self.image = Bomb.images[0]
        self.rect = self.image.get_rect(midbottom=alien.rect.move(0, 5).midbottom)
        self.explosion_group = explosion_group

    def update(self):
        self.rect.move_ip(0, Bomb.speed)
        if self.rect.bottom >= 470:
            Explosion(self, self.explosion_group)
            self.kill()
