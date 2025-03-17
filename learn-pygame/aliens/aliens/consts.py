import pygame as pg
from pathlib import Path

SCREENRECT = pg.Rect(0, 0, 640, 480)
ASSETS_HOME = Path(__file__).parent / "assets"

MAX_SHOTS = 2  # Max number of player bullets on screen

# minimum number of frames between bombs
MIN_FRAMES_BOMB = 150
# Probability of dropping a bomb in a frame
PROB_BOMB = 0.2

# minimum number of frames between alien respawns
MIN_FRAMES_ALIEN_RESPAWN = 100
# Probablity of spawning an alien in a frame
PROB_ALIEN_RESPAWN = 0.3
