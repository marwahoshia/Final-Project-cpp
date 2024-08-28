#define CPPHTTPLIB_OPENSSL_SUPPORT // Enable SSL support in httplib for HTTPS requests
#include "DownloadThread.h" // Include the header file for the DownloadThread class
#include "httplib.h" // Include the httplib library for making HTTP requests
#include "nlohmann/json.hpp" // Include the nlohmann JSON library for handling JSON data
#include <iostream> // Include the iostream library for standard input/output operations

// Define JSON serialization for the JobInfo struct to easily map JSON keys to struct members
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JobInfo, id, title, company, job_type, location, experience, job_description)

void DownloadThread::operator()(CommonObjects& common) {
    // Create an HTTP client instance pointing to the API host
    httplib::Client cli("https://jobs-api19.p.rapidapi.com");

    while (!common.exit_flag) { // Loop until the exit_flag is set to true // while(true)
        if (common.start_download) { // Check if the start_download flag is set
            common.start_download = false;  // Reset the start_download flag to prevent repeated downloads

            // Perform a GET request to the specified URL with the required headers
            auto res = cli.Get(common.url.c_str(), {
                { "x-rapidapi-key", "b12660daf6msheaaca3176081389p15b6fcjsn86b4f6e57405" }, // API key for authentication
                { "x-rapidapi-host", "jobs-api19.p.rapidapi.com" } // API host identifier
                });

            if (!res) { // Check if the response is null (indicating a failed request)
                std::cerr << "Failed to get response from API." << std::endl; // Log an error message
                continue; // Continue the loop without processing further
            }

            if (res->status == 200) { // Check if the HTTP status code is 200 (OK)
                try {
                    auto json_result = nlohmann::json::parse(res->body); // Parse the JSON response
                    std::lock_guard<std::mutex> lock(common.mutex); // Lock the mutex to ensure thread-safe access to shared data

                    common.jobList.clear(); // Clear the previous job list
                    for (const auto& item : json_result) { // Iterate over each item in the JSON array
                        JobInfo job; // Create a JobInfo struct to hold job details
                        job.id = item.value("id", 0); // Extract the job ID, defaulting to 0 if missing
                        job.title = item.value("job_title", "N/A"); // Extract the job title, defaulting to "N/A" if missing
                        job.company = item.value("company", "N/A"); // Extract the company name, defaulting to "N/A" if missing
                        job.job_type = item.value("job_type", "N/A"); // Extract the job type, defaulting to "N/A" if missing
                        job.location = item.value("location", "N/A"); // Extract the location, defaulting to "N/A" if missing
                        job.experience = item.value("experience", "N/A"); // Extract the experience level, defaulting to "N/A" if missing
                        job.job_description = item.value("job_description", "N/A"); // Extract the job description, defaulting to "N/A" if missing
                        common.jobList.push_back(job); // Add the job to the job list
                    }
                    common.data_ready = true; // Set the data_ready flag to indicate that new data is available
                }
                catch (const std::exception& e) { // Catch any exceptions during JSON parsing
                    std::cerr << "JSON parsing error: " << e.what() << std::endl; // Log the error message
                }
            }
            else { // Handle non-200 HTTP status codes
                std::cerr << "HTTP request failed with status code: " << res->status << std::endl; // Log the status code
                std::cerr << "Response body: " << res->body << std::endl; // Log the response body
            }
        }
    }
}

// Function to set a new URL for the download process
void DownloadThread::SetUrl(const std::string& new_url) {
    _download_url = new_url; // Update the _download_url member variable with the new URL
}