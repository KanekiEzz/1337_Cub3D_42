
## 📋 Cub3D Project Board

### 🟦 To Do
#### Setup & Learning
- [X] Install MLX and test example code
- [ ] Learn raycasting basics (watch YouTube videos or read guides)
- [ ] Understand X and Y axis math (angle, sin/cos, grid units)

#### Map Parsing
- [ ] Implement `.cub` file parser
- [ ] Parse resolution, floor & ceiling colors
- [ ] Parse texture paths (if required)
- [ ] Parse and validate map layout
- [ ] Find and validate player start position
- [ ] Create 2D array map representation

#### Rendering Prep
- [ ] Set up MLX window
- [ ] Draw background with two colors (ceiling/floor)
- [ ] Draw minimap (top-down map)
- [ ] Add player movement & rotation

---

### 🟨 In Progress
- [ ] Implement basic raycasting (vertical wall rendering)
- [ ] Fix fish-eye distortion
- [ ] Add collision detection for player
- [ ] Clean up input handling

---

### 🟩 Done
(This column will grow over time!)

---

### ⭐ Bonus
- [ ] Add texture rendering for walls
- [ ] Add door mechanic (open/close on keypress)
- [ ] Add minimap with player orientation
- [ ] Add basic sprites (e.g. health or items)
- [ ] Add mouse support (look direction)
- [ ] BMP screenshot saving

---

## ✅ Suggested Task Division (Example)

| Task | Student 1 | Student 2 |
|------|-----------|-----------|
| MLX Init & Window | ✔️ |  |
| Parser (config, map) | ✔️ | ✔️ |
| Player movement | ✔️ |  |
| Raycasting (core logic) |  | ✔️ |
| Drawing 3D scene |  | ✔️ |
| Drawing minimap | ✔️ |  |
| Textures |  | ✔️ |
| Final cleanup | ✔️ | ✔️ |

## CHATGPT

In MLX (MiniLibX), you can draw a circle using the `mlx_pixel_put` function, but there's no built-in circle drawing function. However, you can implement it by calculating the points that lie on the circumference of a circle using the circle equation:

$$
(x - cx)^2 + (y - cy)^2 = r^2
$$

Where:

* $(cx, cy)$ is the center of the circle.
* $r$ is the radius of the circle.

To draw a circle, you'll want to iterate through angles (typically 360 degrees or 0 to 2π radians) and calculate the corresponding points using parametric equations.


### Explanation:

* `mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);` is used to plot each point on the circle. The color `0xFFFFFF` represents white.
* We iterate over angles from 0 to 2π (360 degrees) to get the coordinates of the points on the circle's circumference.
* The circle is drawn by using the parametric equations for `x` and `y` based on the angle.



## Links

- Permadi: [Raycasting](https://www.permadi.com/tutorial/raycast/rayc1.html)
- Minilibx: [hsmits MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- Minilibx: [gontjarow's MiniLibX tutorial](https://gontjarow.github.io/MiniLibX/)
- Xlib (for MLX events): [The Xlib Manual](https://tronche.com/gui/x/xlib/)
- Raycasting: [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
- Raycasting: [Permadi's Raycasting tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- Movement: [Calculating heading in 2d games: Using trigonometric functions part 1](http://gamecodeschool.com/essentials/calculating-heading-in-2d-games-using-trigonometric-functions-part-1/)