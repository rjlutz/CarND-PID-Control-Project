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

---

# Original Project Readme 

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

