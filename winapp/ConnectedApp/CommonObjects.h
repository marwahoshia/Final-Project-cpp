#pragma once
#include <atomic>      // Provides atomic operations for thread-safe access to boolean flags // Lock-Free Synchronization
#include <vector>      // Provides dynamic arrays for storing job lists
#include <string>      // Provides support for string manipulation
#include <mutex>       // Provides mutual exclusion (mutex) to ensure thread-safe access to shared resources
#include "JobInfo.h"   // Includes the definition of the JobInfo struct, representing job details

struct CommonObjects {
    std::atomic_bool exit_flag = false;   // Flag to signal when the application should terminate (thread-safe)
    std::atomic_bool start_download = false; // Flag to indicate when a job download operation should start (thread-safe)
    std::atomic_bool data_ready = false;  // Flag indicating when the job data is ready to be displayed (thread-safe)
    std::string url;                      // URL used for making API requests to download job data
    std::string search_query;             // Stores the job title search query entered by the user
    std::vector<JobInfo> jobList;         // Dynamic array holding a list of JobInfo objects representing job details
    std::mutex mutex;                     // Mutex to ensure thread-safe access to shared resources, such as the job list
};




/*exit_flag: This is likely used to signal when the threads should stop execution.Since multiple threads might check or set this flag,
using std::atomic_bool ensures that the check or modification is done atomically, preventing any race conditions.

start_download : This flag is probably used to indicate when the download thread should begin its operation.By using std::atomic_bool,
you ensure that the flag can be safely read and modified by different threads.

data_ready : This flag indicates when the data is ready to be used by other parts of the program.
Making it atomic ensures that once the data is marked as ready by one thread, other threads can see this change immediately and start using the data.
*/