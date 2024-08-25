#include "dataCollection.h"

void dataInputChecker(const float &currentTime){
    const int currentSecond = static_cast<int>(currentTime);
    if (currentSecond > currentSecondCounter && currentSecond < totalSeconds){
        availableToInput = true;
        currentSecondCounter += 1;
    }
}

void inputMilliseconds(const float &beforeTime, const float &afterTime, float inputArray[]){
    const float elapsedTime = afterTime - beforeTime;
    inputArray[currentSecondCounter] = elapsedTime * 1000; // convert to milliseconds.
}

void createCsv()
{
    // Check if the file already exists
    if (std::ifstream("output.csv")) {
        std::remove("output.csv");
    }

    std::fstream newFile;
    newFile.open("output.csv", std::ios::out | std::ios::app);

    newFile <<
    "Seconds Elapsed" << "," << "Z Coordinate" << "," <<
    "FPS" << "," << "Average FPS" << "," << "CPU Time (ms)" << "," << "GPU Time (ms)" << "," <<
    "Text Calculation (ms)" << "," << "Text Render (ms)" << "," <<
    "Trees Count" << "," <<
    "Tree Calculation (ms)" << "," << "Tree Render (ms)" << "\n";
    for (int i = secondsOffset; i < totalSeconds; i++){ // i set to secondsOffset to ignore first few seconds.
        newFile <<
        i - secondsOffset + 1 << "," << zCoordCollection[i] << "," <<
        fpsCollection[i] << "," << averageFpsCollection[i] << "," << totalCalculationTimeCollection[i] - gpuCalculationTimeCollection[i] << "," << gpuCalculationTimeCollection[i] << "," <<
        textCalculationTimeCollection[i] << "," << textRenderTimeCollection[i] << "," <<
        totalTreeCountCollection[i] << "," <<
        treeCalculationTimeCollection[i] << "," << treeRenderTimeCollection[i] << '\n';
    }
}
