<p align="center">
  <img src="assets/so_long.png" alt="So Long Gameplay" width="800">
</p>

🎮So Long is a 2D game developed as part of the 1337 / 42 curriculum.

The project focuses on learning how to parse and validate a map, work with graphical libraries, handle events, manage game state, and build a simple playable 2D game from scratch using C and MiniLibX.

The game starts by reading a .ber map file. Before launching the graphical interface, the program parses and validates the map. The game is launched only if the map satisfies all the required conditions.

🕹️ Game Goal

The objective is simple:

Collect every coin on the map, then reach the exit.

The player controls the character using the keyboard.

The exit cannot be used until all collectibles have been gathered.

Game elements
Symbol	Meaning
P	Player
C	Collectible / Coin
E	Exit
1	Wall
0	Empty space

Example:

111111111111
1000C0000001
101111101001
100P00000C01
100001111001
100C0000E001
111111111111

🗺️ Map Validation

One of the important parts of the project is validating the map before starting the game.

The program first reads the .ber file, parses its contents, and checks whether the map is valid.

A valid map must satisfy several conditions.

✅ Required conditions
The map must be rectangular.
The map must be completely surrounded by walls.
The map must contain exactly one player (P).
The map must contain exactly one exit (E).
The map must contain at least one collectible (C).
Only valid map characters are allowed.
The player must have a valid path to the required game elements.
All collectibles must be reachable.
The exit must be reachable.
The map must have a valid structure before the graphical window is created.

If the map is invalid, the program displays an error instead of launching the game.

🔍 Map Parsing

The first stage of the program is the map parser.

The parser reads the .ber file and converts the map into a structure that the game can work with.

The general process is:

          .ber map
             │
             ▼
       Read the file
             │
             ▼
       Parse the map
             │
             ▼
      Check characters
             │
             ▼
     Check map dimensions
             │
             ▼
      Check surrounding
          walls
             │
             ▼
      Check P / C / E
             │
             ▼
      Check accessibility
             │
             ▼
       Valid map?
        /       \
      NO         YES
      │           │
      ▼           ▼
    Error      Start game


This approach ensures that the graphical part of the program only receives valid data.

🧱 Checking Map Accessibility

A map can look correct while still being impossible to complete.

For example, a collectible might be surrounded by walls and therefore impossible to reach.

To solve this, the project checks the accessibility of the map using a flood-fill/pathfinding approach.

Starting from the player's position, the algorithm explores all reachable positions without passing through walls.

This allows the program to determine whether:

Every collectible can be reached.
The exit can be reached.
The player is not trapped.
The map can actually be completed.

This was an important part of the project because map validation is not only about checking the characters — it is also about checking the logic of the map.

🖼️ MiniLibX

The graphical part of the project is built using MiniLibX, a small graphical library commonly used in the 42 curriculum.

MiniLibX provides the basic tools needed to create a window, display images, and listen for user events.

Some of the main functions used in the project include:

mlx_init()

Initializes the MiniLibX connection and prepares the graphical environment.

mlx_new_window()

Creates the game window.

mlx_xpm_file_to_image()

Loads graphical assets from XPM files.

mlx_put_image_to_window()

Places an image inside the game window.

mlx_key_hook() / event hooks

Allows the program to react to keyboard input.

mlx_hook()

Used to listen for window and system events, such as closing the window.

mlx_loop()

Starts the MiniLibX event loop and keeps the game running while waiting for user input.

mlx_destroy_window()

Closes and destroys the game window.

Image destruction functions

Used to free graphical resources when the game ends.

🎮 Event Handling

The game is event-driven.

Instead of constantly checking the keyboard manually, the program registers callbacks that are triggered when an event occurs.

For example:

Keyboard input
      │
      ▼
 MiniLibX event
      │
      ▼
 Key handler
      │
      ▼
 Check movement
      │
      ▼
 Is destination valid?
    /       \
  NO         YES
  │           │
  ▼           ▼
Nothing    Move player
              │
              ▼
        Update game state
              │
              ▼
        Render the map


The player can move around the map while walls prevent invalid movement.

🚪 Exiting the Game

The game can be closed in two ways:

❌ Window X

Clicking the X button on the game window triggers the appropriate window event and closes the game cleanly.

⎋ ESC

Pressing the ESC key also closes the game.

Both are handled through MiniLibX event listening.

This was an important part of learning how external events interact with the program's game state.

🪙 Collectibles & Exit Logic

The game keeps track of how many collectibles remain.

When the player moves onto a collectible:

Player moves
     │
     ▼
Collectible found?
     │
    YES
     │
     ▼
Collectible removed
     │
     ▼
Remaining collectibles--


The exit has a special condition:

                    Player reaches exit
                           │
                    ┌──────┴──────┐
                    │             │
              Coins remain    No coins remain
                    │             │
                    ▼             ▼
                Continue        YOU WIN 🎉


The player must collect all coins before exiting.

🛠️ Development Process

I developed the project progressively instead of trying to build the complete game at once.

1. Map parsing

First, I implemented the logic required to read the .ber file and store the map.

2. Map validation

After parsing the map, I added checks for:

Map dimensions
Valid characters
Walls
Player
Exit
Collectibles
Map accessibility
3. Game structures

I then created structures to keep track of important game information such as:

Map data
Player position
Collectible count
Exit position
Map dimensions
MiniLibX objects
Loaded images
4. MiniLibX initialization

Once the map was validated, I initialized MiniLibX and created the game window.

5. Rendering

I created the rendering system to translate the map characters into graphical elements.

For example:

1  →  Wall image
0  →  Floor image
P  →  Player image
C  →  Coin image
E  →  Exit image


Each map character corresponds to a tile displayed in the game window.

6. Player movement

I implemented keyboard event handling and movement validation.

The player can move only when the destination tile is not blocked by a wall.

7. Game state

I added the logic for:

Collecting coins
Counting remaining collectibles
Detecting the exit
Determining when the player wins
Counting/displaying movements
8. Event management and cleanup

Finally, I implemented proper handling for:

ESC
Window close button
Game completion
Image cleanup
Window destruction
Memory cleanup

This helped make the program more robust and avoid resource leaks.

🧰 Technologies
C
MiniLibX
Makefile
Unix / Linux
XPM images
File descriptors
Dynamic memory allocation
Event-driven programming
Flood-fill / path validation
🚀 Installation & Usage
Clone the repository
git clone <YOUR_REPOSITORY_URL>
cd so_long

Compile the project
make


This creates the executable:

./so_long

Launch the game

Provide a .ber map as an argument:

./so_long maps/map1.ber


You can choose any valid map from the maps directory:

./so_long maps/map2.ber


For example:

maps/
├── map1.ber
├── map2.ber
├── map3.ber
└── ...

🎮 Controls
Key	Action
W / ↑	Move up
A / ←	Move left
S / ↓	Move down
D / →	Move right
ESC	Exit game
X	Close window
📁 Project Structure
so_long/
│
├── assets/
│   ├── player.xpm
│   ├── wall.xpm
│   ├── floor.xpm
│   ├── coin.xpm
│   └── exit.xpm
│
├── maps/
│   ├── map1.ber
│   ├── map2.ber
│   └── ...
│
├── src/
│   ├── parsing/
│   ├── validation/
│   ├── rendering/
│   ├── movement/
│   ├── events/
│   └── ...
│
├── Makefile
├── so_long.h
└── README.md

📚 What I Learned

This project helped me develop several important programming skills.

Parsing

I learned how to read external files and convert their contents into a usable internal representation.

Validation

I learned how to verify that input data satisfies multiple conditions before allowing the program to continue.

Algorithms

The accessibility check introduced me to flood-fill/pathfinding concepts and showed me how algorithms can be used to validate real-world data.

Graphics

Using MiniLibX taught me the fundamentals of creating a graphical window and rendering a game world from data.

Event handling

I learned how event-driven programs react to keyboard and window events.

Memory management

The project required careful allocation and freeing of memory for maps, images, and game structures.

Program architecture

Instead of keeping everything inside one large function, I learned how to separate the project into different responsibilities:

Parsing
   ↓
Validation
   ↓
Initialization
   ↓
Rendering
   ↓
Events
   ↓
Movement
   ↓
Game State
   ↓
Cleanup

🎯 Project Goal

The main goal of So Long was not simply to create a game.

It was to understand how different programming concepts work together in a complete project:

Input → Parsing → Validation → Algorithms → Graphics → Events → Game Logic → Cleanup

This project gave me practical experience turning a text-based map into an interactive graphical application while keeping the program structured, validated, and memory-safe.

👨‍💻 1337 / 42 Project

So Long — 1337 Coding School / 42 Network

A small 2D game, but a big lesson in parsing, algorithms, graphics, events, and software structure.
