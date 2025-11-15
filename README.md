# 🐍 Snake Game

A classic Snake game implementation in C++ using OpenGL and GLUT with grid-based movement, food collection, and score tracking.

## 🎮 Features

- **Classic Snake Gameplay**: Control the snake with arrow keys to collect food and grow longer
- **Multiple Food Types**: 
  - 🔴 Regular food: +5 points, +1 length
  - 🟣 Power-up food: +20 points, +1 length (spawns less frequently)
- **Screen Wrapping**: Snake wraps around screen edges for continuous gameplay
- **Score System**: Real-time score tracking displayed on screen
- **Smooth Controls**: Arrow key navigation with anti-repeat protection
- **Game Over Detection**: Collision detection when snake hits itself

## 🎯 Controls

| Key | Action |
|-----|--------|
| ⬆️ Up Arrow | Move Up |
| ⬇️ Down Arrow | Move Down |
| ⬅️ Left Arrow | Move Left |
| ➡️ Right Arrow | Move Right |
| ESC | Exit Game |

## 🛠️ Prerequisites

### Ubuntu/Debian/WSL
```bash
sudo apt update
sudo apt install build-essential freeglut3-dev libglew-dev libfreeimage-dev mesa-common-dev libglu1-mesa-dev
```

### Fedora/RHEL
```bash
sudo dnf install @development-tools mesa-libGL-devel mesa-libGLU-devel freeglut-devel
```

### Arch Linux
```bash
sudo pacman -S base-devel freeglut mesa
```

## 🚀 Installation & Running

1. **Clone the repository**
   ```bash
   git clone https://github.com/sudoHasaan/snake-game-cpp.git
   cd snake-game-cpp
   ```

2. **Compile the game**
   ```bash
   make
   ```
   
   Or manually compile:
   ```bash
   g++ game-release.cpp util.cpp -o game-release -lGL -lGLU -lglut
   ```

3. **Run the game**
   ```bash
   ./game-release
   ```

## 🎲 Gameplay

- The snake starts with 2 segments at the center of the grid
- Use arrow keys to change direction
- Collect orange food items to increase your score by 5 points
- Collect purple power-ups (rare) to get 20 points
- Each food item increases the snake's length by 1
- Game ends when the snake collides with its own body
- Final score is displayed on the game over screen

## 📁 Project Structure

```
.
├── game-release.cpp      # Main game logic and rendering
├── util.h               # Utility functions and color definitions
├── util.cpp             # Utility implementations (drawing functions)
├── Makefile             # Build configuration
├── install-libraries.sh # Dependency installation script
└── README.md            # Project documentation
```

## 🎨 Game Components

- **Grid**: 64×58 playable area with 10-pixel cells
- **Snake Head**: Green circle
- **Snake Body**: Yellow squares
- **Regular Food**: Orange-red circles
- **Power-up Food**: Purple circles
- **Background**: Dark purple/slate gray grid

## 👨‍💻 Author

**sudoHasaan**

## 📄 License

This project is open source and available under the MIT License.


