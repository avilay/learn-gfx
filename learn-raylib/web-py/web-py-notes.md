# Web Py Notes

A couple of caveats when using pygbag build -
  * The default CDN JS/WASM provider https://pygame-web.github.io/archives/0.9/ does not work. I will need to override it with https://pygame-web.github.io/pygbag/0.0/.
  * Python 3.13 does not seem to be supported, not sure whether it is a pygbag limitation or pyscript. Best to use 3.12.
  * OGG is the preferred sound encoding, wav files seem to work be result in a warning from pygbag.
  * It generates a `*-pygbag.py` file for every file - code or resource - that it needs to package.
  * It does something very funky - in `game.py` I am attempting to laod a `sound.wav` file but it does not exist in my resources dir. However, the generaqted `game-pygbag.py` replaces the string "sound.wav" with "sound.ogg"!!
  * It takes a while for the sound to be initialized.
