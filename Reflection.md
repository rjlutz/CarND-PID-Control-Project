# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

This project was created in fulfillment of Udacity's CarND PID Controls project. The template 
project was forked from https://github.com/udacity/CarND-PID-Control-Project and improved to meet
the specification set forth for the project.


---
* Describe the effect each of the P, I, D components had in your implementation.


Creation of and observation of the Proportional/Integral/Derivative (PID) controller met the 
expectations set in the preceding lessons. A PID controller was created to drive a car model around
a simulated track. The proportional component of this model applies steering change in proportion 
to the reported amount of cross track error (CTE). The derivative component further adjusts the 
steering, based on the rate of change (or gradient) of the CTE value. This added adjustment further refines
the control to have a smoother approach toward acquisition of the correct vehicle trajectory. This 
smoother approach prevents the vehicle from overshooting the target trajectory. Finally, the integral 
component further adjusts the control for long-term systematic errors such as vehicle steering drift.

Individual removal of each of the P-I-D components from the model resulted in significantly 
poorer performance of the controller.

The following demonstration was run at throttle of 0.3. The coefficients for Kp, Ki, and Kd were set
to 0.1550, 0.00025, and 3.0, respectively.


[Demo Video](https://www.dropbox.com/s/fjyc3shsry1opf9/PID-Demo.mp4?dl=0 "Demonstration Video")


---


* Describe how the final hyperparameters were chosen.

Initial settings for steering hyperparameters were selected manually via trial and error. 
Once some good candidates were chosen, the gradient descent algorithm from the course's
twiddle example was modified to work continuously while running the 
course-supplied simulator. Initial coefficients were set to 0.125, 0.0002, 3.0, with tuning
parameters of 0.03, 0.00005, and 0.3. After 63 epochs of 500 steps at 0.3 throttle, these 
values were selected for Kp, Ki,and Kd:

    0.2634, 0.00029455, 3.2869

The simulation was continued for 500 epochs, without identification of a new minima. 
values.

Next, the throttle was increased to 0.6 and the twiddle algorithm was rerun. Resulting coefficients
were:

    0.1550, 0.00025, 3.0
    
The minimal process cost was encountered in epoch 2. The twiddle was continued for an additional 300 epochs 
without  identification if a new minima.
    
The video referenced above demonstrates a drive around the test track with these Kp, Ki 
and Kd values. The drive was conducted safely at approximately 35 MPH (throttle = 0.3).


Since the project goals were acheieved at this point, I did not endeavor to add a throttle 
controller. It is anticipated that the existing PID controller class could be reused for the 
gradient descent and production control of the throttle setting.