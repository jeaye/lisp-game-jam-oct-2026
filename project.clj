(defproject com.jeaye.claw-game "0.1-SNAPSHOT"
  :license {:name "MPL 2.0"
            :url "https://www.mozilla.org/en-US/MPL/2.0/"}
  :dependencies [[org.jank-lang.commons/raylib-sys "2026.10-1"]
                 [org.jank-lang.commons/box2d-sys "2026.10-1"]
                 [org.jank-lang.commons/box2d-draw-sys "2026.10-1"]]
  :build-dependencies [[org.jank-lang.commons/jank-build "2026.10-1"]]
  :plugins [[org.jank-lang/lein-jank "2026.10-3"]]
  :middleware [leiningen.jank/middleware]
  :main com.jeaye.claw-game
  :jank {:include-dirs ["include"]}
  :profiles {:base {:jank {:target-dir "target/debug"
                           :optimization-level 0
                           :eager? true
                           :debug? false}}
             :release {:jank {:target-dir "target/release"
                              :optimization-level 3}}})
