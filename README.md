Project Name: Job Researcher

Description: Job Researcher is a multi-threaded C++ application that allows users to search for job listings using an API and view detailed information about each job. The application provides a graphical user interface (GUI) built with ImGui, where users can search for jobs, mark jobs as favorites, and view detailed descriptions of selected jobs. The job data is fetched from a remote API, and the application supports searching, filtering, and favoriting jobs.

Main Components
1. CommonObjects Structure
Purpose:
Serves as a shared data structure between threads, holding important flags, job data, and synchronization mechanisms.
Main Members:
std::atomic_bool exit_flag: Indicates when the application should terminate.
std::atomic_bool start_download: Triggers the job download process.
std::atomic_bool data_ready: Signals when the job data is ready to be displayed.
std::string url: Stores the API endpoint URL.
std::string search_query: Holds the job title search query entered by the user.
std::vector<JobInfo> jobList: A list of jobs fetched from the API.
std::mutex mutex: Ensures thread-safe access to shared data.
2. JobInfo Structure
Purpose:
Represents the details of a job fetched from the API.
Main Members:
int id: The unique identifier of the job.
std::string title: The job title.
std::string company: The company offering the job.
std::string job_type: The type of job (e.g., full-time, part-time).
std::string location: The job's location.
std::string experience: The required experience level.
std::string job_description: A detailed description of the job.
bool show_details: Indicates whether to display additional job details.
bool is_favorite: Indicates whether the job is marked as a favorite.
3. DownloadThread Class
Purpose:
Handles downloading job data from the API in a separate thread.
Main Functions:
operator()(CommonObjects& common): The main function that runs in the thread, performing API requests and parsing JSON data into JobInfo objects.
SetUrl(const std::string& new_url): Allows setting a new URL for API requests.
4. DrawThread Class
Purpose:
Manages the GUI rendering process in a separate thread using ImGui.
Main Functions:
operator()(CommonObjects& common): The main function that runs in the thread, handling user input, displaying job data, and managing GUI interactions.
DrawAppWindow: The function used to render the GUI and handle the logic for displaying job data, search functionality, and favoriting jobs.
5. Main Function
Purpose:
Initializes the CommonObjects structure, starts the download and draw threads, and waits for them to complete.
Main Operations:
Sets the initial API URL.
Starts the DownloadThread and DrawThread.
Joins the threads to ensure the application runs until both threads complete.
How It Works
Initialization:

The CommonObjects structure is initialized with default values and an initial API URL.
The DownloadThread and DrawThread are started, running concurrently.
Job Search & Download:

When a user enters a search query and clicks "Search," the DownloadThread fetches job data from the API.
The fetched data is parsed into JobInfo objects and stored in the jobList.
GUI Rendering:

The DrawThread handles all GUI-related operations, displaying the job titles, providing options to show details, mark jobs as favorites, or remove them.
Users can toggle between viewing all jobs or only their favorite jobs.
Displaying Job Details:

When a job title is selected, detailed information about the job is displayed in a new window.
Thread Synchronization:

The std::mutex in CommonObjects ensures that shared data is accessed in a thread-safe manner, preventing race conditions.
Project Setup
To run the Job Researcher application, ensure that the necessary dependencies (such as ImGui, httplib, and nlohmann/json) are installed and configured. Compile and run the application, and interact with the GUI to search for jobs and view details.
