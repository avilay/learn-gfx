import logging
import random

import pygame as pg

import aliens.consts as k
from aliens.sprites import Alien, Player, Shot, Bomb, Explosion
from aliens.score import Score
from aliens.utils import Direction

logging.basicConfig(level=logging.WARN)
logger = logging.getLogger(__name__)


def main():
    pg.mixer.pre_init(44100, 32, 2, 1024)
    pg.init()

    # Set up the game window
    screen = pg.display.set_mode(k.SCREENRECT.size)
    icon_img = pg.transform.scale(
        pg.image.load(str(k.ASSETS_HOME / "alien1.gif")), (32, 32)
    )
    pg.display.set_icon(icon_img)
    pg.display.set_caption("Aliens 👽")
    pg.mouse.set_visible(False)

    # background tile is a vertical strip that has to be replicated across the
    # entire width of the screen. First I'll create a background surface with
    # the tile replicated, and then I'll blit the entire surface onto the screen.
    # TODO: What is the benefit of doing this way as opposed to blitting the tile
    # onto the screen directly?
    background_tile = pg.image.load(str(k.ASSETS_HOME / "background.gif"))
    background = pg.Surface(k.SCREENRECT.size)
    for x in range(0, k.SCREENRECT.width, background_tile.get_width()):
        background.blit(background_tile, (x, 0))
    screen.blit(background, (0, 0))

    # Set up the sounds.
    boom_sound = pg.mixer.Sound(str(k.ASSETS_HOME / "boom.wav"))
    shoot_sound = pg.mixer.Sound(str(k.ASSETS_HOME / "shot.wav"))
    pg.mixer.music.load(str(k.ASSETS_HOME / "house_lo.wav"))
    pg.mixer.music.play(-1)

    pg.display.flip()

    all = pg.sprite.RenderUpdates()

    score = Score(all)

    player = Player(all)

    aliens = pg.sprite.Group()
    last_alien = pg.sprite.GroupSingle()
    Alien(aliens, all, last_alien)
    n_frames_after_alien_respawn = 0

    bombs = pg.sprite.Group()
    n_frames_after_bomb = 0

    shots = pg.sprite.Group()

    clock = pg.time.Clock()
    frame_count = 0

    # Sprite.alive checks whether or not the sprite is part of any group
    while player.alive():
        for event in pg.event.get():
            if event.type == pg.QUIT:
                player.kill()
            elif event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                player.kill()
        keystate = pg.key.get_pressed()

        # Player is updated as part of the move method. Even though it is called
        # in every frame, the move impl. is such that it will only have any effect
        # if the direction is non-zero.
        direction = Direction.from_value(keystate[pg.K_RIGHT] - keystate[pg.K_LEFT])
        player.move(direction)

        # Using player.reloading and MAX_SHOTS is a good way to ensure that shots
        # are only fired every few frames. Without this check the shots will look
        # like a continuous stream.
        firing = keystate[pg.K_SPACE]
        if not player.reloading and firing and len(shots) < k.MAX_SHOTS:
            logger.debug(f"[{frame_count}]: Shot fired.")
            Shot(player.gunpos(), shots, all)
            shoot_sound.play()
        player.reloading = firing

        # After at least {MIN_FRAMES_ALIEN_RESPAWN} frames, respawn an alien
        # with {PROB_ALIEN_RESPAWN}% probablity.
        # The newly spawned alien becomes the last alien
        if n_frames_after_alien_respawn < k.MIN_FRAMES_ALIEN_RESPAWN:
            n_frames_after_alien_respawn += 1
        else:
            prob = random.random()
            if prob < k.PROB_ALIEN_RESPAWN:
                Alien(aliens, all, last_alien)
                n_frames_after_alien_respawn = 0
                logger.debug(f"[{frame_count}]: prob = {prob} spawning alien.")

        # Drop bomb - use the same trick as above to ensure that bombs are dropped
        # only every few frames.
        if n_frames_after_bomb < k.MIN_FRAMES_BOMB:
            n_frames_after_bomb += 1
        else:
            if aliens and random.random() < k.PROB_BOMB:
                # The bomb ctor is a bit weird, it needs the groups that it belongs
                # to like all other sprite ctors, but it also needs the group it
                # should pass along to the Explosion ctor in case the bomb reaches
                # the ground without impacting anything and has to explode on its own.

                # Using last_alien to demo usage of GroupSingle, otherwise I'd
                # do something like choosing an alien at random.
                # chosen_alien = aliens.sprites()[random.randint(0, len(aliens) - 1)]
                chosen_alien = last_alien.sprite
                if chosen_alien:
                    Bomb(chosen_alien, all, bombs, all)
                    n_frames_after_bomb = 0

        # Detect collisions between aliens and player
        collided_aliens = pg.sprite.spritecollide(
            sprite=player, group=aliens, dokill=True
        )
        for alien in collided_aliens:
            boom_sound.play()
            Explosion(alien, all)
            Explosion(player, all)
            score.score = score.score + 1
            player.kill()

        # Detect if shots hit aliens
        collided_aliens = pg.sprite.groupcollide(
            groupa=aliens, groupb=shots, dokilla=True, dokillb=True
        ).keys()
        for alien in collided_aliens:
            boom_sound.play()
            Explosion(alien, all)
            score.score += 1

        # Detect if bombs hit player
        hit_bombs = pg.sprite.spritecollide(player, bombs, dokill=True)
        for bomb in hit_bombs:
            boom_sound.play()
            Explosion(player, all)
            Explosion(bomb, all)
            player.kill()

        # Do the usual of 1) clear, 2) sprite update, 3) draw, 4) display update
        # Even though player is part of all, it will not be updated because it
        # does not implement the update method. Only aliens, shots, and explosions
        # will be updated.
        all.clear(screen, background)
        all.update()
        dirty = all.draw(screen)
        pg.display.update(dirty)

        frame_count += 1
        clock.tick(60)

    font = pg.font.Font(None, 64)
    game_over = font.render("Game Over", True, (255, 0, 0))
    rect = game_over.get_rect(center=k.SCREENRECT.center)
    screen.blit(game_over, rect)
    pg.display.flip()

    terminate = False
    clock = pg.time.Clock()
    while not terminate:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                terminate = True
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                terminate = True
        clock.tick(10)
        pg.event.pump()


if __name__ == "__main__":
    main()
