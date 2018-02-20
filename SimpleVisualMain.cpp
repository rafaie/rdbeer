#include "random.h"
#include "VisualAgent.h"
#include <iostream>
#include <fstream>
#include <chrono>

// Global constants

// const double StepSize = 0.1;
// const double RunDuration = 200;
const long RandomSeed = 1;


// The main program
void run_for_line(ofstream &outFile, double StepSize, int X1, int Y1, int X2, int Y2){
  VisualAgent Agent;
  Line Object;
  // Circle Object;

  // Load the CTRNN into the agent
  char fname[] = "categorize.ns";
  ifstream ifs;
  ifs.open(fname);
  if (!ifs) {
      cerr << "File not found: " << fname << endl;
      exit(EXIT_FAILURE);
  }
  ifs >> Agent.NervousSystem;

  // Run the agent
  SetRandomSeed(RandomSeed);
  Agent.Reset(0, Y1);
  Agent.SetPositionX(X1);
  Object.SetPositionX(X2);
  Object.SetPositionY(Y2);
  int timer = 0;
  int status = 0;
  auto start = std::chrono::system_clock::now();
  for (double t = 0; Object.PositionY() > BodySize/2; t += StepSize) {
      // cout << "------------------\n";
      // cout << Agent.PositionX() << " " << Agent.PositionY() << " \n";
      // cout << Object.PositionX() << " " << Object.PositionY() << " \n";
      outFile << 1 << ',' << ++timer << ',' << StepSize << ',' << X1 << ',' << Y1 << ',' << X2 << ',' << Y2 << ',';
      outFile << Agent.PositionX() << "," << Agent.PositionY() << "," << Object.PositionX() << "," << Object.PositionY() << "," << status <<" \n";
      status = 1;
      Agent.Step(StepSize, Object);
      Object.Step(StepSize);
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

  outFile << 1 << ',' << ++timer << ',' << StepSize << ',' << X1 << ',' << Y1 << ',' << X2 << ',' << Y2 << ',';
  outFile << Agent.PositionX() << "," << Agent.PositionY() << "," << Object.PositionX() << "," << Object.PositionY() << "," << ++status <<" \n";


}

void run_for_Circle(ofstream &outFile, double StepSize, int X1, int Y1, int X2, int Y2){
  VisualAgent Agent;
  // Line Object;
  Circle Object;

  // Load the CTRNN into the agent
  char fname[] = "categorize.ns";
  ifstream ifs;
  ifs.open(fname);
  if (!ifs) {
      cerr << "File not found: " << fname << endl;
      exit(EXIT_FAILURE);
  }
  ifs >> Agent.NervousSystem;

  // Run the agent
  SetRandomSeed(RandomSeed);
  Agent.Reset(0, Y1);
  Agent.SetPositionX(X1);
  Object.SetPositionX(X2);
  Object.SetPositionY(Y2);
  int timer = 0;
  int status = 0;
  for (double t = 0; Object.PositionY() > BodySize/2; t += StepSize) {
      // cout << "------------------\n";
      // cout << Agent.PositionX() << " " << Agent.PositionY() << " \n";
      // cout << Object.PositionX() << " " << Object.PositionY() << " \n";
      outFile << 2 << ',' << ++timer << ',' << StepSize << ',' << X1 << ',' << Y1 << ',' << X2 << ',' << Y2 << ',';
      outFile << Agent.PositionX() << "," << Agent.PositionY() << "," << Object.PositionX() << "," << Object.PositionY() << "," << status <<" \n";
      status = 1;
      Agent.Step(StepSize, Object);
      Object.Step(StepSize);
  }
  outFile << 2 << ',' << ++timer << ',' << StepSize << ',' << X1 << ',' << Y1 << ',' << X2 << ',' << Y2 << ',';
  outFile << Agent.PositionX() << "," << Agent.PositionY() << "," << Object.PositionX() << "," << Object.PositionY() << "," << ++status <<" \n";

}

void showModel(string fname){
  CTRNN NervousSystem;
  ifstream ifs;
  ifs.open(fname);
  if (!ifs) {
      cerr << "File not found: " << fname << endl;
      exit(EXIT_FAILURE);
  }
  ifs >> NervousSystem;
  cout << "------------------------------------\n";
  NervousSystem.PrintModel();
}

int main(int argc, char* argv[])
{
    ofstream outFile;
    outFile.open ("output.csv");
    outFile << "obj_type,timer,step_size,X1,Y1,X2,Y2,agent_X,agent_Y,obj_X,obj_Y,status\n";
    // int X1, Y1, X2, Y2;
    for (int j1=150; j1 < 275; j1+=20){
      for (int j2=-30; j2 <= 30; j2+=15){
        for (double i = 0.1; i <= 0.2; i+= 0.05){
          cout << "------------------------------------\n";
          cout << i << " " << 0<< " " << j1<< " " <<-32 + int((275-j1)/2)<< " " << j2 << "\n";
          run_for_line(outFile, i, j2, 0, -32 + int((275-j1)/2), j1);
          run_for_Circle(outFile, i, j2, 0, -32 + int((275-j1)/2), j1);
        }
      }
    }
    outFile.close();
    showModel("categorize.ns");
    return 0;
}
