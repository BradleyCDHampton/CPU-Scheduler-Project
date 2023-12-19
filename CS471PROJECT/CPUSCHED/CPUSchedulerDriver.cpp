
#include <iostream>
#include <string>
#include "CPUScheduler.hpp"

int main(int argc, char* argv[]){

    if (argc != 3){
        std::cout << "You must specify a scheduling algorithm via a command-line argument.\n"
                  << "Legal options are:\n"
                  << "\tFCFS\t\tFirst Come First Serve\n"
                  << "\tSJF\t\tShortest Job First\n"
                  << "\tPRIORITY\tPriority\n";
                  exit(1);
    }

    std::string fileName = argv[1];
    std::string modeSelection = argv[2];

    std::string outputFileName = fileName.substr(0, fileName.size()-4) + "-" + modeSelection + "-output.txt";

    int mode;
    if (modeSelection == "FCFS")
        mode = FCFS;
    else if (modeSelection == "SJF")
        mode = SJF;
    else if (modeSelection == "PRIORITY")
        mode = PRIORITY;
    else{
        std::cout << "Invalid Mode Entry" << std::endl;
        exit(1); // User will have to invoke the program invoking an appropriate mode.
    }

    CPUScheduler scheduler = CPUScheduler(fileName, mode);
    scheduler.runScheduler();
    scheduler.output(outputFileName);

    return 0;
    

}