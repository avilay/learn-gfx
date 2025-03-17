from pyray import *
from pathlib import Path
from typing import Optional

# fx_wav: Sound | None = None
fx_wav = None
fx_ogg = None
logo = None

err_msg_1 = "error message one placeholder"
err_msg_2 = "error message two placeholder"
err_msg_3 = "error message three placeholder"


def initialize(resource_root):
    init_window(576, 768, "Web Py")
    init_audio_device()

    global fx_wav
    sound_wav = resource_root / "sound.wav"
    if sound_wav.exists():
        fx_wav = load_sound(str(sound_wav))
    else:
        global err_msg_1
        err_msg_1 = f"{sound_wav} does not exist"

    global fx_ogg
    target_ogg = resource_root / "target.ogg"
    if target_ogg.exists():
        fx_ogg = load_sound(str(target_ogg))
    else:
        global err_msg_2
        err_msg_2 = f"{target_ogg} does not exist!"

    global logo
    logo_file = resource_root / "raylib_logo.png"
    if logo_file.exists():
        logo = load_texture(str(logo_file))
    else:
        global err_msg_3
        err_msg_3 = f"{logo_file} does not exist!"

    set_target_fps(30)


def loop():
    # noinspection PyUnresolvedReferences
    if is_key_pressed(KEY_SPACE) and fx_wav:
        play_sound(fx_wav)
    # noinspection PyUnresolvedReferences
    if is_key_pressed(KEY_ENTER) and fx_ogg:
        play_sound(fx_ogg)

    begin_drawing()
    clear_background(WHITE)

    draw_text(err_msg_1, 20, 20, 20, RED)
    draw_text(err_msg_2, 20, 50, 20, RED)
    draw_text(err_msg_3, 20, 80, 20, RED)

    draw_text("Press SPACE to play wav", 100, 200, 30, DARKBLUE)
    draw_text("Press ENTER to play ogg", 100, 230, 30, VIOLET)
    draw_texture(logo, 300 - logo.width, 550 - logo.height, WHITE)

    end_drawing()
