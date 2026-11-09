# shapewave
This is a submission to the Autumn Lisp Game Jam 2026. Control the claw, ride the waves, bucket the shapes, rack up your score, and prioritize the white bonus pieces to gain more time. Enter the shapewave!

CONTROLS

A controller (PlayStation, Xbox, etc) is required.

* R2/L2 (or equivalent) - Close the corresponding claw arm
* Left stick - Move the claw carriage
* Right stick - Tilt the claw carriage

The game is written in jank, the native Clojure dialect with seamless C++ interop. The source repository is here. shapewave was written by Bryan Chacosky and Jeaye Wilkerson.

DEPENDENCIES

 jank (build and run time)
 raylib (run time)
 box2d (run time)
 Leiningen (build time)
 babashka (build time)

## Compiling
* Install jank: https://book.jank-lang.org/getting-started/01-installation.html
* Install game dependencies

```bash
sudo apt install leiningen cmake libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl-dev
```

* Launch the game with `lein run`
* AOT compile the game for release with `lein with-profile +release compile`
