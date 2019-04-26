# VideoConverter

VideoConverter is a tool to process a video file and convert the processed video to a CSV file.

## Getting Started

The build system is CMake-based and supports Linux distros.

## Building

### Requirements

* C++ 17
* CMake `>=3.14`
* OpenCV `4.1`
* ffmpeg `4`

### Steps to build

1. Install the required tools.
2. Check out this repository.
3. Create and enter the build directory.
4. Run `cmake`
5. Run `make`

## Improvements

This is a quick project that lacks optimizing and proper testing. Listed below are some ways to imrpove quality and efficiency of the proejct

### Testing

I believe that no professional project is complete without adequate testing.
A boost test suite can easily be incorporated into the present cmake build system.
Throughout my code I attempted to break processing steps into separate functions to allow for unit testing.

### Optimizations

Without having a full picture of the scenario, it can be difficult to properly maximize time and space efficiency. 
Making those optimizations though can yield massive gains in a large production environment, so it's always important to keep in mind what could possibly be improved as you go.

The most glaring potential improvement is the two "system" calls being used. Using a c++ library should provide a large reduction in time spent performing those tasks and eliminate the need to search for and read files in the following code.

Another big bottleneck occurs in the [frame passing-processing pipeline](https://github.com/bchoates/videoconverter/blob/master/src/VideoConverter.h#L55)
I separated the frame getting and processing classes to allow for future parallel processing, however, I did't take advtange of that in this example.
I would improve this process based on the expected systems used to run this task repeatedly.

* Multi-core systems with large amounts of memory could make use of multiple threads, each processing a different frame.
* Thread-safe queues can be implemented to facilitate frame passing between those threads and the resulting csv strings
