# Spy-VS-Spy

## This is a very small turned-based game in C++. 

### Description
This is a turned-based game where we have a player(Spy) which has to avoid being spotted/caught by a sentry(security). The player starts at the right-hand side of the GameWorld. The player wins the game if the player manages to reach the left side of the GameWorld avoiding all the sentries. We have two types of sentries: Sentries that move up and sentries that move down. All sentries whether it only moves up or down are placed on even-numbered coloumns. The GameWorld also contains wall which makes it difficult for the player to reach the left side pf the GameWorld. The walls are placed on odd-numbers coloumns going down and each coloumns that has a wall has at least a space where the player can pass through. 

### Features
- The size of the gameworld (rows and coloumns) are passed via Command-Line Arguments.
- The game contains a player which moves around the Gameworld.
- The game contains walls which prevents the player from moving over them.
- The game contains sentries which prevents the player from reaching the left side of the Gameworld.

### Conditions
- The player can't leave the Gameworld.
- When a player collides with a sentry. You lose the game.
- When a player reaches the left side of the Gameworld, you win the game.

### Concepts displayed
- Pointers.
- Dynamic memory allocation & deallocation.
- Namespaces.
- One and Two-Dimensional dynamic Arrays.
- Error-handling and assertions.
- Command-Line Arguments

### TO:DO
- Write code that prevents the player to move to wall or outside the GameWorld.
- Write Code that when the player is in the same position of the sentry, you lose the game.
- Write Code such that when the player reaches the left side of the Gameworld, the player wins the game.

### How to run the project.
- Open command line interface and type "run.bat"
- "run.bat" is a batch file which has certain commands that will get executed when the batch file is called.
  
