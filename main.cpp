#include <iostream>
#include <ctime>

extern "C" {
#include "remoteApi/extApi.h"
}

void sleep(float seconds) {
    std::clock_t startClock = std::clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    // do nothing until the elapsed time has passed.
    while (std::clock() < startClock + secondsAhead);
}


int main() {

    int clien_id = simxStart((simxChar *) "127.0.0.1", 19997, true, true, 2000, 5);
    if (clien_id != -1) {
        simxStartSimulation(clien_id, simx_opmode_oneshot_wait);
        std::cout << "Conncetion work" << std::endl;
        int r, l;
        simxGetObjectHandle(clien_id, "DynamicRightJoint", &r, simx_opmode_oneshot_wait);


        simxSetJointTargetVelocity(clien_id, r, 10, simx_opmode_oneshot_wait);
        sleep(5);

        simxStopSimulation(clien_id, simx_opmode_oneshot_wait);
        simxFinish(clien_id);
    } else {
        std::cout << "Error connection" << std::endl;
        simxStopSimulation(clien_id, simx_opmode_oneshot_wait);
    }

    return 0;
}
