# MuscleControlledSurgery
This project focuses on bettering the interface between a surgeon and patient during robotic surgery by allowing muscle signals to guide a simple endoscope extension and using haptic feedback when the endoscope is within 5 cm of a surface.

A robot with 1 DOF has an endoscope that moves on a gear track via stepper motor. The back and forth movement will be dictated by an Arduino that will collect muscle signals (EMG) from a person's wrist. If a person flexes their wrist up, the endoscope pole will go backwards at a constant velocity and if the person flexes down, the endoscope will travel forwards.
