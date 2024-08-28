#pragma once
#include <string>  // Includes support for the standard C++ string class

struct JobInfo {
    int id;                        // Unique identifier for the job
    std::string title;             // Title of the job position
    std::string company;           // Name of the company offering the job
    std::string job_type;          // Type of job (e.g., Full-time, Part-time)
    std::string location;          // Location where the job is based
    std::string experience;        // Required experience level for the job
    std::string job_description;   // Detailed description of the job responsibilities and requirements
    bool show_details = false;     // Flag to toggle the display of additional job details in the UI
    bool is_favorite = false;      // Flag to indicate whether the job is marked as a favorite
};
