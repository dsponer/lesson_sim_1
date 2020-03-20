#include <iostream>

extern "C" {
#include "remoteApi/extApi.h"
}

int main() {

    int clien_id = simxStart((simxChar*)"127.0.0.1", 19997, true, true, 2000, 5);
    if(clien_id != -1){
        std::cout << "Conncetion work" << std::endl;
    }
    else{
        std::cout << "Error connection" << std::endl;
    }

    return 0;
}
