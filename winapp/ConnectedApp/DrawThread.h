#pragma once
#include "CommonObjects.h" // Includes the CommonObjects struct definition, which holds shared data between threads

class DrawThread {
public:
    // Overloaded function call operator that runs the drawing process in a thread
    // This will handle the GUI rendering based on the shared data in CommonObjects
    void operator()(CommonObjects& common);
};
