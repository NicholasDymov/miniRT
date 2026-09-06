*This project has been created as part of the 42 curriculum by ndymov, ddymov.*

# miniRT

## Description

**miniRT** is a 3D ray tracer implemented in C from scratch using the **MLX42** graphics library. The project demonstrates the fundamental physics of ray tracing: generating rays through a virtual pinhole camera, computing geometric surface intersections, calculating Lambertian diffuse and ambient lighting, and casting shadow rays in 3D space.

### Key Features (Mandatory Part)
* **Camera Simulation**: Pinhole camera model with configurable origin, normalized look orientation, and adjustable horizontal Field of View (FOV).
* **Geometric Primitives**:
  * **Spheres**: Exact ray-sphere intersection with inner and outer view support.
  * **Planes**: Infinite planar surfaces with double-sided normal handling.
  * **Cylinders**: Finite cylinders bounded by two circular planar end-caps, correctly rendered from both the exterior and the interior.
* **Lighting & Shading**:
  * Ambient lighting with adjustable intensity ratio and RGB color.
  * Point light source with inverse-length light rays and Lambertian (diffuse) surface shading.
  * Hard shadow ray occlusion testing.
* **Interactive Scene Modification**:
  * Real-time translation of camera, light source, and scene objects across 6 degrees of freedom.
  * 3D rotation using Rodrigues' axis-angle formula without gimbal lock or $(0, 0, 0)$ singularities.
  * Object picking via mouse cursor rays and cycling via keyboard.
  * Interactive resizing of sphere/cylinder radii and cylinder heights.
  * Visual feedback: selected objects are highlighted with semi-transparency.
* **Robust Scene Parser**: Strict validation of `.rt` scene files with descriptive error messages (`Error\n<message>`).

---

## Instructions

### Requirements
* OS: Linux
* Compiler: `cc` (GCC or Clang)
* Build Tools: `make`, `cmake`
* Libraries: `libglfw3-dev`, `libdl`, `pthread`, `libm`

### Compilation
Build the mandatory executable:
```bash
make
```

Additional build targets:
* `make clean`: Removes all object files and temporary build artifacts.
* `make fclean`: Removes object files, libraries, and executables.
* `make re`: Full clean rebuild.
* `make fast`: Compiles with high optimization flags (`-O3 -march=native -ffast-math -flto`).
* `make debug`: Compiles with debug symbols (`-g3`).
* `make sanitize`: Compiles with AddressSanitizer and UndefinedBehaviorSanitizer (`-fsanitize=address,undefined`).

### Execution
Run the ray tracer with any valid `.rt` scene configuration file:
```bash
./miniRT assets/valid/complex/colonnade.rt
```

---

## Interactive Controls

| Category | Key / Action | Description |
| :--- | :--- | :--- |
| **Selection** | `Left Click` | Pick object directly under mouse cursor |
| | `Right Click` | Deselect object (return to Camera control) |
| | `TAB` | Cycle target: Camera (`0`) $\to$ Light (`-1`) $\to$ Objects (`1..N`) |
| **Translation** | `W` / `S` | Move forward / backward along viewing direction |
| | `A` / `D` | Strafe left / right along camera right axis |
| | `E` / `Q` | Move up / down along camera up axis |
| **Rotation** | `Ctrl + W` / `S` | Pitch camera or object up / down |
| | `Ctrl + A` / `D` | Yaw camera or object left / right |
| **Resizing** | `Alt + D` / `A` | Increase / decrease radius (Spheres & Cylinders) |
| | `Alt + W` / `S` | Increase / decrease height (Cylinders) |
| **Window** | `ESC` / `[X]` button | Cleanly exit and free all resources |

---

## Resources & AI Usage

### References
* **Scratchapixel** ([scratchapixel.com](https://www.scratchapixel.com)): Mathematical foundations of ray-sphere, ray-plane, and ray-cylinder intersections, as well as coordinate basis generation.
* **Ray Tracing in One Weekend** by Peter Shirley: Intuitive ray generation and camera projection models.
* **MLX42 Documentation** ([Codam Coding College](https://github.com/codam-coding-college/MLX42)): Window initialization, image pixel buffering, and event callback hooks.
* **Rodrigues' Rotation Formula**: Angle-axis rotation of 3D direction vectors without trigonometric matrix decomposition.

### AI Usage Disclosure
Artificial Intelligence (Google Antigravity) was consulted during pair programming for:
1. **Mathematical Validation**: Formulating and verifying Rodrigues' vector rotation to avoid $(0,0,0)$ cross-product degenerations when rotating vertical cylinders.
2. **Hook System Architecture**: Structuring modular key and mouse event dispatchers in compliance with 42 Norminette constraints (≤ 25 lines per function, ≤ 5 functions per file).
3. **Makefile Refactoring**: Designing separate object trees and dependency tracking for isolated mandatory (`src/mandatory/`, `include/mandatory/`) and bonus (`src/bonus/`, `include/bonus/`) compilations with zero relinking.
4. **Codebase Auditing**: Identifying edge cases such as uninitialized light variables and verifying scene parser error handling against invalid scenes.
