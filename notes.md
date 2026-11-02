## TODO
* Fun
  * [bryan] Scoring
  * [jeaye] Claw rotation
  * [jeaye] Controller vibrations
  * [jeaye] Thrust
    * Build up thrust bar based on scoring?
  * [bryan] Bonus piece, rather than type
    * Bonus shouldn't be something you get without trying
  * [bryan] Non-uniform pieces
    * Stars
    * Moon
    * Large shapes (each shape has variance)
    * Long rectangles
  * Dump more pieces when the piece count gets low
  * Bad pieces?
    * Bombs that explode and destroy other pieces?
      * Explodes after a certain amount of time
      * Destroys pieces next to it?
      * Can be bucketed for points, deactivating it
    * Spiky pieces that stick to the claw
    * Heavy pieces which weigh down the claw
* [bryan] UI
  * Maybe gamepad selection?
  * Coin drop scene
    * ENTER A COIN TO START
  * Countdown before gameplay (3 2 1)
    * Can still move claw during this?
  * Gameplay
    * Score and time at the top of the playspace
  * Pause menu
  * Game over
    * Show stats
      * Time spent
      * Score
      * Pieces collected
      * Largest combo
      * Thrusts used
      * Bonuses
      * Bombs defused / exploded
    * Restarting goes back to coin drop
* [jeaye] Rendering
  * Claw
  * Pieces
  * Bucket
  * Playspace border
* [bryan] Audio
  * Background music
  * Claw scraping
  * Claw open/closing
  * Piece interactions
  * Scoring
  * Game over
* [jeaye] Special effects
  * Bloom/glow for the pieces
  * Scoring effect (confetti?)
  * Claw scraping sparks
  * Bonus piece lets you know that it's special
* Up in the air
  * Easy screenshotting?
  * Options robustness
    * KBM
    * Controller selection
    * Resolution selection
    * Volume
  * In-game REPL
    * Exploration of code and data
    * Might as well let them change everything
  * Is there anything that helps us demonstrate jank?

## Issues
### jank
* Terminal output from other threads ends up clogging EVERY REPL output
* Trait conversion type matching is annoying
* No uniform initialization for arrays
* `case` can't return native types
* Missing trait conversions for `cpp/=` arg
* Compilation time affects physics and is generally quite slow, even one fn at a
  time
* AOT compilation with `cpp/raw` conversion traits causes some issues
  * We're not producing AOT codegen in such a way that allows our modules to
    take advantage of the compiled C++. The main difference is that the JIT
    compilation is effectively done as one translation unit, so every cpp/raw
    from every namespace comes together and is available. But with how C++
    compiles, each translation unit is separate, so if you do a cpp/raw in one
    namespace, that C++ won't be available to every other namespace that
    includes that one.
* We can't use a `jank-build.bb` to add a top-level `include` path
  * We assume that relative dirs are under `*out*`
  * We don't provide an input for the project dir
* The lack of LSP makes both Clojure and C++ work so bothersome

### Box2D
* API search box doesn't do anything (firefox and chromium)
* b2MakeCircle would be nice
  * https://github.com/erincatto/box2d/discussions/903
* Ghost collisions doc has a cut off image
  * https://box2d.org/documentation/md_collision.html
* Hello Box2D docs have incorrect `!caution` blocks
  * https://box2d.org/documentation/hello.html
* The doc page cannot expand the arrow of a page unless that page is current
  * This makes searching the tree more cumbersome, especially since the search
    bar doesn't work
