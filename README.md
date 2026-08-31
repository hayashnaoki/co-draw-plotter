# CoDraw Plotter
An arm interface that bridges human hand-drawn input with AI-driven plotter output, enabling "Syn-Sketching" between AI and humans.

## Background
Design tools have shifted through three eras:
1. Paper & Foam (Analog): Offers immediate physical feedback and tactile joy, but is limited in execution speed and precision.
1. CAD & 3D Printers (Digital): Delivers high precision, but disconnects the creator through separated input/output and long iteration delays.
1. Generative AI (Prompts): Provides high speed, but turns creators into passive "prompt-and-wait" observers.

## Concept: Integrating Syn-Sketch, Input, and Output
Instead of complex CAD operations or waiting passively for images to generate, the creator and AI weave a single sketch together in real-time on the exact same sheet of paper.

1. Syn-Sketching & The Joy of Making
    - Hands-On Agency: Preserves the friction of paper, the flow of ink, and the satisfaction of drawing.
    - Creative Friction: Welcomes mechanical quirks, hand tremors, and line overlaps to spark unexpected ideas instead of clean, sterile database averages.
    - Gesture Dialogue: Speaks to the AI through pen strokes rather than rigid text prompts.

2. Physical Input & Live CAD Output
    - A Single Shared Loop: Hand input and robotic pen output happen simultaneously on the same sheet of paper.
    - Instant CAD Conversion: As you draw, the encoder arm streams live kinematic data to generate editable curves directly in CAD. No scanning or manual tracing is required.

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
- Children and Learners: Play and draw on real paper without looking at a screen, building spatial and visual design skills.
- Rehabilitation: Combine hand movement and physical feedback to enhance cognition.

## Hardware Architecture
To maintain responsiveness and low latency of physical drawing, gesture tracking and plotter control are split into a dual MCU setup.

![](/docs/images/codraw_system.jpg)

<!---
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
--->

## Roadmap
- [ ] Phase 1: Encoder Arm — Dual AS5048A SPI encoder reading, Forward Kinematics (FK), and live PC stroke display.
- [ ] Phase 2: Plotter Arm — Lightweight rigid arm, closed-loop stepper control, and Inverse Kinematics (IK).
- [ ] Phase 3: Full Syn-Sketch Loop — Real-time AI path generation and physical pen integration.