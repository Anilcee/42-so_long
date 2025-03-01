# So_long

## **Description**
SoLong is a 2D maze game inspired by the classic Pac-Man style. The player must collect randomly placed items in the map. The game is developed in **C** using the **Minilibx** library for graphics.

## **Features**
- Navigate through a maze.
- Enemies and moving characters.
- Graphics library powered by **Minilibx**.

## **Installation**

### **1. Clone the repository:**

```bash
git clone --recurse-submodules git@github.com:Anilcee/42-so_long.git
```

If you have already cloned the project, you can update the submodule by running the following command:

```bash
git submodule update --init --recursive
```

### **2. Install Minilibx:**
This project uses **Minilibx**. It has been included as a submodule. If the submodule is not downloaded correctly, you can update it by running:

```bash
git submodule update --init --recursive
```

### **3. Compilation:**
To compile the project, use the following command in your terminal:

```bash
make
```

### **4. Run the Game:**
After compiling, you can run the game by executing:

```bash
./so_long maps/map5.ber
```

## **Gameplay**

- The player moves around a **maze**, collecting items.

## **Controls**

- **Arrow Keys**: Move around.
- **Esc**: Exit the game.

## **Credits**
- The **Minilibx** library is used for graphical interface rendering.

---

Feel free to modify and add more specific details based on the features you've implemented in the game.
