# CoDraw Plotter
A merged I/O physical arm interface for *Syn-Sketching*, converting real-time encoder gestures directly into physical AI co-drawing.

## Background: The Paradigm Shift in Design Tools

CoDraw bridges three distinct eras of design to unlock a new paradigm of human-AI creation:

1. **Analog & Physical Era (Paper & Foam):** Ultra-low latency and rich tactile feedback, but limited by manual execution speed and precision.
2. **Digital & CAD Era (3D Printing & CNC):** Unmatched precision, but severely disconnected by input-output separation and long iteration lags.
3. **Generative AI Era (Passive Prompting):** Asynchronous "prompt-and-wait" text/image generation that degrades human agency and recycles database averages.

## Concept: Syn-Sketching, Real-Time I/O & Creative Friction
CoDraw is built around the core ethos of **restoring the Joy of Making** in an increasingly automated world. It introduces **Syn-Sketching**—a paradigm shift away from traditional turn-based exchanges toward simultaneous, co-creative emergence. Rather than a passive "wait-for-results" task, human and AI **weave a single, shared sketch on the same physical paper in real time**.

### 1. Syn-Sketching & The Joy of Making
Syn-Sketching shifts AI from polishing and replacement to rough-sketch co-creation:

- Preserving Creative Agency: Keeps the tactile friction, paper resistance, and gestural flow that make drawing satisfying.
- Creative Friction & Serendipity: Welcomes noise, overlaps, and physical quirks to break habitual patterns and avoid database-driven sameness.
- Non-Text Gestural Dialogue: Expresses spatial intent through stroke dynamics instead of rigid text prompts.

### 2. Real-Time Input & Output in One Loop
CoDraw merges hand input and machine output into a single live workflow, turning each sketch into usable CAD data as it unfolds:

- Shared Physical-Digital Loop: Human gestures and robotic drawing happen in the same space at the same time, keeping the act of making continuous.
- CAD as a Live Result: As the sketch progresses, the system converts the interaction into editable digital geometry rather than treating drawing as a separate offline step.

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

## Potential Use Scenarios
CoDraw's physical-digital fusion could benefit several groups:

- Designers & Engineers: AI could support ideation and form exploration by overlaying guidance directly on paper while preserving the flow of hand sketching.
- Children & Learners: Physical co-drawing could make learning more tactile and embodied, helping with shape, structure, and spatial understanding.
- Elderly & Rehabilitation: Real-time tactile feedback and guided drawing could support motor practice, memory recall, and gentle cognitive stimulation.

## Technical Architecture

To ensure temporal alignment and eliminate hardware blocking, CoDraw decouples gesture tracking from plotter actuation using a dual-MCU system.

```
                  [ Shared Paper Workspace ]
                             │
            (Human Input) ┌──┴──┐ (AI Physical Output)
                          │     │
                          ▼     │
┌───────────────────────────┐   │   ┌───────────────────────────┐
│ Input Tracking Arm        │   │   │ Low-Inertia Parallel Arm  │
│ ├─ Passive Linkage        │   │   │ ├─ Base-mounted Steppers  │
│ ├─ SPI Magnetic Encoders  │   │   │ ├─ Closed-loop            │
│ └─ XIAO RP2040 (#1)       │   │   │ └─ XIAO RP2040 (#2)       │
└─────────────┬─────────────┘   │   └─────────────▲─────────────┘
              │                 │                 │
              │ Serial/USB      │                 │ Serial/USB
              ▼                 │                 │
┌───────────────────────────────┴─────────────────┴─────────────┐
│ AI Processing Host (PC)                                       │
│ └─ Real-time Vector Path Generation (<30ms Inference Target)  │
└───────────────────────────────────────────────────────────────┘
```

## Roadmap

- [ ] **Phase 1: Input Tracking Arm** — Dual AS5048A SPI reading, Forward Kinematics (FK), and real-time XY stroke visualization on PC.
- [ ] **Phase 2: Low-Inertia Output Plotter** — Slim 2-DOF parallel linkage CAD, closed-loop stepper control, and Inverse Kinematics (IK).
- [ ] **Phase 3: Syn-Sketch Loop Integration** — Sub-30ms pipeline integration with real-time vector AI path generation & spatial calibration.
