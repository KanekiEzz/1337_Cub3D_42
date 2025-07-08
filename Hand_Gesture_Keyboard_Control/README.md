# ✋ Hand Gesture Keyboard Controller

> Control your keyboard using hand gestures and computer vision powered by **MediaPipe**, **OpenCV**, and optionally **PyAutoGUI**.

---

## 📸 Overview

This Python project detects your hand and finger positions through your webcam in real time. Based on how many fingers are extended, it simulates key presses (`W`, `S`, `A`, `D`, etc.) to control your computer — ideal for hands-free applications or accessibility tools.

---

## 🧠 Features

* 🖐️ Real-time hand detection using MediaPipe
* ✨ Count extended fingers
* 🎮 Trigger keyboard input based on gesture:

  * 0 fingers: stop input
  * 1 finger: press and hold `W`
  * 2 fingers: press and hold `S`
  * 3 fingers: press and hold `D`
  * 4 fingers: press and hold `A`
* 🧪 Fallback support using `xdotool` if `pyautogui` fails

---

## 🧰 Requirements

```bash
pip install opencv-python mediapipe pyautogui
# Optional if pyautogui fails:
sudo apt install xdotool
```

---

## 🚀 Usage

```bash
python hand_gesture_control.py
```

Hold your hand in front of the camera and extend different numbers of fingers to simulate key presses.

---

## 💻 Supported Inputs

| Fingers | Action        | Key  |
| ------- | ------------- | ---- |
| 0       | Stop Input    | None |
| 1       | Move Forward  | `W`  |
| 2       | Move Backward | `S`  |
| 3       | Move Right    | `D`  |
| 4       | Move Left     | `A`  |

> 🛑 Press `Q` to quit the program.

---

## 📂 Repository Structure

```bash
hand-gesture-keyboard/
├── hand_gesture_control.py
├── README.md
```

---

## 🎯 Project Name & Repo Suggestion

**Project Name:** `Hand Gesture Keyboard Control`

**Suggested Repo Name:** `hand-gesture-keyboard`

---

## 📜 License

This project is released under the MIT License.

---

## 🙌 Author

Created with ❤️ by **Your Name**
🔗 [GitHub Profile](https://github.com/KanekiEzz)
