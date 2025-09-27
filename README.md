
# PID_Autonomous_Car

## Author  
**George Read**  
LinkedIn: https://www.linkedin.com/in/george-yaccoup/  

---

## Overview  
This project was developed as part of an Automatic Control course. It implements a prototype self-driving car using PID control. The control system runs on an Arduino Uno, managing the steering (and possibly speed) of the vehicle to follow a desired path.

---

## Features & Highlights  
- Implementation of a PID (Proportional–Integral–Derivative) controller  
- Real-time feedback loop for course correction  
- Designed to run on Arduino Uno hardware  
- Supports modular tuning and adjustment of PID parameters  
- Includes simulation and response analysis (Matlab / plots)  

---

## Repository Structure  

Here is a brief description of key files and folders:

| Path | Description |
|------|-------------|
| `CAR/` | Main Arduino code and logic for controlling the vehicle |
| `Matlab Response/` | Scripts or files for analyzing system response, tuning, simulation |
| `Project Backups/` | Backup files and previous versions |
| `presentation.pdf` | Project presentation slides |
| `Scematic_Car.pdsprj`, `ControlProject.pdsprj` | Project files for circuit / control system design tools |
| Image files (e.g. `.png`, `.jpg`) | Schematics, simulation graphs, hardware photos |

---

## Getting Started  

### Prerequisites  
- Arduino Uno  
- Motor driver (e.g. L293D)  
- Chassis with steering mechanism and sensors (e.g. line sensors, distance sensors)  
- Computer with Arduino IDE installed  
- (Optional) MATLAB / Octave for simulation and response plotting  

### Installation & Usage  

1. Clone the repository:  
   ```bash
   git clone https://github.com/georgeyaccoup/PID_Autonoums_Car.git
   cd PID_Autonoums_Car


2. Open the Arduino project (in `CAR/`) in Arduino IDE.

3. Adjust PID parameters (Kₚ, Kᵢ, K_d) inside the code to match your hardware.

4. Upload the code to the Arduino Uno.

5. Power the car, place it on the course, and observe its behavior. Tune parameters iteratively for stable performance.

6. (Optional) Use the MATLAB / simulation files to visualize the system response, step response, error curves, etc.

---

## Tuning Tips

* Start with only the proportional term (Kₚ) and gradually increase until oscillation or instability occurs.
* Introduce derivative (K_d) to dampen oscillations.
* Add integral (Kᵢ) to eliminate steady‐state error cautiously, as it can introduce overshoot.
* Record system response (e.g. plots) and refine parameters iteratively.

---

## Limitations & Future Improvements

* No autonomously generated path planning — it's reactive control along a fixed route or line
* Does not currently include obstacle avoidance
* May be sensitive to noise and hardware imperfections
* Future upgrades: integrate sensors (ultrasonic, LiDAR), implement higher-level control, machine learning path following


---

## Acknowledgements

This project was done for academic purposes in the Automatic Control course. Many thanks to instructors, lab assistants, and reference materials on control theory.

---

## Contact

For questions or collaboration, reach out on LinkedIn: [https://www.linkedin.com/in/george-yaccoup/](https://www.linkedin.com/in/george-yaccoup/)


