<div align="center">

# 🎮 So Long

<p align="center">
  <img src="assets/so_long.png" alt="So Long Gameplay" width="850">
</p>

**A 2D top-down game built in C using MiniLibX as part of the 1337 / 42 curriculum.**

[![42 School](https://img.shields.io/badge/42-1337_School-000000?style=for-the-badge&logo=42&logoColor=white)](#)
[![Language](https://img.shields.io/badge/Language-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)](#)
[![Graphics](https://img.shields.io/badge/Library-MiniLibX-orange?style=for-the-badge)](#)

</div>

---

## 📌 Overview

**So Long** is a 2D tile-based game where the player navigates a map, collects all available coins, and exits through the gate without getting trapped.

The project processes a `.ber` map file, validating its layout, integrity, and path solvability before initializing graphics and game loops.

### Core Technical Pillars
* 🧩 **Map Parsing & File I/O:** Reading and converting configuration files into in-memory structures.
* 🗺️ **Flood-Fill Algorithm:** Graph traversal to verify level solvability.
* 🎨 **2D Graphics Pipeline:** Tile rendering and sprite composition via MiniLibX.
* 🎮 **Event-Driven Architecture:** Non-blocking hook registration for user inputs and OS signals.
* 🧠 **Defensive Memory Management:** Zero-leak cleanup across error states and execution paths.

---

## 🎯 Game Rules & Mechanics

The core objective is straightforward: **Collect all coins 🪙 and reach the exit 🚪.**

### Map Symbols

| Character | Asset | Description |
| :---: | :---: | :--- |
| `P` | 🧍 | **Player:** Initial spawn position (Exactly 1 required) |
| `C` | 🪙 | **Collectible:** Item required to open exit (1 or more required) |
| `E` | 🚪 | **Exit:** Level finish point (Exactly 1 required) |
| `1` | 🧱 | **Wall:** Unreachable obstacle surrounding the area |
| `0` | 🌱 | **Floor:** Traversible open space |

#### Example Map Layout (`map.ber`):
```text
111111111111
1000C0000001
101111101001
100P00000C01
100001111001
100C0000E001
111111111111
```

---

## 🗺️ Map Validation & Pathfinding

Before graphical initialization, the map undergoes multi-stage structural and algorithmic verification.

### Validation Rules
- [x] Must be fully enclosed by walls (`1`).
- [x] Must be rectangular in shape.
- [x] Must contain **exactly one** Player (`P`) and **one** Exit (`E`).
- [x] Must contain **at least one** Collectible (`C`).
- [x] Must contain no unknown characters.
- [x] **Path Validation:** All collectibles (`C`) and the exit (`E`) must be accessible from `P`.

### Parsing & Validation Flow

```text
       .ber file
           │
           ▼
     Read Map File (gnl)
           │
           ▼
    Parse Grid Data
           │
           ▼
   Validate Dimensions & Walls
           │
           ▼
   Count Entities (P, C, E)
           │
           ▼
  Flood-Fill Path Verification
           │
     ┌─────┴─────┐
     │           │
     ▼           ▼
  [Error]   [Start Game]
 (Exit safe)  (Launch window)
```

### Flood-Fill Exploration

```text
Player (Start)
  │
  ├──► Reachable Collectible 1  [✓]
  ├──► Reachable Collectible 2  [✓]
  ├──► Reachable Collectible 3  [✓]
  │
  └──► Reachable Exit           [✓]
```

> **Note:** If any collectible or the exit remains unvisited after exhaustive traversal, the program frees all allocated structures and exits gracefully with an explicit error.

---

## 🎨 MiniLibX & Event Architecture

The project relies on **MiniLibX**, an X-Window / Cocoa abstraction library, to handle rendering and OS event dispatching.

### Core API Usage

| Function | Role |
| :--- | :--- |
| `mlx_init()` | Establishes connection to the underlying display system. |
| `mlx_new_window()` | Allocates a dedicated rendering window on screen. |
| `mlx_xpm_file_to_image()` | Decodes and loads raw XPM assets into image buffers. |
| `mlx_put_image_to_window()` | Pushes rasterized tiles directly to window coordinates. |
| `mlx_key_hook()` / `mlx_hook()` | Binds keyboard actions and window events (`DestroyNotify`). |
| `mlx_loop()` | Runs the main event listener loop. |

### Event Lifecycle

```text
User Event (Key / Close Button)
           │
           ▼
    MiniLibX Hook
           │
           ▼
     Event Handler
           │
           ▼
   State & Position Logic
           │
           ▼
     Buffer Re-render
```

---

## 🛠️ Step-by-Step Architecture

```text
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│  01. PARSING │ ──► │02. VALIDATION│ ──► │03. ALLOCATION│
│  Read .ber   │     │  Flood Fill  │     │ Setup Structs│
└──────────────┘     └──────────────┘     └──────────────┘
                                                 │
                                                 ▼
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│ 06. CLEANUP  │ ◄── │05. GAME LOOP │ ◄── │04. RENDERING │
│ Free Memory  │     │Events & State│     │   MiniLibX   │
└──────────────┘     └──────────────┘     └──────────────┘
```

1. **Parsing:** Reads the file descriptor line by line, loading characters into a 2D matrix.
2. **Validation:** Checks structural boundaries, entity counts, and flood-fill reachability.
3. **Allocation:** Instantiates the primary `t_game` context and registers state variables.
4. **Rendering:** Maps characters (`1`, `0`, `P`, `C`, `E`) to their respective XPM sprites.
5. **Game Loop:** Tracks step counts, collectible collection, victory triggers, and input hooks.
6. **Cleanup:** Unloads textures, destroys the display/window, and deallocates matrices cleanly.

---

## 🎮 Controls

| Key Bindings | Action |
| :---: | :--- |
| <kbd>W</kbd> / <kbd>↑</kbd> | Move Character Up |
| <kbd>A</kbd> / <kbd>←</kbd> | Move Character Left |
| <kbd>S</kbd> / <kbd>↓</kbd> | Move Character Down |
| <kbd>D</kbd> / <kbd>→</kbd> | Move Character Right |
| <kbd>ESC</kbd> | Close game cleanly |
| <kbd>✕</kbd> | Window close event |

---

## 🚀 Getting Started

### Prerequisites
* GCC or Clang compiler
* MiniLibX dependencies (X11 / OpenGL / AppKit depending on OS)
* Make

### Installation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/so_long.git](https://github.com/your-username/so_long.git)
   cd so_long
   ```

2. **Compile the binary:**
   ```bash
   make
   ```

3. **Run with a valid map:**
   ```bash
   ./so_long maps/valid/map_default.ber
   ```

---

## 📁 Repository Structure

```text
so_long/
├── assets/         # Sprites and XPM game textures
├── include/        # Header definitions (so_long.h)
├── maps/           # Valid and invalid test maps (.ber)
│   ├── valid/
│   └── invalid/
├── src/            # Source implementation files
│   ├── parsing/    # File reading & matrix creation
│   ├── validation/ # Map rules & flood-fill verification
│   ├── graphics/   # MiniLibX window and sprite rendering
│   ├── events/     # Key hooks & movement validation
│   └── utils/      # Memory cleanup & string helpers
├── Makefile        # Compilation target rules
└── README.md
```

---

<div align="center">
  <sub>Built with precision as part of the 1337 / 42 Network Common Core.</sub>
</div>
