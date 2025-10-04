Keylogger (C++)

Simple Windows Polling This is a basic, single-file keylogging application written in C++ using the Windows API (windows.h). It operates by continuously polling the state of the keyboard to detect and log keystrokes to a local file.

Ethical and Legal Disclaimer

This code is for educational and ethical self-monitoring purposes only. Using keylogging software to monitor, intercept, or capture data from users without their express, informed consent is generally illegal and unethical. The developer assumes no liability and is not responsible for any misuse or damage caused by this program.

 Prerequisites

Operating System: Windows (The code relies on Windows API functions like GetAsyncKeyState).

Compiler: A C++ compiler environment that supports the Windows API, such as:

Microsoft Visual C++ (MSVC) compiler (Recommended when using VSCode/Visual Studio).

MinGW/GCC with proper setup for Windows API calls.

Editor: Visual Studio Code (VSCode) is recommended for easy implementation.

 How to Compile and Run

Step 1: Compilation (Using MSVC via Command Line)

Open your terminal or a Visual Studio Developer Command Prompt and navigate to the directory containing keylogger.cpp. Compile the code using the following command, which links the necessary Windows user interface library (user32.lib):

cl keylogger.cpp /link user32.lib


This will generate an executable file named keylogger.exe.

Step 2: Running the Program

Run the generated executable:

keylogger.exe


The program will immediately hide its console window and begin monitoring keystrokes.

You can confirm it is running by checking your Windows Task Manager.

Step 3: Stopping the Keylogger

The program includes a built-in safety exit:

Press the ESCAPE (ESC) key on your keyboard.

This will automatically terminate the process and allow you to view the log file.

📄 Log File Details

File Name: log.txt

Location: The log file is created and updated in the same directory as keylogger.exe.

Contents: Keystrokes are recorded, with special keys noted in brackets (e.g., [ENTER], [BACKSPACE], [SHIFT]).

