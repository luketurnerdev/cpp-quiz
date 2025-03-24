#include <iostream>

using namespace std;

/*
 * This is a simple multiple choice quiz with 5 questions.
 * The user will interact with it via the command line, and
 * receive a score at the end.
 *
 * They should enter A,B,C or D (upper case only for now) to answer.
 *
 * 1) First we need to define a list of questions, and their corresponding answers.
 * 2) We then need to present the questions to the user one after the other, and have them respond.
 * 3) We should calculate their score at the end and show it to them.
 *
 * Edge cases: User types something other than A,B,C or D - we should ask them the same question again in this case.
 *
 *
 */

// Define the questions
// Fixed size array
const string questions[] = {
    "Question 1: \nWhat is the first step a compiler takes when processing code?\n\n"
    "A: Running the code immediately.\n"
    "B: Breaking the code into smaller pieces (tokens)\n"
    "C: Displaying an error message\n"
    "D: Saving the code as a text file\n",

    "Question 2: \nWhat does a compiler produce when it finishes translating your code?\n\n"
    "A: A text document.\n"
    "B: Machine code or executable file.\n"
    "C: An error message.\n"
    "D: A printed book.\n",

    "Question 3: \nWhat is the difference between a compiler and interpreter?\n\n"
    "A: Compilers are only used for web pages.\n"
    "B: Compilers translate all code at once; interpreters translate one line at a time.\n"
    "C: Interpreters create executable files.\n"
    "D: Compilers only work with images.\n"
};

// Size of entire array in bytes (~128 bytes, ~32 each)
// Divided by the size of 1 element
constexpr size_t amountOfElements = size(questions);

const string correctAnswers[] = {"B", "B", "B"};

// Limit the answers they can input
string acceptableInputs[4] = {"A", "B", "C", "D"};
const size_t acceptableListSize = size(acceptableInputs) / size(acceptableInputs[0]);

int score = 0;

// Methods

string makeUpper(string stringToConvert) {
    for (char &c : stringToConvert) {
        // Cast it to unsigned char first to avoid negative value issues (toupper expects this)
        const int upper = toupper(static_cast<unsigned char>(c));
        c = static_cast<char>(upper); // Convert each character to uppercase (back to a normal char)
    }

    return stringToConvert;
}

bool isValidAnswer(const size_t listSize, string acceptableInputs[], const string& userAnswer) {
    for (int j=0; j < listSize; j++ ) {
        if (acceptableInputs[j] == userAnswer) {
            return true;
        }
    }

    return false;
}

void quizLoop() {
    // Asking the user the questions
    for (size_t i=0; i < amountOfElements; i++ ) {
        string userAnswer;

        // Keep prompting until they give a valid input
        while (true) {
            // Ask the question
            cout << questions[i] << endl;

            // Get user input
            cin >> userAnswer;
            userAnswer = makeUpper(userAnswer);

            if (isValidAnswer(acceptableListSize, acceptableInputs, userAnswer)) {
                if (userAnswer == correctAnswers[i]) {
                    score++;
                    cout << "Correct!\n";
                } else {
                    cout << "Wrong!\n";
                }
                break;
            }

            // Incase the entry wasn't valid
            cout << "You entered an invalid answer. Please type A,B,C or D.\n" << endl;

        }
    }

    cout << "Your final score is " << score << "." << endl;
}

int main() {
    quizLoop();

    // If the user wants to play again
    string playAgainResponse;
    while (true) {
        cout << "Would you like to play again? (Y/N)" << endl;

        string acceptablePlayAgainInputs[2] = {"Y", "N"};
        cin >> playAgainResponse;

        playAgainResponse = makeUpper(playAgainResponse);

        if (isValidAnswer(size(acceptablePlayAgainInputs), acceptablePlayAgainInputs, playAgainResponse)) {
            break;
        } else {
            cout << "Please enter Y or N.\n";
        }
    }

    if (playAgainResponse == "Y") {
            quizLoop();
        }
    else if (playAgainResponse == "N") {
        cout << "Thanks for playing!";
    }


    return 0;
}