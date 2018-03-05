#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>
#include <iomanip>

// for convenience
using json = nlohmann::json;
using namespace std;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

long iteration = 0;
long twiddle_epoch = 0;

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}


int main()
{
  uWS::Hub h;

  PID pid;

//  pid.run_state = PID::State::Not_started; // for twiddling
//  double k[] = {0.125, 0.0002, 3.0};
//  double dk[] = {0.03, 0.00005, 0.3};


  pid.run_state = PID::State::Production;    // for non-twiddling production run
  // double k[] = {0.2634, 0.00029455, 3.2869}; // determined after 63 epochs of 500 steps, throttle 0.3
  double k[] = {0.1550, 0.00025, 3.0}; // determined after 2 epochs of 500 steps, throttle = 0.6
  double dk[] = {0, 0, 0};

  pid.Init(k, dk);

  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(string(data).substr(0, length));
      if (s != "") {

        auto j = json::parse(s);
        string event = j[0].get<string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = stod(j[1]["cte"].get<string>());
          double speed = stod(j[1]["speed"].get<string>());
          double angle = stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          /*
          * TODO: Calculate steering value here, remember the steering value is
          * [-1, 1].
          * NOTE: Feel free to play around with the throttle and speed. Maybe use
          * another PID controller to control the speed!
          */

          pid.UpdateError(cte);
          steer_value = pid.TotalError();

          if (pid.run_state != PID::State::Production) {

            pid.steps_elapsed++;
            iteration++;

            // Let it start running a bit first and also reset if car crashes
            if ((pid.steps_elapsed >= pid.twiddle_interval)) {
              twiddle_epoch++;
              if ((speed<15) && pid.steps_elapsed > pid.twiddle_interval) {
                pid.best_err = numeric_limits<double>::max();;
                cout << "Crash Detected ..." << endl;
                string msg = "42[\"reset\", {}]";
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
              }

              pid.twiddle();
              cout <<
                   "iter: " <<
                   setw(8) << fixed << setprecision(0) << iteration << "\t" <<
                   "epoch :" <<
                   setw(8) << fixed << setprecision(0) << twiddle_epoch << "\t" <<
                   "k: " <<
                   setw(8) << fixed << setprecision(4) << pid.k[0] << "\t" <<
                   setw(8) << fixed << setprecision(13) << pid.k[1] << "\t" <<
                   setw(8) << fixed << setprecision(4) << pid.k[2] << "\t" <<
                   "best error: " <<
                   setw(8) << fixed << setprecision(4) << pid.best_err << "\t" <<
                   "cte^2 error: " <<
                   setw(8) << fixed << setprecision(4) << pid.cte_squared_err << "\t" <<
                   "steering angle: " <<
                   setw(6) << fixed << setprecision(2) << steer_value << "\t" <<
                   endl;

              pid.steps_elapsed = 0;
              pid.cte_squared_err = 0;
            }
          }
          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    cout << "Connected!!!" << endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    cout << "Disconnected" << endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    cout << "Listening to port " << port << endl;
  }
  else
  {
    cerr << "Failed to listen to port" << endl;
    return -1;
  }
  h.run();
}
