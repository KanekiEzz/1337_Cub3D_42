# <h1 align="center">1337🇲🇦\_Cub3D\_42 🐚  Kaneki</h1>

<p align="center">
  <a href="https://github.com/KanekiEzz/1337_Cub3D_42">
    <img src="https://raw.githubusercontent.com/KanekiEzz/kaneki_badges/refs/heads/main/cub3dm.png" alt="42 Badge">
  </a>
</p>

---

# 🎮 Cub3D: A Raycasting Adventure

> ✨ A first-person 3D game engine powered by **raycasting**, inspired by *Wolfenstein 3D* and built from scratch in **C** using **MiniLibX**.

<p align="center">
  <img src="./assets/screenshot_main.png" alt="Cub3D Demo Screenshot" width="700"/>
</p>

---

## 📘 Overview

Cub3D is your gateway into the world of **graphics programming**. It renders a 3D perspective from a 2D grid map using real-time raycasting techniques — no 3D libraries involved.

You'll build everything manually: the math, the textures, the engine, and the gameplay interactions.

🖐️ **NEW BONUS:** Integrated with a [Hand Gesture Keyboard Controller](https://github.com/KanekiEzz/hand-gesture-keyboard) — control the player using just your hand via webcam!

<p align="center">
  <img src="./public/vedio/1.webm" alt="Hand Gesture Control" width="600"/>
</p>

---

## 🚀 Features

* 🧱 Real-time **raycasting** with the DDA algorithm
* 🚶 Smooth **player movement** with keyboard and mouse support
* 🚪 **Doors** that can open and close dynamically
* 🔫 **Animated weapon HUD** with mouse click to shoot
* 👾 **Enemy sprites** with frame-by-frame animations
* 🧭 **2D minimap** that updates in real time
* 🎨 **Textured walls**, RGB floor/ceiling
* 🖐️ **Hand Gesture Controls** (optional bonus)
* 🔊 Optional **sound support** (if added)

---

## 🛠️ Compilation

```bash
make
```

> 📦 Dependencies: MiniLibX, X11 (Linux) or macOS graphics libraries.

---

## 🎮 Controls

| Action          | Key(s)               |
| --------------- | -------------------- |
| Move Forward    | `W` / ☝️ (1 finger)  |
| Move Backward   | `S` / ✌️ (2 fingers) |
| Strafe Left     | `A` / ✋ (4 fingers)  |
| Strafe Right    | `D` / 🤟 (3 fingers) |
| Turn Left       | `←` or move mouse    |
| Turn Right      | `→` or move mouse    |
| Open/Close Door | `E`                  |
| Shoot           | `Left Mouse Click`   |
| Exit Game       | `ESC`                |

> 🖐️ For gesture control, run the [Hand Gesture Controller](https://github.com/KanekiEzz/1337_Cub3D_42/tree/main/Hand_Gesture_Keyboard_Control) in the background.

---

## 🧠 Technical Highlights

* 📐 **Trigonometry** and vectors for rendering & movement
* 🧮 **DDA (Digital Differential Analyzer)** for grid-based raycasting
* ✨ **Fish-eye correction** using cosine projection
* 🖼️ **Texture mapping** for immersive visuals

---

## 🧪 Learning Outcomes

* Understand how **3D perspective** can be simulated from 2D grids
* Apply real math concepts to real-time rendering
* Build your own **engine loop**, **renderer**, and **interactor**
* Manage memory and performance in C
* BONUS: Integrate **AI/computer vision input** with OpenCV and MediaPipe

---

## 👨‍💻 Authors ✍🏼

<table>
  <tr>
    <td align="center"><a href="https://github.com/KanekiEzz/"><img src="https://avatars.githubusercontent.com/u/110631781?s=400&u=0cd1de60c073f367d291df9c6ccef5c18ac64e41&v=4" width="100px;" alt="Kaneki"/>
      <br />
    </a>
      <br />
      <a href="https://profile.intra.42.fr/users/iezzam" title="Intra 42">
        iezzam42  🇲🇦
      </a>
    </td>
    <td align="center"><a href="https://github.com/iaceene/"><img src="https://avatars.githubusercontent.com/u/106110604?v=4" width="100px;" alt="Iaceene"/>
      <br />
    </a>
      <br />
      <a href="https://profile.intra.42.fr/users/yaajagro" title="Intra 42">
        yaajagro42  🇲🇦
      </a>
    </td>
  </tr>
</table>

---

## 📜 License

This project is part of the educational curriculum of [42/1337 Network](https://42.fr) and intended for academic use only.

---

> 💬 *"The first time you see your wall appear through code... you realize you've just stepped into another dimension."*
