# Fractal Render Lab

Explore Mandelbrot views through center/zoom controls and export rendered PNGs.

[![Build and verify](https://github.com/netcodermike/fractal-render-lab/actions/workflows/verify.yml/badge.svg)](https://github.com/netcodermike/fractal-render-lab/actions/workflows/verify.yml)

**Language:** C++ · **Platform:** Windows, macOS, Linux desktop · **App type:** Fractal explorer with image export

First-release learning implementation, with explicit scope below. This is one independently runnable app, not a placeholder in a combined repository.

## Features

- Complex escape-time model
- Center and zoom input
- Native Qt preview
- PNG image export

## Requirements

C++17, CMake 3.16+, and Qt 6 Widgets. Ubuntu: sudo apt-get install qt6-base-dev. On other systems install the matching Qt compiler kit and set CMAKE_PREFIX_PATH.

## Quick start

```sh
git clone https://github.com/netcodermike/fractal-render-lab.git
cd fractal-render-lab
cmake -S . -B build
cmake --build build --config Release
# Linux/macOS: ./build/app
# Windows MSVC: .\build\Release\app.exe
```

Commands run from the repository root. Lines marked for a particular operating system apply only there. Language tools are prerequisites, not installed by the app. Close desktop windows normally; terminal/server apps stop with Ctrl+C unless their usage notes say otherwise.

## Example workflow

Render -0.5,0,1, then -0.75,0.1,10. Export both and compare detail. Try an invalid zoom.

## Architecture, configuration, and data

main.cpp iterates z²+c from zero for each pixel, with a 300-iteration limit and escape radius 2. The 800×500 image uses a cyclic HSV palette and dark interior. Input is centerX,centerY,zoom, bounded to finite centers within ±4 and zoom 1–100000. Tests check known interior/exterior points and nonuniform output.

## Verification

Build with the quick-start command where needed, then run:

```sh
ctest --test-dir build -C Release --output-on-failure
```

Manual acceptance: Render -0.5,0,1, then -0.75,0.1,10. Export both and compare detail. Try an invalid zoom. Also test malformed inputs and an unwritable output destination.

See [validation record](docs/VALIDATION.md) for observed checks and their limits. CI results verify only what the workflow runs; they do not establish native GUI correctness or production readiness.

## Limitations and next steps

No mouse navigation, arbitrary precision, Julia sets, iteration control, antialiasing, smooth coloring, asynchronous rendering, or deep-zoom guarantees. Double precision and fixed iterations limit accuracy. UI blocks during rendering; PNG export replaces the chosen file.

## Troubleshooting

Use the exact platform/toolchain above. Preserve originals and use synthetic fixtures first. Errors are displayed in the UI or stderr. A headless machine can run the model tests but cannot verify native GUI/audio behavior. Output paths are chosen explicitly; keep backups of important data.

## Source map

- `CMakeLists.txt`
- `main.cpp`

## Development and license

Read [contributing](CONTRIBUTING.md) before changing the app, and [security/privacy](SECURITY.md) before supplying private data. Use synthetic fixtures for tests. No telemetry, paid API key, or account is required by the app itself. Dependencies, when present, are stated in Requirements.

[MIT license](LICENSE), copyright 2026 netcodermike.
