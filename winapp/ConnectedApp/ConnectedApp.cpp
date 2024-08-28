#include <iostream> // For standard input/output operations
#include <thread>   // For using threading functionalities
#include "CommonObjects.h" // Include the shared data structure
#include "DrawThread.h"    // Include the DrawThread class for GUI handling
#include "DownloadThread.h" // Include the DownloadThread class for handling data downloads

int main() {
    CommonObjects common; // Instantiate the shared data structure
    common.url = "https://jobs-api19.p.rapidapi.com/jobs?limit=100";  // Set the initial API URL to download job data

    DrawThread draw; // Instantiate the DrawThread class for managing the GUI
    auto draw_th = std::jthread([&] { draw(common); }); // Create a thread to handle the GUI rendering and start it

    DownloadThread down; // Instantiate the DownloadThread class for managing the data download
    auto down_th = std::jthread([&] { down(common); }); // Create a thread to handle the data downloading and start it

    common.start_download = true;  // Trigger the initial download of job data by setting the start_download flag to true
    std::cout << "Running...\n"; // Print a message to the console to indicate that the program is running

    down_th.join(); // Wait for the download thread to finish
    draw_th.join(); // Wait for the draw thread to finish

    return 0; // Return 0 to indicate that the program executed successfully
}
