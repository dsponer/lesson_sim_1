#include <iostream>
#include <ctime>

extern "C" {
#include "remoteApi/extApi.h"
}

//функция паузы
void sleep(float seconds) {
    std::clock_t startClock = std::clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    // do nothing until the elapsed time has passed.
    while (std::clock() < startClock + secondsAhead);
}


int main() {
    //подключение к симулятору
    int clien_id = simxStart((simxChar *) "127.0.0.1", 19997, true, true, 2000, 5);

    //проверка что симулятор подключен
    if (clien_id != -1) {

        simxStartSimulation(clien_id, simx_opmode_oneshot_wait); //страрт симулятора
        std::cout << "Conncetion work" << std::endl;

        int r, l;
        simxGetObjectHandle(clien_id, "DynamicRightJoint", &r, simx_opmode_oneshot_wait);

        int left_sensor;
        simxFloat * auxValues;
        simxInt * auxValuesCount;
        simxUChar vision_state;

        simxGetObjectHandle(clien_id, "LeftSensor", &left_sensor, simx_opmode_oneshot_wait);
        simxReadVisionSensor(clien_id, left_sensor,NULL,NULL,NULL,simx_opmode_streaming);
        sleep(1);


        while (true) {
            simxReadVisionSensor(clien_id, left_sensor, &vision_state, &auxValues, &auxValuesCount,simx_opmode_buffer);
            std::cout << auxValues[0] << std::endl;
            simxSetJointTargetVelocity(clien_id, r, 0, simx_opmode_oneshot_wait);
        }

    } else {
        std::cout << "Error connection" << std::endl;
        simxStopSimulation(clien_id, simx_opmode_oneshot_wait);
        simxFinish(clien_id);
    }

    return 0;
}
