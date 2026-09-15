# CoDraw Plotter
A physical drawing interface for real-time human-AI Co-Drawing.

## What is CoDraw
CoDraw is a desktop drawing system with two robotic arms sharing a single sheet of paper:

- **Encoder Arm (Input):** A passive arm held by your hand that tracks pen movements in real time.
- **Plotter Arm (Output):** A motorized SCARA arm that draws physical ink strokes alongside human hand.

![](/docs/images/codraw_idea.jpg)

## Background: Three Eras of Design
1. **Analog (Paper & Foam):** Great tactile feedback and creative joy, but lacks speed and precision.
2. **Digital (CAD & 3D Printing):** High precision, but counter-intuitive, separating input from output with long iteration delays.
3. **Generative AI (Prompts):** Easy, but turns creators into passive "prompt-and-wait" observers.

## Concept: Co-Drawing & The Joy of Making
Instead of typing prompts or waiting for renders, human and the AI weave a single sketch on the same sheet of paper in real time, using drawing both to **communicate** (input) and to **think** (ideation).

- **Human Strokes & Agency:** Preserves the tactile flow of ink and direct physical control over every line.
- **Sketching to Think:** Welcomes line overlaps and raw physical friction to spark unexpected ideas, treating the sketch as a live, evolving prototype.
- **Sketching to Communicate:** Streams hand strokes as direct spatial input, generating editable NURBS curves in CAD instantly without scanning.

## How It Can Be Used
- **Designers & Engineers:** Sketch rough concepts on paper while AI overlays structural guidelines, streaming vector paths straight to CAD.
- **Students & Learners:** Explore spatial thinking through hands-on physical play without staring at a screen.
- **Rehabilitation:** Combine physical feedback and hand movement for cognitive practice and motor skills.

## How It Works (Dual-MCU System)

![](/docs/images/codraw_system.jpg)

<!---
```
┌───────────────────────────────────────────────────────────┐
│                 Shared Paper Workspace                    │
│                                                           │
│   [ Human Hand ]  ─────── (Stroke Input) ───────┐         │
│         ▲                                       │         │
│         │ (Physical Feedback &                  │         │
│         │  Creative Friction)                   ▼         │
│         │                                [ AI Engine ]    │
│         │                                       │         │
│         │                                       │         │
│   [ CoDraw Arm ]  ◄── (Physical Pen Output) ────┘         │
└─────────────────────────────┬─────────────────────────────┘
                              │
                 (Real-Time Vector Kinematics)
                              ▼
            [ Live CAD Environment / NURBS Curves ]
```
--->

- **Hardware:** Microcontroller #1 reads magnetic encoders on the tracking arm. Microcontroller #2 drives stepper motors on the plotter arm.
- **Software:** A Python host processes serial inputs, generates AI vector paths, and streams live curves to CAD (Rhino/Grasshopper).

## Roadmap

### 1. Input Track: Encoder Arm

- [ ]  **Procurement & Cad Design (Sep 2026)**: Order encoders & XIAO RP2040s; CAD 2-DOF passive arm.
- [ ]  **Firmware & FK (Oct 2026)**: 3D print linkages; write firmware & Forward Kinematics (FK).
- [ ]  **Calibration (Nov 2026)**: Calibrate encoder resolution, filtering, and physical rigidity.
- [ ]  **Integration (Dec 2026 – Feb 2027)**: Mount to baseplate; perform high-speed gesture tracking & stress tests.

### 2. Output Track: Plotter Arm

- [ ]  **Procurement & Geometry Study (Sep 2026)**: Order steppers/drivers; design 2-DOF SCARA layout.
- [ ]  **Mechanism & Wiring (Oct 2026)**: 3D print parallel arm; wire drivers and pen-lift mechanism.
- [ ]  **Firmware & IK (Nov 2026)**: Write Inverse Kinematics (IK), acceleration, and motor control firmware.
- [ ]  **Integration (Dec 2026 – Feb 2027)**: Calibrate workspace reach, pen-lift height, and motion safety.

### 3. Integration Track: Software & AI *(Parallel Track)*

- [ ]  **Dev Setup & APIs (Sep 2026)**: Setup Python stack; research Rhino/Grasshopper live streaming APIs.
- [ ]  **Serial Bridge & NURBS (Oct 2026)**: Build `serial_bridge.py` & stream live NURBS directly in CAD.
- [ ]  **Path Processing (Nov 2026)**: Add real-time stroke smoothing & vector path preprocessing.
- [ ]  **Syn-Sketch Engine (Dec 2026 – Jan 2027)**: Build `ai_engine.py`; close sub-30ms real-time loop.
- [ ]  **Demo & Plugin (Feb 2027)**: Finalize Rhino/Grasshopper plugin & record prototype demo video.