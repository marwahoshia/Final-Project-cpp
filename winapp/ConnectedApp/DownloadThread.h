#pragma once //This directive ensures the header file is included only once during compilation, preventing duplicate definitions.
#include "CommonObjects.h" // Includes the CommonObjects struct definition, which holds shared data between threads
#include <thread> // Includes support for creating and managing threads

class DownloadThread {
public:
    // Overloaded function call operator that runs the download process in a thread
    void operator()(CommonObjects& common);

    // Sets the URL for downloading job data
    void SetUrl(const std::string& new_url);

private:
    std::string _download_url; // Stores the URL to be used for downloading job data
};
