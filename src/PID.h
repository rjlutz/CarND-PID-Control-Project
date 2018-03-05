#ifndef PID_H
#define PID_H

class PID {
public:
    /*
    * Errors
    */
    double p_error;
    double i_error;
    double d_error;

    /*
    * Coefficients
    */
    double k[3];            // tau_p, tau_i, tau_d
    double dk[3];           // used to twiddle coefficients

    double best_err;        // lowest error of all time
    double cte_squared_err; // error encountered in current epoch
    long steps_elapsed;     // steps counted in current epoch

    int current_param;      // 0=tau_p, 1=tau_i, 2=tau_d
    int twiddle_interval;   // number of steps to consider in each tuning epoch


    enum State: int
    {
        Not_started,
        Incrementing,
        Decrementing,
        Production
    };

    State run_state;

    /*
    * Constructor
    */
    PID();

    /*
    * Destructor.
    */
    virtual ~PID();

    /*
    * Initialize PID.
    */
    void Init(double Kp, double Ki, double Kd);

    void Init(double pid[], double delta_k[]);

    /*
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    /*
    * Calculate the total PID error.
    */
    double TotalError();

    /*
     * gradient ascent algorithm
     */
    void twiddle();

    /*
     * cycled through k parameters, rotating back to the first after the third value has been processed
     */
    int next_param();


};

#endif /* PID_H */
