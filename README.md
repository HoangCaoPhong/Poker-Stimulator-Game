# Poker Simulator

Poker Simulator is a cross-platform desktop poker demo written in modern C++ and rendered with SFML. The current game presents two five-card hands, evaluates them using standard poker rules, and shows the result on an interactive table.

## Highlights

- Native desktop rendering with SFML graphics, window, and input modules.
- A shuffled 52-card deck and complete five-card hand evaluation, including tie breakers.
- Responsive card-table interface with mouse and keyboard controls.
- CMake-based builds for Linux and Windows, with automated checks for both platforms.
- A small, independently testable game domain separated from the SFML presentation layer.

## Requirements

- CMake 3.21 or newer
- A C++17 compiler
- Git, when allowing CMake to fetch SFML automatically

SFML 2.5+ is used. CMake first looks for a system installation and otherwise downloads the pinned SFML 2.6.1 source during configuration. On Linux, install the usual OpenGL, X11, Xrandr, Xcursor, Xi, and UDev development packages before configuring.

## Build and run

### Linux

```bash
sudo dnf install cmake gcc-c++ libX11-devel libXrandr-devel libXcursor-devel libXi-devel mesa-libGL-devel systemd-devel
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/poker_simulator
```

On Debian or Ubuntu, replace the package command with:

```bash
sudo apt install cmake g++ libx11-dev libxrandr-dev libxcursor-dev libxi-dev libgl1-mesa-dev libudev-dev libfreetype6-dev libjpeg-dev
```

### Windows

Open a Developer PowerShell for Visual Studio:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
.\build\Release\poker_simulator.exe
```

The build copies the required game assets and SFML runtime libraries beside the executable. The resulting build output is therefore the starting point for a platform-specific release folder.

### Tests

```bash
cmake -S . -B build -DPOKER_BUILD_TESTS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Controls

- **Deal / Space / Enter**: deal a new round.
- **Escape**: close the game.

## Project layout

```text
assets/           Runtime assets packaged next to the game
docs/             Historical project documentation
include/poker/    Public C++ headers
src/domain/       Deck and hand-evaluation logic
src/ui/           SFML application and rendering
tests/            Automated domain tests
legacy/           Preserved original console implementation, excluded from builds
.github/          Continuous-integration workflows
```

## Distribution

Use the `Release` build output as the distributable directory: it contains the executable and `assets/`. For a Windows release, build on Windows; for a Linux release, build on Linux. This ensures each package contains binaries and runtime dependencies for its target operating system.

## License

This project is licensed under the Apache License 2.0. See [LICENSE](LICENSE).
