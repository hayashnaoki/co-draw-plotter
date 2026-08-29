# CoDraw Plotter
A merged I/O arm interface for *Syn-Sketching*, converting real-time encoder gestures directly into physical AI co-drawing.

## Background
Design tools have shifted through three eras:
1. Paper & Foam (Analog): Instant physical feedback and tactile joy, but limited execution speed and accuracy.
2. CAD & 3D Printers (Digital): High precision, but disconnected by input-output separation and long iteration lags.
3. Generative AI (Prompting): Fast, but turns creators into passive "prompt-and-wait" observers.

## Concept: Syn-Sketching & Merged I/O
Instead of taking turns or generating images on a screen, creator and the AI weave a single sketch together on the exact same piece of paper in real time.

1. Syn-Sketching & The Joy of Making
    - Hands-On Agency: Preserves the friction of paper, the flow of ink, and the satisfaction of drawing.
    - Creative Friction: Welcomes mechanical quirks, hand tremors, and line overlaps to spark unexpected ideas instead of clean, sterile database averages.
    - Gestural Dialogue: Talk to the AI through the speed and weight of your pen strokes, not rigid text prompts.

2. Physical Input & Live CAD Output
    - One Shared Loop: Your hand input and the robot's pen output happen on the same sheet at the same time.
    - Instant CAD Vectors: As you draw, the encoder arm streams live kinematic data to generate editable curves directly in CAD. No scanning or manual tracing required.

![](/docs/images/codraw_idea.jpg)

<!---
```
┌───────────────────────────────────────────────────────┐
│               Shared Paper Workspace                  │
│                                                       │
│ [ Human Hand ]  ─────── (Stroke Input) ───────┐       │
│       ▲                                       │       │
│       │ (Physical Feedback &                  │       │
│       │  Creative Friction)                   ▼       │
│       │                                [ AI Engine ]  │
│       │                                       │       │
│       │                                       │       │
│ [ CoDraw Arm ]  ◄── (Physical Pen Output) ────┘       │
└─────────────────────────┬─────────────────────────────┘
                          │
            (Real-Time Vector Kinematics)
                          ▼
        [ Live CAD Environment / NURBS Curves ]
```
--->

## Potential Applications
- Designers & Engineers: Co-sketch rough ideas with live AI scaffolding directly on paper, streaming clean curves straight into CAD.
- Kids & Learners: Play, draw, and build spatial intuition on real paper without getting glued to a screen.
- Rehab: Combine hand movement and physical feedback for cognition.

## Hardware Architecture
To maintain responsiveness and low latency of physical drawing, gesture tracking and plotter control are split into a dual MCU setup.

```
                [ Shared Paper Workspace ]
                             │
            (Human Input) ┌──┴──┐ (AI Physical Output)
                          │     │
                          ▼     │
┌───────────────────────────┐   │   ┌───────────────────────────┐
│ Input Encoder Arm         │   │   │ Plotter Arm               │
│ ├─ Passive Linkage        │   │   │ ├─ Base-mounted Steppers  │
│ ├─ SPI Magnetic Encoders  │   │   │ ├─ Closed-loop Control    │
│ └─ XIAO RP2040 (#1)       │   │   │ └─ XIAO RP2040 (#2)       │
└─────────────┬─────────────┘   │   └─────────────▲─────────────┘
              │                 │                 │
              │ Serial/USB      │                 │ Serial/USB
              ▼                 │                 │
┌───────────────────────────────┴─────────────────┴─────────────┐
│ AI Processing Host (PC)                                       │
│ └─ Real-Time Vector Path Generation (<30ms target)            │
└───────────────────────────────────────────────────────────────┘
```

## Roadmap
- [ ] Phase 1: Encoder Arm — Dual AS5048A SPI encoder reading, Forward Kinematics (FK), and live PC stroke display.
- [ ] Phase 2: Plotter Arm — Lightweight rigid arm, closed-loop stepper control, and Inverse Kinematics (IK).
- [ ] Phase 3: Full Syn-Sketch Loop — Real-time AI path generation and physical pen integration.