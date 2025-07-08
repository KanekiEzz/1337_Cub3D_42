import cv2
import mediapipe as mp
import numpy as np
import time
import os
import sys

try:
    import pyautogui
    pyautogui.FAILSAFE = False
    USE_PYAUTOGUI = True
except Exception as e:
    print(f"PyAutoGUI not available: {e}")
    print("Will use keyboard simulation instead")
    USE_PYAUTOGUI = False
    
    try:
        import subprocess
        USE_XDOTOOL = True
    except:
        USE_XDOTOOL = False

def press_key_down(key):
    if USE_PYAUTOGUI:
        try:
            pyautogui.keyDown(key)
            return True
        except:
            pass
    
    if USE_XDOTOOL:
        try:
            subprocess.run(['xdotool', 'keydown', key], check=True)
            return True
        except:
            pass
    
    print(f"KEY '{key}' PRESSED DOWN! (simulated)")
    return True

def release_key(key):
    if USE_PYAUTOGUI:
        try:
            pyautogui.keyUp(key)
            return True
        except:
            pass
    
    if USE_XDOTOOL:
        try:
            subprocess.run(['xdotool', 'keyup', key], check=True)
            return True
        except:
            pass
    
    print(f"KEY '{key}' RELEASED! (simulated)")
    return True

def count_extended_fingers(landmarks):
    finger_tips = [8, 12, 16, 20]
    finger_pips = [6, 10, 14, 18]
    
    thumb_tip = 4
    thumb_ip = 3
    
    extended_fingers = 0
    
    if landmarks[thumb_tip].x > landmarks[thumb_ip].x:
        extended_fingers += 1
    
    for tip, pip in zip(finger_tips, finger_pips):
        if landmarks[tip].y < landmarks[pip].y:
            extended_fingers += 1
    
    return extended_fingers

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.5
)

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

current_key_pressed = None
key_press_start_time = 0
gesture_stability_time = 0.3
last_gesture_time = 0

print("Hand Gesture Control Started!")
print("0 fingers (fist) = No keys pressed")
print("1 finger = Press and hold 'z'")
print("2 fingers = Press and hold 's'")
print("Press 'q' to quit")

while True:
    ret, frame = cap.read()
    if not ret:
        break
    
    frame = cv2.flip(frame, 1)
    frame_height, frame_width = frame.shape[:2]
    
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    
    results = hands.process(rgb_frame)
    
    detected_fingers = 0
    current_time = time.time()
    
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
            
            detected_fingers = count_extended_fingers(hand_landmarks.landmark)
    
    cv2.putText(frame, f"Fingers: {detected_fingers}", (10, 50),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
    
    target_key = None
    if detected_fingers == 0:
        target_key = None
    elif detected_fingers == 1:
        target_key = 'w'
    elif detected_fingers == 2:
        target_key = 's'
    elif detected_fingers == 3:
        target_key = 'd'
    elif detected_fingers == 4:
        target_key = 'a'
    else:
        target_key = None
    
    if target_key != current_key_pressed:
        if current_key_pressed:
            release_key(current_key_pressed)
            print(f"Released key '{current_key_pressed}'")
            current_key_pressed = None
        
        if target_key and current_time - last_gesture_time > gesture_stability_time:
            press_key_down(target_key)
            current_key_pressed = target_key
            key_press_start_time = current_time
            last_gesture_time = current_time
            print(f"Pressed and holding key '{target_key}'")
    
    if current_key_pressed:
        hold_time = current_time - key_press_start_time
        cv2.putText(frame, f"Holding '{current_key_pressed}' ({hold_time:.1f}s)", 
                   (10, 90), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
    else:
        cv2.putText(frame, "No key pressed", (10, 90), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    
    cv2.putText(frame, "0=nothing | 1=hold 'z' | 2=hold 's'", 
               (10, frame_height - 60), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)
    cv2.putText(frame, "Press 'q' to quit", (10, frame_height - 30),
                cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)
    
    cv2.imshow('Hand Gesture Control', frame)
    
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

if current_key_pressed:
    release_key(current_key_pressed)
    print(f"Released key '{current_key_pressed}' on exit")

cap.release()
cv2.destroyAllWindows()
hands.close()
print("Hand Gesture Control Stopped!")