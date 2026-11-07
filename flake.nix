{
  description = "Dev environment for jank commons.";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    jank.url = "git+https://github.com/jank-lang/jank?submodules=1";
    nixpkgs.follows = "jank/nixpkgs";
    self.submodules = true;
  };

  outputs = inputs @ {flake-parts, ...}:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "aarch64-darwin"
        "x86_64-darwin"
      ];
      perSystem = {
        pkgs,
        inputs',
        lib,
        ...
      }: let
        # Commons builds these packages, so include their transitive
        # dependencies.
        commonsTransitive = with pkgs; [
          box2d
          ftxui
          glm
          imgui
          raygui
          raylib
          sdl3
        ];
        # Commons depends on these packages directly (probably via pkg-config).
        commonsDirect = with pkgs; [
          libGL
          glfw3
          ncurses
          sqlite
        ];
        # Audio backends. raylib's miniaudio dlopen()s these at runtime, so
        # they must be on LD_LIBRARY_PATH or it silently falls back to the
        # Null backend (no sound). Linux only; macOS uses CoreAudio.
        audioLibs = lib.optionals pkgs.stdenv.hostPlatform.isLinux (with pkgs; [
          libpulseaudio
          alsa-lib
        ]);
      in {
        legacyPackages = pkgs;
        formatter = pkgs.alejandra;

        devShells.default = pkgs.mkShell {
          inputsFrom = commonsTransitive;
          packages = with pkgs;
            [
              ## Jank
              inputs'.jank.packages.default

              ## Build tools.
              git-lfs
              cmake
              ninja
              pkg-config
              leiningen
              babashka
              bubblewrap

              ## Linting.
              clj-kondo
              shellcheck

              ## Debugging.
              gdb
            ]
            ++ commonsDirect
            ++ audioLibs;

          # Append rather than overwrite, in case something else sets it.
          shellHook = lib.optionalString pkgs.stdenv.hostPlatform.isLinux ''
            export LD_LIBRARY_PATH="${lib.makeLibraryPath audioLibs}''${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
          '';
        };
      };
    };
}
