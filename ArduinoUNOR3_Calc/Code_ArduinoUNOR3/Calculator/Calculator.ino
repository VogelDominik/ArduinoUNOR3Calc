#include <Arduino.h>

// Function to parse the input string and perform the calculation
int parseAndCalculate(char* input);

void setup() {
    // Initialize serial communication at 9600 bits per second
    Serial.begin(9600);
}

void loop() {
    // Check if data is available to read from the serial port
    if (Serial.available() > 0) {
        // Read the incoming string until a newline character is received
        String inputString = Serial.readStringUntil('\n');
        // Remove any leading and trailing whitespace
        inputString.trim();
        // Convert the String object to a character array
        char inputCharArray[50];
        inputString.toCharArray(inputCharArray, 50);

        // Parse the input and calculate the result
        int result = parseAndCalculate(inputCharArray);
        // Send the result back to the PC via serial communication
        Serial.println(result);
    }
}

// This function parses the input string and performs the calculation
int parseAndCalculate(char* input) {
    int operand1 = 0, operand2 = 0; // Variables to hold the operands
    char operation; // Variable to hold the operation (+, -, *, /)

    // Parse the input string to extract the operands and the operation
    sscanf(input, "%d %c %d", &operand1, &operation, &operand2);

    // Perform the calculation based on the operation
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) { // Check for division by zero
                return operand1 / operand2;
            } else {
                Serial.println("Error: Division by zero"); // Print error message
                return 0;
            }
        default:
            Serial.println("Error: Invalid operation"); // Print error message
            return 0;
    }
}
