🍬 Candy Crush Project

👤 Author Information

Author: Oleh Nosul

Academic Year at un: 3rd Year

Program: Applied Informatics

📜 Project Description

This project is a recreation of the classic Candy Crush game, implemented as part of the PGR1 course requirements.

🔧 Prerequisites

To run this project, you need:

🖥️ A Linux-based operating system.


🚀 Installation Guide


Step 1️⃣: Clone the Repository

git clone git@github.com:antimit/PGR_P.git

Step 2️⃣: 

cd PGR_P


Step 3️⃣: Install Required Libraries

Debian:

sudo apt-get install libsfml-dev

Fedora:

sudo dnf install SFML SFML-devel

Arch:

sudo pacman -S sfml


Step 4️⃣: Build the Project

make


Step 5️⃣: Run the Program


./myProgram



🌟 Features

🍭 Classic Candy Crush gameplay mechanics.

🎵 Smooth animations and sound effects (requires SFML Audio).

🛠️ Project Details

Programming Language: C++(SFML),


📚 Documentation
🔍 How It Works
The program implements Candy Crush gameplay using a grid-based system and relies on object-oriented design principles for modularity and clarity.

Key Components:
Game Board
The game board is represented as a 2D grid of jewels. It handles:

Candy placement and initialization.
Detecting matches of three or more candies in rows or columns.
Game Logic

Matching Detection: When a match is found the matched candies are removed and candies above  them fall into their place.
Scoring System: Players cat earn points based on the number and type of matches he or she destroyed.
Rendering and Animation

Players can swap two adjacent candies using mouse.
Invalid moves are detected and prevented.


🛠️ Customization
You can modify game parameters by editing the corresponding JSON configuration file in the project directory. The following values can be adjusted:

Timer: Set the duration of the game session.
Required Score: Specify the score needed to win the game.
Number of Moves: Limit the total number of moves a player can make.
To apply your changes, open the JSON file, update the values, and save the file before starting the program.

