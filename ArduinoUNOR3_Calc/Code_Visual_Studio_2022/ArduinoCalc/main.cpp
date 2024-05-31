
#include <windows.h>   // Windows-specific header for serial communication
#include <iostream>
#include <string>

using namespace std;

// Handle for the serial port
HANDLE hSerial;
// Serial port settings structure
DCB dcbSerialParams = { 0 };
// Structure for serial port timeouts
COMMTIMEOUTS timeouts = { 0 };

// Function to convert a standard string (std::string) to a wide string (std::wstring)
// This is necessary because Windows API functions often require wide strings
wstring s2ws(const std::string& s) {
    int len;
    int slength = (int)s.length() + 1; // Get length of the input string including null terminator
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); // Get required buffer size
    wchar_t* buf = new wchar_t[len]; // Allocate buffer for wide string
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len); // Convert string to wide string
    std::wstring r(buf); // Create wstring from buffer
    delete[] buf; // Free the allocated buffer
    return r; // Return the wide string
}

// Function to connect to the serial port
bool connectSerial(const char* portName) {
    // Convert the port name to a wide string
    wstring stemp = s2ws(portName);
    LPCWSTR portNameW = stemp.c_str();

    // Open the serial port
    hSerial = CreateFile(portNameW, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        // If the port cannot be opened, print an error message
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            cout << "Error: Port not found." << endl;
        }
        return false; // Return false to indicate failure
    }

    // Get the current serial port state
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout << "Error getting state." << endl;
        return false; // Return false if we cannot get the state
    }

    // Set the serial port parameters
    dcbSerialParams.BaudRate = CBR_9600; // Baud rate of 9600
    dcbSerialParams.ByteSize = 8; // 8 data bits
    dcbSerialParams.StopBits = ONESTOPBIT; // 1 stop bit
    dcbSerialParams.Parity = NOPARITY; // No parity

    // Apply the serial port parameters
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cout << "Error setting state." << endl;
        return false; // Return false if we cannot set the state
    }

    // Set the timeouts for the serial port
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    // Apply the timeouts
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        cout << "Error setting timeouts." << endl;
        return false; // Return false if we cannot set the timeouts
    }

    return true; // Return true to indicate success
}

// Function to close the serial port
void closeSerial() {
    CloseHandle(hSerial); // Close the handle to the serial port
}

// Function to write data to the serial port
bool writeSerial(const char* data) {
    DWORD bytesWritten;
    // Write data to the serial port
    if (!WriteFile(hSerial, data, strlen(data), &bytesWritten, NULL)) {
        cout << "Error writing to serial port." << endl;
        return false; // Return false if we cannot write data
    }
    return true; // Return true to indicate success
}

// Function to read data from the serial port
bool readSerial(char* buffer, DWORD bufferSize) {
    DWORD bytesRead;
    // Read data from the serial port
    if (!ReadFile(hSerial, buffer, bufferSize, &bytesRead, NULL)) {
        cout << "Error reading from serial port." << endl;
        return false; // Return false if we cannot read data
    }
    // Add a null terminator to the buffer to make it a valid C-string
    buffer[bytesRead] = '\0';
    return true; // Return true to indicate success
}

int main() {
    // Connect to the serial port (adjust COM3 to your actual port)
    if (!connectSerial("\\\\.\\COM3")) {
        return 1; // Exit if we cannot connect to the serial port
    }

    while (true) {
        string input;
        // Prompt the user for input
        cout << "Enter calculation (for example: 34 * 72): ";
        getline(cin, input); // Get the input from the user

        // Add a newline character to the input
        input += '\n';
        // Write the input to the serial port
        if (!writeSerial(input.c_str())) {
            return 1; // Exit if we cannot write data
        }

        char buffer[128];
        // Read the result from the serial port
        if (!readSerial(buffer, sizeof(buffer))) {
            return 1; // Exit if we cannot read data
        }

        // Display the result
        cout << "Result: " << buffer << endl;
    }

    // Close the serial port when done
    closeSerial();
    return 0; // Exit the program
}
