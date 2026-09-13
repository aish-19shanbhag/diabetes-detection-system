/*
 * Diabetes Detection System
 *
 * A rule-based expert system that asks a user a series of symptom
 * questions across up to three escalating levels of detail, and
 * classifies the likely type of diabetes (or rules it out) based
 * on the answers.
 *
 * Modernized from an original Turbo C++ (DOS) implementation to
 * standard, portable C++.
 */

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

class Diabetes {
private:
    string name;
    float age = 0;
    int weight = 0;
    float height = 0;
    char sex = ' ';
    char symptoms[20] = {};

public:
    void welcomeScreen();
    void getPersonalInfo();
    void getLevel1Symptoms();
    void getLevel2Symptoms();
    void getLevel3Symptoms();
    int analyseSymptoms(int level);
    char displayMessage(int level, int result);
};

void Diabetes::welcomeScreen() {
    cout << "********* W E L C O M E *********\n";
    cout << " D I A B E T E S   D E T E C T I O N   S Y S T E M\n\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void Diabetes::getPersonalInfo() {
    cout << "\n--- PERSONAL INFORMATION ---\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Age: ";
    cin >> age;
    cout << "Weight: ";
    cin >> weight;
    cout << "Height: ";
    cin >> height;
    cout << "Sex (M/F): ";
    cin >> sex;
}

void Diabetes::getLevel1Symptoms() {
    cout << "\n--- MEDICAL DIAGNOSIS FORM: LEVEL 1 ---\n";
    const char *questions[] = {
        "Appetite (H=High, L=Low, N=Normal): ",
        "Frequency of thirst (H/L/N): ",
        "Frequency of urination (H/L/N): ",
        "Vision (I=Impairment, N=Normal): ",
        "Urine sugar (P=Passive, A=Active): ",
        "Ketonurea (P/A): ",
        "Fasting blood sugar (H/L/N): ",
        "RBS (H/L/N): ",
        "Family history of diabetes (P/A): ",
        "OGTT (D/N): ",
    };
    for (int i = 0; i < 10; i++) {
        cout << questions[i];
        cin >> symptoms[i];
        symptoms[i] = toupper(symptoms[i]);
    }
}

void Diabetes::getLevel2Symptoms() {
    cout << "\n--- MEDICAL DIAGNOSIS FORM: LEVEL 2 ---\n";
    const char *questions[] = {
        "Pancreatitis (P/A): ",
        "Carcinoma (P/A): ",
        "Cirrhosis (P/A): ",
        "HCTS (H/L/N): ",
        "Hepatitis (P/A): ",
        "Hormonal disorder (P/A): ",
        "Pancreatectomy (P/A): ",
    };
    for (int i = 0; i < 7; i++) {
        cout << questions[i];
        cin >> symptoms[i];
        symptoms[i] = toupper(symptoms[i]);
    }
}

void Diabetes::getLevel3Symptoms() {
    cout << "\n--- MEDICAL DIAGNOSIS FORM: LEVEL 3 ---\n";
    const char *questions[] = {
        "Age group (Y=Young, M=Middle-aged, E=Elderly): ",
        "Body weight (N=Normal, A=Above normal, B=Below normal, O=Obese): ",
        "Duration (W=Weeks, M=Months, Y=Years): ",
        "Ketonurea (P/A): ",
        "Auto antibodies (P/A): ",
    };
    for (int i = 0; i < 5; i++) {
        cout << questions[i];
        cin >> symptoms[i];
        symptoms[i] = toupper(symptoms[i]);
    }
}

int Diabetes::analyseSymptoms(int level) {
    int count = 0;
    int result = 0;  // 0 = not diabetic / negative branch, -1 = diabetic / positive branch

    switch (level) {
        case 1:
            if (symptoms[9] == 'D') {
                result = -1;
            } else if (symptoms[5] == 'P' && symptoms[6] == 'P' && symptoms[7] == 'H') {
                result = -1;
            } else {
                for (int i = 0; i < 10; i++) {
                    if (symptoms[i] == 'H' || symptoms[i] == 'P' || symptoms[i] == 'D' || symptoms[i] == 'I') {
                        count++;
                    }
                }
                if (count > 5) {
                    result = -1;
                }
            }
            break;

        case 2:
            if (symptoms[0] == 'P' || symptoms[1] == 'P' || symptoms[2] == 'P' ||
                symptoms[3] == 'H' || symptoms[4] == 'P' || symptoms[5] == 'P' || symptoms[6] == 'P') {
                result = -1;
            } else {
                result = 0;
            }
            break;

        case 3:
            if ((symptoms[0] == 'Y' && symptoms[1] == 'N' && symptoms[2] == 'W' && symptoms[3] == 'P' && symptoms[4] == 'P') ||
                (symptoms[0] == 'Y' && symptoms[1] == 'B' && symptoms[2] == 'W' && symptoms[3] == 'P' && symptoms[4] == 'P') ||
                (symptoms[0] == 'Y' && symptoms[1] == 'N' && symptoms[2] == 'M' && symptoms[3] == 'P' && symptoms[4] == 'P') ||
                (symptoms[0] == 'Y' && symptoms[1] == 'N' && symptoms[2] == 'Y' && symptoms[3] == 'P' && symptoms[4] == 'P')) {
                result = 0;
            } else {
                result = -1;
            }
            break;

        default:
            break;
    }
    return result;
}

char Diabetes::displayMessage(int level, int result) {
    char ch = 'N';

    switch (level) {
        case 1:
            if (result == 0) {
                cout << "\nTHE PERSON IS NOT DIABETIC.\n";
                return 'N';
            } else {
                cout << "\nTHE PERSON IS DIABETIC.\n";
                cout << "Proceed to next level? (Y/N): ";
                cin >> ch;
            }
            break;

        case 2:
            if (result == 0) {
                cout << "\nIT IS PRIMARY DIABETES.\n";
                cout << "Proceed to next level? (Y/N): ";
                cin >> ch;
            } else {
                cout << "\nIT IS SECONDARY DIABETES.\n";
                return 'N';
            }
            break;

        case 3:
            if (result == 0) {
                cout << "\nIT IS INSULIN DEPENDENT DIABETES.\n";
            } else {
                cout << "\nIT IS NON-INSULIN DEPENDENT DIABETES.\n";
            }
            return 'N';
    }
    return toupper(ch);
}

int main() {
    Diabetes dts;
    int level = 1;
    int result;
    char choice;

    dts.welcomeScreen();
    dts.getPersonalInfo();

    dts.getLevel1Symptoms();
    result = dts.analyseSymptoms(level);
    choice = dts.displayMessage(level, result);

    if (choice == 'Y') {
        level = 2;
        dts.getLevel2Symptoms();
        result = dts.analyseSymptoms(level);
        choice = dts.displayMessage(level, result);

        if (choice == 'Y') {
            level = 3;
            dts.getLevel3Symptoms();
            result = dts.analyseSymptoms(level);
            dts.displayMessage(level, result);
        }
    }

    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();
    return 0;
}
