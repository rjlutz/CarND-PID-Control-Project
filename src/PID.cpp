#include "PID.h"
#include <math.h>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {

  best_err = 0;
  cte_squared_err = 0;
  twiddle_interval = 500;
  steps_elapsed = 0;
  current_param = 0; // 0=tau_p, 1=tau_i, 2=tau_d
  best_err = std::numeric_limits<double>::max();
  run_state = Production;

}

PID::~PID() {}

void PID::Init(double pid[], double delta_k[]) {
  Init(pid[0], pid[1], pid[2]);
  dk[0] = delta_k[0];
  dk[1] = delta_k[1];
  dk[2] = delta_k[2];

}

void PID::Init(double Kp, double Ki, double Kd) {

  k[0] = Kp;
  k[1] = Ki;
  k[2] = Kd;

  p_error = 0;
  i_error = 0;
  d_error = 0;

}

void PID::UpdateError(double cte) {

  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
  cte_squared_err += pow(cte, 2.0);

}

double PID::TotalError() {
  return - k[0] * p_error - k[1] * i_error - k[2] * d_error;
}

int PID::next_param() {
  return (current_param + 1) % 3;
}

void PID::twiddle() {

  if (run_state == State::Not_started) {
    best_err = cte_squared_err;
    k[current_param] += dk[current_param];
    run_state = State::Incrementing;
  } else if (run_state == 1) {
    if (cte_squared_err < best_err) {
      best_err = cte_squared_err;
      dk[current_param] *= 1.1;
      current_param = next_param();
      k[current_param] += dk[current_param];
      run_state = State::Incrementing;
    } else {
      k[current_param] += -2 * dk[current_param];
      if (k[current_param] < 0) {
        k[current_param] = 0;
        current_param = (current_param + 1) % 3;
      }
      run_state = State::Decrementing;
    }
  } else {  // decrementing
    if (cte_squared_err < best_err) {
      best_err = cte_squared_err;
      dk[current_param] *= 1.1;
      current_param = next_param();
      k[current_param] += dk[current_param];
      run_state = State::Incrementing;
    } else {
      k[current_param] += dk[current_param];
      dk[current_param] *= 0.9;
      current_param = next_param();
      k[current_param] += dk[current_param];
      run_state = State::Incrementing;
    }
  }
}

