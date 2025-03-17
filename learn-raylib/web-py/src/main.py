import asyncio
import platform
import sys

from pyray import *
from pathlib import Path
import web_py.game as game


def native():
    game.initialize(Path("./resources"))
    while not window_should_close():
        game.loop()
    close_window()


async def web():
    game.initialize(Path("./resources"))
    platform.window.window_resize()
    while not window_should_close():
        game.loop()
        await asyncio.sleep(0)
    close_window()


if sys.platform == "emscripten":
    asyncio.run(web())
else:
    native()
