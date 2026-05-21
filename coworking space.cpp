#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <iomanip> 
#include <ctime>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

struct User {
    int ID = 0;
    string FirstName;
    string LastName;
    string Password;
    string Email;
    string Phone;
    string role;
};

struct Space {
    int SpaceID = 0;
    string Name;
    string Area;
    float PricePerHour = 0.0f;
    float Rating = 0.0f;
    int HasWifi = 0;
    int HasMeetingRoom = 0;
    int NoOfSeatAvailable = 0;
    string OpenTime;
    string CloseTime;
};

struct Booking {
    int BookingID = 0;
    int UserID = 0;
    int SpaceID = 0;
    string name;
    string phone;
    int Hours = 0;
    int Seats = 0;
    string Date;
    string Time;
    float TotalCost = 0.0f;
    float Rating = 0.0f;
};

User users[10];
string spaces2D[20][12];
Booking bookings[20];

int numUsers = 0;
int numSpaces = 0;
int numBookings = 0;
int currentUserID = -1;

////////////////////////////////////////////////////ADMIN////////////////////////////////////////////////////////
void addSpace();
void editspaces();
void ensureAdminExists();
void showAdminMenu();
void deleteSpace();
void load_space();
void save_space();
void viewallbookings();
////////////////////////////////////////////////////////////////////////////////////////
string getCurrentDay();
string getCurrentDate();
void initializeSpaces2D();
int convertTimeToInt(const string& timeStr);
void displayAvailableHours(const string& openTime, const string& closeTime);
bool Password(const string& p);
string PasswordHidden();
void displayHourlySlots(int spaceID, const string& date, const string& openTime, const string& closeTime);
bool isHourAvailable(int spaceID, const string& date, int hour);
bool selectTimeSlot(int spaceID, const string& date, const string& openTime, const string& closeTime, int& startHour, int& hours);
bool isValidSpaceIndex(int idx);
bool isValidDate(int day, int month, int year);
string correct_Date(string date);
////////////////////////////////////////////////////////////////////////////////////////
void load();
void save(const User& u);
void customerLogin();
void signup();
void viewAllSpaces();
void showCustomerMenu();
////////////////////////////////////////////////////////////////////////////////////////
void searchSpacesByArea();
void filterSpaces();
///////////////////////////////////////////////////////////////////////////////////////
Booking book_space(int space_id);
float calculateTotalCost(int space_id, int hours, int seats);
bool check_availability(int space_id, Booking& b);
void loadBookings();
void saveAllBookingsToFile();
void confirm_booking(Booking& b);
void bookASpace(int selectedID);
void viewMyBookings();
void Booking_cancellation();
void edit_booking();
void updateRating();
float Average_Rating(int space_id);

//========================================================================//

string getCurrentDay() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    string days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    return days[ltm.tm_wday];
}

string getCurrentDate() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    stringstream ss;
    ss << setw(2) << setfill('0') << ltm.tm_mday << "/"
        << setw(2) << setfill('0') << 1 + ltm.tm_mon << "/"
        << 1900 + ltm.tm_year;
    return ss.str();
}

void initializeSpaces2D() {
    numSpaces = 0;
    string currentDay = getCurrentDay();
    string currentDate = getCurrentDate();

    // NASRCITY
    spaces2D[0][0] = "1001"; spaces2D[0][1] = "ITCAN"; spaces2D[0][2] = "NASRCITY";
    spaces2D[0][3] = "150"; spaces2D[0][4] = "4.5"; spaces2D[0][5] = "1";
    spaces2D[0][6] = "1"; spaces2D[0][7] = "8";
    spaces2D[0][8] = "08:00"; spaces2D[0][9] = "20:00";
    spaces2D[0][10] = currentDay; spaces2D[0][11] = currentDate;
    numSpaces++;

    spaces2D[1][0] = "1002"; spaces2D[1][1] = "MAJAL"; spaces2D[1][2] = "NASRCITY";
    spaces2D[1][3] = "120"; spaces2D[1][4] = "4.3"; spaces2D[1][5] = "1";
    spaces2D[1][6] = "0"; spaces2D[1][7] = "7";
    spaces2D[1][8] = "09:00"; spaces2D[1][9] = "21:00";
    spaces2D[1][10] = currentDay; spaces2D[1][11] = currentDate;
    numSpaces++;

    // NEW CAIRO
    spaces2D[2][0] = "1003"; spaces2D[2][1] = "NEXT LEVEL"; spaces2D[2][2] = "NEW CAIRO";
    spaces2D[2][3] = "200"; spaces2D[2][4] = "4.8"; spaces2D[2][5] = "1";
    spaces2D[2][6] = "1"; spaces2D[2][7] = "10";
    spaces2D[2][8] = "10:00"; spaces2D[2][9] = "22:00";
    spaces2D[2][10] = currentDay; spaces2D[2][11] = currentDate;
    numSpaces++;

    // MID OF EGYPT
    spaces2D[3][0] = "1004"; spaces2D[3][1] = "THE HUB"; spaces2D[3][2] = "MID OF EGYPT";
    spaces2D[3][3] = "180"; spaces2D[3][4] = "4.6"; spaces2D[3][5] = "1";
    spaces2D[3][6] = "1"; spaces2D[3][7] = "6";
    spaces2D[3][8] = "07:00"; spaces2D[3][9] = "19:00";
    spaces2D[3][10] = currentDay; spaces2D[3][11] = currentDate;
    numSpaces++;

    // ZAMALIK
    spaces2D[4][0] = "1005"; spaces2D[4][1] = "CREATIVO"; spaces2D[4][2] = "ZAMALIK";
    spaces2D[4][3] = "160"; spaces2D[4][4] = "4.4"; spaces2D[4][5] = "1";
    spaces2D[4][6] = "0"; spaces2D[4][7] = "15";
    spaces2D[4][8] = "11:00"; spaces2D[4][9] = "23:00";
    spaces2D[4][10] = currentDay; spaces2D[4][11] = currentDate;
    numSpaces++;

    // SHOBRA
    spaces2D[5][0] = "1006"; spaces2D[5][1] = "MAKANAK"; spaces2D[5][2] = "SHOBRA";
    spaces2D[5][3] = "90"; spaces2D[5][4] = "4.0"; spaces2D[5][5] = "1";
    spaces2D[5][6] = "0"; spaces2D[5][7] = "11";
    spaces2D[5][8] = "06:00"; spaces2D[5][9] = "18:00";
    spaces2D[5][10] = currentDay; spaces2D[5][11] = currentDate;
    numSpaces++;

    // ZATON
    spaces2D[6][0] = "1007"; spaces2D[6][1] = "BAFAKAR"; spaces2D[6][2] = "ZATON";
    spaces2D[6][3] = "110"; spaces2D[6][4] = "4.2"; spaces2D[6][5] = "0";
    spaces2D[6][6] = "0"; spaces2D[6][7] = "13";
    spaces2D[6][8] = "09:00"; spaces2D[6][9] = "21:00";
    spaces2D[6][10] = currentDay; spaces2D[6][11] = currentDate;
    numSpaces++;

    // MAADI
    spaces2D[7][0] = "1008"; spaces2D[7][1] = "CTRL + P"; spaces2D[7][2] = "MAADI";
    spaces2D[7][3] = "140"; spaces2D[7][4] = "4.5"; spaces2D[7][5] = "1";
    spaces2D[7][6] = "1"; spaces2D[7][7] = "9";
    spaces2D[7][8] = "08:00"; spaces2D[7][9] = "20:00";
    spaces2D[7][10] = currentDay; spaces2D[7][11] = currentDate;
    numSpaces++;

    spaces2D[8][0] = "1009"; spaces2D[8][1] = "THE DISTRICT"; spaces2D[8][2] = "MAADI";
    spaces2D[8][3] = "170"; spaces2D[8][4] = "4.7"; spaces2D[8][5] = "1";
    spaces2D[8][6] = "1"; spaces2D[8][7] = "14";
    spaces2D[8][8] = "10:00"; spaces2D[8][9] = "22:00";
    spaces2D[8][10] = currentDay; spaces2D[8][11] = currentDate;
    numSpaces++;

    // HELWAN
    spaces2D[9][0] = "1010"; spaces2D[9][1] = "ESCACES"; spaces2D[9][2] = "HELWAN";
    spaces2D[9][3] = "80"; spaces2D[9][4] = "3.9"; spaces2D[9][5] = "0";
    spaces2D[9][6] = "0"; spaces2D[9][7] = "7";
    spaces2D[9][8] = "07:00"; spaces2D[9][9] = "19:00";
    spaces2D[9][10] = currentDay; spaces2D[9][11] = currentDate;
    numSpaces++;
}

int convertTimeToInt(const string& timeStr) {
    if (timeStr.empty() || timeStr.length() < 2) return -1;
    try {
        string hourStr = timeStr.substr(0, 2);
        return stoi(hourStr);
    }
    catch (...) {
        return -1;
    }
}

bool Password(const string& p) {
    if (p.size() < 8) return false;
    bool u = false, l = false, d = false, s = false;
    for (char c : p) {
        if (isupper(c)) u = true;
        else if (islower(c)) l = true;
        else if (isdigit(c)) d = true;
        else if (!isalnum(c)) s = true;
    }
    return u && l && d && s;
}

void displayAvailableHours(const string& openTime, const string& closeTime) {
    int openHour = convertTimeToInt(openTime);
    int closeHour = convertTimeToInt(closeTime);
    if (openHour == -1 || closeHour == -1) {
        cout << "\n   Invalid opening hours.\n";
        return;
    }
    cout << "\n   Available Hours:" << endl;
    cout << "   ";
    if (closeHour < openHour) {
        for (int h = openHour; h < 24; ++h) cout << setw(2) << setfill('0') << h << ":00   ";
        for (int h = 0; h < closeHour; ++h) cout << setw(2) << setfill('0') << h << ":00   ";
    }
    else {
        for (int h = openHour; h < closeHour; ++h) cout << setw(2) << setfill('0') << h << ":00   ";
    }
    cout << endl;
}

string PasswordHidden() {
    string pass;
    char ch;
    cout << "Password: ";
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && !pass.empty()) {
            cout << "\b \b";
            pass.pop_back();
        }
        else if (ch >= 32 && ch <= 126) {
            cout << '*';
            pass += ch;
        }
    }
    cout << endl;
    return pass;
}

bool isHourAvailable(int spaceID, const string& date, int hour) {
    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].SpaceID == spaceID && bookings[i].Date == date) {
            int start = stoi(bookings[i].Time);
            int end = start + bookings[i].Hours;
            if (hour >= start && hour < end) {
                return false;
            }
        }
    }
    return true;
}

void displayHourlySlots(int spaceID, const string& date, const string& openTime, const string& closeTime) {
    int openHour = convertTimeToInt(openTime);
    int closeHour = convertTimeToInt(closeTime);
    if (openHour == -1 || closeHour == -1) {
        cout << "\nInvalid operating hours for this space.\n";
        return;
    }

    cout << "\nHourly availability for " << date << ":\n";

    cout << "   ";
    for (int h = openHour; h < closeHour; ++h) {
        string hourStr;
        if (h < 10) hourStr = " " + to_string(h) + ":00";
        else hourStr = to_string(h) + ":00";
        cout << setw(6) << hourStr;
    }
    cout << "\n   ";

    for (int h = openHour; h < closeHour; ++h) {
        if (isHourAvailable(spaceID, date, h))
            cout << setw(6) << "[ ]";
        else
            cout << setw(6) << "[X]";
    }
    cout << "\n   [ ] = available, [X] = booked\n";
}

bool selectTimeSlot(int spaceID, const string& date, const string& openTime, const string& closeTime, int& startHour, int& hours) {
    int openHour = convertTimeToInt(openTime);
    int closeHour = convertTimeToInt(closeTime);
    if (openHour == -1 || closeHour == -1) {
        cout << "Invalid operating hours.\n";
        return false;
    }
    cout << "\nAvailable hours: ";
    for (int h = openHour; h < closeHour; ++h) {
        if (h < 10) cout << " " << h << ":00 ";
        else cout << h << ":00 ";
    }
    cout << endl;
    cout << "Enter start hour (e.g., 9 for 09:00): ";
    cin >> startHour;
    cout << "Enter number of hours: ";
    cin >> hours;
    cin.ignore();
    int endHour = startHour + hours;
    if (startHour < openHour || endHour > closeHour || hours <= 0) {
        cout << "Invalid time range. Must be within opening hours.\n";
        return false;
    }
    for (int h = startHour; h < endHour; ++h) {
        if (!isHourAvailable(spaceID, date, h)) {
            cout << "Sorry, the time slot from " << startHour << ":00 is not fully available.\n";
            return false;
        }
    }
    return true;
}

bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }

    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap) {
            if (day > 29) return false;
        }
        else {
            if (day > 28) return false;
        }
    }

    return true;
}

string correct_Date(string date) {
    stringstream ss(date);
    string dayStr, monthStr, yearStr;

    getline(ss, dayStr, '/');
    getline(ss, monthStr, '/');
    getline(ss, yearStr, '/');

    if (dayStr.empty() || monthStr.empty() || yearStr.empty()) {
        return "";
    }

    int day = stoi(dayStr);
    int month = stoi(monthStr);
    int year = stoi(yearStr);

    if (!isValidDate(day, month, year)) {
        return "";
    }

    if (dayStr.length() == 1) dayStr = "0" + dayStr;
    if (monthStr.length() == 1) monthStr = "0" + monthStr;

    return dayStr + "/" + monthStr + "/" + yearStr;
}

//========================================================================//

void load() {
    ifstream f("info.txt");
    if (!f) return;
    string line;
    numUsers = 0;
    while (getline(f, line) && numUsers < 10) {
        stringstream ss(line);
        string idStr, fname, lname, email, phone, pass, role;
        getline(ss, idStr, '|');
        getline(ss, fname, '|');
        getline(ss, lname, '|');
        getline(ss, email, '|');
        getline(ss, phone, '|');
        getline(ss, pass, '|');
        getline(ss, role, '|');

        if (idStr.empty()) continue;
        users[numUsers].ID = stoi(idStr);
        users[numUsers].FirstName = fname;
        users[numUsers].LastName = lname;
        users[numUsers].Email = email;
        users[numUsers].Phone = phone;
        users[numUsers].Password = pass;
        users[numUsers].role = role;

        numUsers++;
    }
}

void save(const User& u) {
    ofstream f("info.txt", ios::app);
    if (f) {
        f << u.ID << "|" << u.FirstName << "|" << u.LastName << "|"
            << u.Email << "|" << u.Phone << "|" << u.Password << "|" << u.role << "\n";
    }
}

void signup() {
    User u;
    string fname, lname, email, phone, pass1, pass2;
    int age;
    cout << "\n=== Sign Up ===\n";
    cout << "First name: "; getline(cin, fname);
    cout << "Last name: "; getline(cin, lname);
    do {
        cout << "Age: "; cin >> age; cin.ignore();
        if (age < 17) cout << "You must be at least 17 years old\n";
    } while (age < 17);
    cout << "Phone number: "; getline(cin, phone);
    cout << "Email: ";        getline(cin, email);
    do {
        cout << "Password: "; getline(cin, pass1);
        cout << "Confirm password: "; getline(cin, pass2);
        if (pass1 != pass2) cout << "Passwords do not match\n";
        else if (!Password(pass1)) cout << "Weak password (must be 8+ chars, uppercase, lowercase, digit, special char)\n";
    } while (pass1 != pass2 || !Password(pass1));
    u.ID = 1000 + rand() % 990000;
    u.FirstName = fname;
    u.LastName = lname;
    u.Email = email;
    u.Phone = phone;
    u.Password = pass1;
    u.role = "USER";

    if (numUsers < 10) {
        users[numUsers++] = u;
        save(u);
        cout << "Registration successful! Your ID: " << u.ID << "\n";
        currentUserID = u.ID;
    }
    else cout << "Maximum number of users reached\n";
}

bool isValidSpaceIndex(int idx) {
    return (idx >= 0 && idx < numSpaces && !spaces2D[idx][0].empty());
}

void viewAllSpaces() {
    if (numSpaces == 0) {
        cout << "\nNo spaces available at the moment.\n";
        return;
    }
    cout << "\n" << string(150, '=') << endl;
    cout << "                             ALL CO-WORKING SPACES" << endl;
    cout << string(150, '=') << endl;
    cout << left << setw(6) << "ID" << setw(15) << "Name" << setw(15) << "Area"
        << setw(12) << "Price/Hour" << setw(8) << "Rating" << setw(8) << "WiFi"
        << setw(14) << "Meeting Room" << setw(8) << "Seats" << setw(12) << "Open Time"
        << setw(12) << "Close Time" << setw(12) << "Day" << setw(12) << "Date" << endl;
    cout << string(150, '-') << endl;
    for (int i = 0; i < numSpaces; i++) {
        int currentID = stoi(spaces2D[i][0]);
        float liveRating = Average_Rating(currentID);
        cout << left << setw(6) << spaces2D[i][0] << setw(15) << spaces2D[i][1]
            << setw(15) << spaces2D[i][2] << setw(12) << spaces2D[i][3];
        if (liveRating == 0) cout << setw(8) << "No Rate";
        else cout << setw(8) << fixed << setprecision(1) << liveRating;
        cout << setw(8) << (spaces2D[i][5] == "1" ? "Yes" : "No")
            << setw(14) << (spaces2D[i][6] == "1" ? "Yes" : "No")
            << setw(8) << spaces2D[i][7] << setw(12) << spaces2D[i][8]
            << setw(12) << spaces2D[i][9] << setw(12) << spaces2D[i][10]
            << setw(12) << spaces2D[i][11] << endl;
    }
    cout << string(150, '=') << endl;

    int spaceChoice;
    cout << "\nEnter Space ID to view detailed schedule (or 0 to return): ";
    cin >> spaceChoice;

    float liveRating = Average_Rating(spaceChoice);

    cin.ignore();
    if (spaceChoice == 0) return;

    int spaceIndex = -1;
    for (int i = 0; i < numSpaces; i++) {
        if (stoi(spaces2D[i][0]) == spaceChoice) {
            spaceIndex = i;
            break;
        }
    }
    if (spaceIndex == -1 || !isValidSpaceIndex(spaceIndex)) {
        cout << "Space ID not found.\n";
        return;
    }


    cout << "\n***********************************************************************************************************" << endl;
    cout << "                                    DETAILED SPACE INFORMATION                                             " << endl;
    cout << "***********************************************************************************************************" << endl;
    cout << "ID:           " << spaces2D[spaceIndex][0] << endl
        << "Name:         " << spaces2D[spaceIndex][1] << endl
        << "Area:         " << spaces2D[spaceIndex][2] << endl
        << "Price/Hour:   " << spaces2D[spaceIndex][3] << " EGP" << endl
        << "Rating:       " << liveRating << endl
        << "WiFi:         " << (spaces2D[spaceIndex][5] == "1" ? "Yes" : "No") << endl
        << "Meeting Room: " << (spaces2D[spaceIndex][6] == "1" ? "Yes" : "No") << endl
        << "Seats:        " << spaces2D[spaceIndex][7] << endl
        << "Open Time:    " << spaces2D[spaceIndex][8] << endl
        << "Close Time:   " << spaces2D[spaceIndex][9] << endl
        << "Day:          " << spaces2D[spaceIndex][10] << endl
        << "Date:         " << spaces2D[spaceIndex][11] << endl;


    string selectedDate = spaces2D[spaceIndex][11];
    string openTime = spaces2D[spaceIndex][8];
    string closeTime = spaces2D[spaceIndex][9];
    if (openTime.empty() || closeTime.empty()) {
        cout << "\nError: Space operating hours not defined.\n";
        return;
    }
    displayHourlySlots(spaceChoice, selectedDate, openTime, closeTime);

    bool isAdmin = false;
    for (int i = 0; i < numUsers; i++) {
        if (users[i].ID == currentUserID && users[i].role == "ADMIN") {
            isAdmin = true;
            break;
        }
    }

    if (!isAdmin) {
        cout << "\nWould you like to book this space now?\n";
        cout << "1. Yes, book a time slot\n";
        cout << "2. No, return to menu\n";
        cout << "Enter choice: ";
        int bookChoice;
        cin >> bookChoice;
        cin.ignore();
        if (bookChoice == 1) {
            bookASpace(spaceChoice);
        }
        else {
            cout << "Returning to menu.\n";
        }
    }
}

void showCustomerMenu() {
    int choice;
    while (true) {
        cout << "\n=== Customer Menu ===\n";
        cout << "1. View All Spaces\n";
        cout << "2. Search Spaces by Area\n";
        cout << "3. Filter Spaces (Price/Rating/Facilities/Availability)\n";
        cout << "4. Book a Space\n";
        cout << "5. View My Bookings\n";
        cout << "6. Cancel a Booking\n";
        cout << "7. Rate a Booking\n";
        cout << "8. Edit a Booking\n";
        cout << "9. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:  viewAllSpaces();         break;
        case 2:  searchSpacesByArea();    break;
        case 3:  filterSpaces();          break;
        case 4:  bookASpace(-1);          break;
        case 5:  viewMyBookings();        break;
        case 6:  Booking_cancellation();  break;
        case 7:  updateRating();          break;
        case 8:  edit_booking();          break;
        case 9:  cout << "Logged out successfully.\n";
            saveAllBookingsToFile();
            currentUserID = -1;
            return;
        default: cout << "Invalid choice!\n";
        }
    }
}

void customerLogin() {
    string email, pass;

    cout << "\n=== Login ===\n";
    cout << "Email: ";
    getline(cin, email);

    pass = PasswordHidden();

    load();

    for (int i = 0; i < numUsers; i++) {
        if (users[i].Email == email && users[i].Password == pass) {
            cout << "Welcome " << users[i].FirstName << " " << users[i].LastName << "!\n";
            currentUserID = users[i].ID;

            if (users[i].role == "ADMIN") {
                showAdminMenu();
            }
            else {
                showCustomerMenu();
            }
            return;
        }
    }
    cout << "Invalid credentials\n";
}

//========================================================================//

//  ADMIN FUNCTIONS

//========================================================================//

void editspaces() {

    if (numSpaces == 0) {
        cout << "No spaces available to edit!\n";
        return;
    }

    string targetID;
    cout << "Enter Space ID to edit: ";
    cin >> targetID;

    bool found = false;
    for (int i = 0; i < numSpaces; i++) {
        if (spaces2D[i][0] == targetID) {
            found = true;
            int editChoice;

            cout << "Space Found: " << spaces2D[i][1] << endl;
            cout << "1. Edit Space ID\n";
            cout << "2. Edit Name\n";
            cout << "3. Edit Area\n";
            cout << "4. Edit Price Per Hour\n";
            cout << "5. Edit Wifi Status\n";
            cout << "6. Edit Meeting Room Status\n";
            cout << "7. Edit Number of Seats\n";
            cout << "8. Edit Opening Time\n";
            cout << "9. Edit Closing Time\n";
            cout << "10. Edit Everything\n";
            cout << "Enter your choice: ";
            cin >> editChoice;

            switch (editChoice) {
            case 1:
                cout << "Enter New Space ID: "; cin >> spaces2D[i][0];
                break;
            case 2:
                cout << "Enter Space Name: "; cin >> spaces2D[i][1];
                break;
            case 3:
                cout << "Enter Space Area: "; cin >> spaces2D[i][2];
                break;
            case 4:
                cout << "Enter Price Per Hour: "; cin >> spaces2D[i][3];
                break;
            case 5:
                cout << "Does it have Wifi? (1 for Yes / 0 for No): "; cin >> spaces2D[i][5];
                break;
            case 6:
                cout << "Does it have Meeting Room? (1 for Yes / 0 for No): "; cin >> spaces2D[i][6];
                break;
            case 7:
                cout << "Enter Number of Seats: "; cin >> spaces2D[i][7];
                break;
            case 8:
                cout << "Enter Opening Time: "; cin >> spaces2D[i][8];
                break;
            case 9:
                cout << "Enter Closing Time: "; cin >> spaces2D[i][9];
                break;
            case 10:
                cout << "Enter New Space ID: "; cin >> spaces2D[i][0];
                cout << "Enter Space Name: "; cin >> spaces2D[i][1];
                cout << "Enter Space Area: "; cin >> spaces2D[i][2];
                cout << "Enter Price Per Hour: "; cin >> spaces2D[i][3];
                cout << "Does it have Wifi? (1 for Yes / 0 for No): "; cin >> spaces2D[i][5];
                cout << "Does it have Meeting Room? (1 for Yes / 0 for No): "; cin >> spaces2D[i][6];
                cout << "Enter Number of Seats: "; cin >> spaces2D[i][7];
                cout << "Enter Opening Time: "; cin >> spaces2D[i][8];
                cout << "Enter Closing Time: "; cin >> spaces2D[i][9];
                break;
            default:
                cout << "Invalid choice!\n";
                break;
            }

            if (editChoice >= 1 && editChoice <= 10) {
                cout << "Space updated successfully!\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "Space ID not found!\n";
    }


}

void showAdminMenu() {
    int choice;

    while (true) {
        cout << "\n=== ADMIN MENU ===\n";
        cout << "1. View All Spaces\n";
        cout << "2. Add Space\n";
        cout << "3. Edit Space\n";
        cout << "4. Delete Space\n";
        cout << "5. View All Bookings\n";
        cout << "6. Logout\n";

        cout << "Enter your choice :";
        cin >> choice;
        cin.ignore();
        cout << endl;

        switch (choice) {
        case 1: viewAllSpaces();   break;
        case 2: addSpace();        break;
        case 3: editspaces();      break;
        case 4: deleteSpace();     break;
        case 5: viewallbookings(); break;
        case 6: cout << "Logged out successfully.\n";
            save_space();      return;
        default: cout << "Invalid\n";
        }
    }
}

void ensureAdminExists() {
    ifstream f("info.txt");
    string line;
    bool adminExists = false;

    while (getline(f, line)) {
        if (line.find("|ADMIN") != string::npos) {
            adminExists = true;
            break;
        }
    }
    f.close();

    if (!adminExists) {
        User admin;
        admin.ID = 1;
        admin.FirstName = "System";
        admin.LastName = "Admin";
        admin.Email = "admin@system.com";
        admin.Phone = "000";
        admin.Password = "Admin12$";
        admin.role = "ADMIN";

        save(admin);
    }
}

void addSpace()
{
    char repeat;
    do
    {
        if (numSpaces >= 20) {
            cout << "Storage Full!\n";
            break;
        }

        cout << "------- Add New Space -------\n";
        cout << "Enter Space ID: "; cin >> spaces2D[numSpaces][0];
        cout << "Enter Space Name: "; cin >> spaces2D[numSpaces][1];
        cout << "Enter Space Area: "; cin >> spaces2D[numSpaces][2];
        cout << "Enter Price Per Hour: "; cin >> spaces2D[numSpaces][3];

        spaces2D[numSpaces][4] = "0";

        cout << "Does it have Wifi? (1 for Yes / 0 for No): "; cin >> spaces2D[numSpaces][5];
        cout << "Does it have a Meeting Room? (1 for Yes / 0 for No): "; cin >> spaces2D[numSpaces][6];
        cout << "Enter Number of Seats: "; cin >> spaces2D[numSpaces][7];
        cout << "Enter Opening Time (e.g., 08:00): "; cin >> spaces2D[numSpaces][8];
        cout << "Enter Closing Time (e.g., 20:00): "; cin >> spaces2D[numSpaces][9];

        spaces2D[numSpaces][10] = getCurrentDay();
        spaces2D[numSpaces][11] = getCurrentDate();

        numSpaces++;

        cout << "Do you want another space? (Y => yes / N => no): ";
        cin >> repeat;

    } while (repeat == 'Y' || repeat == 'y');
}

void deleteSpace() {
    if (numSpaces == 0)
    {
        cout << "No spaces available to delete!\n";
        return;
    }

    string id_space;
    cout << "Enter Space ID to delete: ";
    cin >> id_space;
    int found = -1;

    for (int i = 0; i < numSpaces; i++)
    {
        if (spaces2D[i][0] == id_space)
        {
            found = i;
            break;
        }

    }

    if (found != -1)
    {
        for (int i = found; i < numSpaces - 1; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                spaces2D[i][j] = spaces2D[i + 1][j];
            }

        }
        numSpaces--;
        cout << "Space deleted successfully!\n";
    }
    else
    {
        cout << "Space ID not found!\n";
    }
}

void viewallbookings() {
    if (numBookings == 0) {
        cout << "No bookings found.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "           ALL BOOKINGS LIST           \n";
    cout << "========================================\n";

    for (int i = 0; i < numBookings; i++) {
        cout << "\n---------- Booking #" << i + 1 << " ----------\n";
        cout << "Booking ID: " << bookings[i].BookingID << endl;
        cout << "User ID: " << bookings[i].UserID << endl;
        cout << "Space ID: " << bookings[i].SpaceID << endl;
        cout << "Name: " << bookings[i].name << endl;
        cout << "Phone: " << bookings[i].phone << endl;
        cout << "Hours: " << bookings[i].Hours << endl;
        cout << "Seats: " << bookings[i].Seats << endl;
        cout << "Date: " << bookings[i].Date << endl;
        cout << "Time: " << bookings[i].Time << endl;
        cout << "Total Cost: " << bookings[i].TotalCost << " EGP" << endl;
        cout << "Rating: " << bookings[i].Rating << endl;
    }

    cout << "\n========================================\n";
    cout << "Total bookings: " << numBookings << endl;
    cout << "========================================\n";
}

void save_space() {
    ofstream file("space.txt");
    if (file.is_open())
    {
        for (int i = 0; i < numSpaces; i++)
        {
            file << spaces2D[i][0] << "|"
                << spaces2D[i][1] << "|"
                << spaces2D[i][2] << "|"
                << spaces2D[i][3] << "|"
                << spaces2D[i][4] << "|"
                << spaces2D[i][5] << "|"
                << spaces2D[i][6] << "|"
                << spaces2D[i][7] << "|"
                << spaces2D[i][8] << "|"
                << spaces2D[i][9] << "|" << endl;
        }
        file.close();
    }
    else
    {
        cout << "file is faild";
    }


}

void load_space() {
    ifstream file("space.txt");
    if (!file.is_open()) {
        return;
    }
    numSpaces = 0;
    string line;
    while (getline(file, line) && numSpaces < 20)
    {
        stringstream ss(line);
        string f_id, f_name, f_area, f_price, f_rate, f_wifi, f_room, f_seats, f_open, f_close;

        getline(ss, f_id, '|');
        getline(ss, f_name, '|');
        getline(ss, f_area, '|');
        getline(ss, f_price, '|');
        getline(ss, f_rate, '|');
        getline(ss, f_wifi, '|');
        getline(ss, f_room, '|');
        getline(ss, f_seats, '|');
        getline(ss, f_open, '|');
        getline(ss, f_close, '|');
        if (f_id.empty()) continue;

        spaces2D[numSpaces][0] = f_id;
        spaces2D[numSpaces][1] = f_name;
        spaces2D[numSpaces][2] = f_area;
        spaces2D[numSpaces][3] = f_price;
        spaces2D[numSpaces][4] = f_rate;
        spaces2D[numSpaces][5] = f_wifi;
        spaces2D[numSpaces][6] = f_room;
        spaces2D[numSpaces][7] = f_seats;
        spaces2D[numSpaces][8] = f_open;
        spaces2D[numSpaces][9] = f_close;
        spaces2D[numSpaces][10] = getCurrentDay();
        spaces2D[numSpaces][11] = getCurrentDate();
        numSpaces++;
    }
    file.close();

}

//========================================================================//

void displaySpaceDetails(int i) {
    float liveRating = Average_Rating(stoi(spaces2D[i][0]));

    cout << "\n" << string(80, '=') << endl;
    cout << "           CO-WORKING SPACE DETAILS" << endl;
    cout << string(80, '=') << endl;
    cout << "ID:          " << spaces2D[i][0] << endl
        << "Name:         " << spaces2D[i][1] << endl
        << "Area:         " << spaces2D[i][2] << endl
        << "Price/Hour:   " << spaces2D[i][3] << " EGP" << endl
        << "Rating:       " << liveRating << endl
        << "WiFi:         " << (spaces2D[i][5] == "1" ? "Yes" : "No") << endl
        << "Meeting Room: " << (spaces2D[i][6] == "1" ? "Yes" : "No") << endl
        << "Seats:        " << spaces2D[i][7] << endl
        << "Open Time:    " << spaces2D[i][8] << endl
        << "Close Time:   " << spaces2D[i][9] << endl
        << "Day:          " << spaces2D[i][10] << endl
        << "Date:         " << spaces2D[i][11] << endl;
    cout << string(80, '=') << endl;
}

void searchSpacesByArea() {
    string input;
    bool found = false;



    if (cin.peek() == '\n') cin.ignore();

    cout << "\n" << string(70, '=') << endl;
    cout << "                  SEARCH SPACES BY AREA" << endl;
    cout << string(70, '=') << endl;

    cout << "\nAvailable Areas:\n";
    string areas[20];
    int numAreas = 0;


    for (int i = 0; i < numSpaces; i++) {
        string current = spaces2D[i][2];
        bool exists = false;
        for (int j = 0; j < numAreas; j++) {
            if (areas[j] == current) {
                exists = true;
                break;
            }
        }
        if (!exists && !current.empty()) {
            areas[numAreas++] = current;
        }
    }

    for (int i = 0; i < numAreas; i++) {
        cout << "  " << i + 1 << ". " << areas[i] << endl;
    }

    do {
        cout << "\nEnter area name (or part of it): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "No input entered! Please try again.\n";
            continue;
        }


        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "nasr city" || input == "nasr" || input == "nasrcity") {
            found = true;
            string workspaceChoice;
            bool validWS = false;
            do {
                cout << "\nThe co-working spaces available in Nasr City: [ITCAN]    [MAJAL]" << endl;
                cout << "Enter your preferred co-working space: ";
                getline(cin, workspaceChoice);
                transform(workspaceChoice.begin(), workspaceChoice.end(), workspaceChoice.begin(), ::tolower);

                if (workspaceChoice == "itcan") {
                    validWS = true;
                    displaySpaceDetails(0);
                }
                else if (workspaceChoice == "majal") {
                    validWS = true;
                    displaySpaceDetails(1);
                }
                else {
                    cout << "[!] Invalid workspace! Please choose ITCAN or MAJAL." << endl;
                }
            } while (!validWS);
        }


        else if (input == "maadi" || input == "maa") {
            found = true;
            string workspaceChoice;
            bool validWS = false;
            do {
                cout << "\nThe co-working spaces available in MAADI: [CTRL + P ]    [THE DISTRICT]" << endl;
                cout << "Enter your preferred co-working space: ";
                getline(cin, workspaceChoice);
                transform(workspaceChoice.begin(), workspaceChoice.end(), workspaceChoice.begin(), ::tolower);

                if (workspaceChoice == "ctrl + p") {
                    validWS = true;
                    displaySpaceDetails(7);
                }
                else if (workspaceChoice == "the district") {
                    validWS = true;
                    displaySpaceDetails(8);
                }
                else {
                    cout << "[!] Invalid workspace! Please choose CTRL + P or THE DISTRICT." << endl;
                }
            } while (!validWS);
        }

        else {
            for (int i = 0; i < numSpaces; i++) {
                string spaceArea = spaces2D[i][2];
                string lowerArea = spaceArea;
                transform(lowerArea.begin(), lowerArea.end(), lowerArea.begin(), ::tolower);


                if (lowerArea.find(input) != string::npos) {
                    if (!found) {
                        cout << "\n" << string(90, '-') << endl;
                        cout << " Search Results for: \"" << input << "\"" << endl;
                        cout << string(90, '-') << endl;
                    }
                    found = true;
                    displaySpaceDetails(i);
                }
            }
        }

        if (!found) {
            cout << "\n[!] Sorry, no spaces found matching: \"" << input << "\"\n";
            cout << "Please try typing another area from the list above.\n";

            cin.clear();
        }

    } while (!found);
}

void filterSpaces() {
    int user_filter;
    string maxprice;
    string minimumrating;
    int Wifi;

    cout << "*****************************************************************************************************" << endl;
    cout << "                                                     Filter by :                                        " << endl;
    cout << "*****************************************************************************************************" << endl;
    cout << "Choose \n 1) Price \n 2) Wifi \n 3) Rating \n 4) Seats \n" << endl;
    cout << "Choose number : ";
    cin >> user_filter;

    auto printHeader = []() {
        cout << "\n" << left << setw(15) << "Name" << setw(10) << "ID" << "Rating" << endl;
        cout << string(35, '-') << endl;
        };

    switch (user_filter) {
    case 1: {
        bool flag;
        while (true) {
            flag = false;
            cout << "Enter your preferred max price: ";
            cin >> maxprice;
            printHeader();
            for (int i = 0; i < numSpaces; i++) {
                if (stoi(spaces2D[i][3]) <= stoi(maxprice)) {
                    float liveRating = Average_Rating(stoi(spaces2D[i][0]));
                    cout << left << setw(15) << spaces2D[i][1]
                        << setw(10) << spaces2D[i][0];
                    if (liveRating == 0)
                        cout << "No Rate" << endl;
                    else
                        cout << fixed << setprecision(1) << liveRating << "/5" << endl;
                    flag = true;
                }
            }
            if (flag) break;
            else cout << "This price not found!" << endl;
        }
        break;
    }

    case 2: {
        cout << "Do you want Wifi(1/2): \n1) Yes \n2) No" << endl;
        cin >> Wifi;
        printHeader();
        if (Wifi == 1) {
            for (int i = 0; i < numSpaces; i++) {
                if (spaces2D[i][5] == "1") {
                    float liveRating = Average_Rating(stoi(spaces2D[i][0]));
                    cout << left << setw(15) << spaces2D[i][1]
                        << setw(10) << spaces2D[i][0];
                    if (liveRating == 0)
                        cout << "No Rate" << endl;
                    else
                        cout << fixed << setprecision(1) << liveRating << "/5" << endl;
                }
            }
        }
        else {
            for (int i = 0; i < numSpaces; i++) {
                if (spaces2D[i][5] == "0") {
                    float liveRating = Average_Rating(stoi(spaces2D[i][0]));
                    cout << left << setw(15) << spaces2D[i][1]
                        << setw(10) << spaces2D[i][0];
                    if (liveRating == 0)
                        cout << "No Rate" << endl;
                    else
                        cout << fixed << setprecision(1) << liveRating << "/5" << endl;
                }
            }
        }
        break;
    }

    case 3: {
        cout << "Enter your preferred minimum Rating (e.g. 4.0): ";
        cin >> minimumrating;
        printHeader();
        bool found = false;
        for (int i = 0; i < numSpaces; i++) {
            float liveRating = Average_Rating(stoi(spaces2D[i][0]));
            if (liveRating >= stof(minimumrating)) {
                cout << left << setw(15) << spaces2D[i][1]
                    << setw(10) << spaces2D[i][0];
                if (liveRating == 0)
                    cout << "No Rate" << endl;
                else
                    cout << fixed << setprecision(1) << liveRating << "/5" << endl;
                found = true;
            }
        }
        if (!found) cout << "Sorry, no spaces found with this rating or higher.\n";
        break;
    }

    case 4: {
        int HasMeetingRoom;
        cout << "Do you want MeetingRoom(1/2):? \n1) Yes, I do \n2) No, I don't \n";
        cin >> HasMeetingRoom;
        printHeader();
        if (HasMeetingRoom == 1) {
            cout << "\n--- Spaces WITH Meeting Rooms ---\n";
            for (int i = 0; i < numSpaces; i++) {
                if (spaces2D[i][6] == "1") {
                    float liveRating = Average_Rating(stoi(spaces2D[i][0]));
                    cout << left << setw(15) << spaces2D[i][1]
                        << setw(10) << spaces2D[i][0];
                    if (liveRating == 0)
                        cout << "No Rate" << endl;
                    else
                        cout << fixed << setprecision(1) << liveRating << "/5" << endl;
                }
            }
        }
        else {
            cout << "\n--- Spaces WITHOUT Meeting Rooms ---\n";
            for (int i = 0; i < numSpaces; i++) {
                if (spaces2D[i][6] == "0") {
                    float liveRating = Average_Rating(stoi(spaces2D[i][0]));
                    cout << left << setw(15) << spaces2D[i][1]
                        << setw(10) << spaces2D[i][0];
                    if (liveRating == 0)
                        cout << "No Rate" << endl;
                    else
                        cout << fixed << setprecision(1) << liveRating << "/5" << endl;
                }
            }
        }
        break;
    }

    default:
        cout << "Invalid choice!\n";
    }
}//========================================================================//

//========================================================================//

void saveAllBookingsToFile() {
    ofstream outfile("bookings.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < numBookings; i++) {
            outfile << bookings[i].UserID << "|"
                << bookings[i].BookingID << "|"
                << bookings[i].SpaceID << "|"
                << bookings[i].name << "|"
                << bookings[i].phone << "|"
                << bookings[i].Hours << "|"
                << bookings[i].Seats << "|"
                << bookings[i].Date << "|"
                << bookings[i].Time << "|"
                << bookings[i].TotalCost << "|"
                << bookings[i].Rating << endl;
        }
        outfile.close();
    }
}

void loadBookings() {
    ifstream file("bookings.txt");
    if (!file.is_open()) {
        numBookings = 0;
        return;
    }

    string line;
    numBookings = 0;
    while (getline(file, line) && numBookings < 20) {
        stringstream ss(line);
        string f_uID, f_bID, f_sID, f_name, f_phone, f_hours, f_seats, f_date, f_time, f_cost, f_rating;

        getline(ss, f_uID, '|');
        getline(ss, f_bID, '|');
        getline(ss, f_sID, '|');
        getline(ss, f_name, '|');
        getline(ss, f_phone, '|');
        getline(ss, f_hours, '|');
        getline(ss, f_seats, '|');
        getline(ss, f_date, '|');
        getline(ss, f_time, '|');
        getline(ss, f_cost, '|');
        getline(ss, f_rating, '|');
        if (f_uID.empty()) continue;

        bookings[numBookings].UserID = stoi(f_uID);
        bookings[numBookings].BookingID = stoi(f_bID);
        bookings[numBookings].SpaceID = stoi(f_sID);
        bookings[numBookings].name = f_name;
        bookings[numBookings].phone = f_phone;
        bookings[numBookings].Hours = stoi(f_hours);
        bookings[numBookings].Seats = stoi(f_seats);
        bookings[numBookings].Date = f_date;
        bookings[numBookings].Time = f_time;
        bookings[numBookings].TotalCost = stof(f_cost);
        bookings[numBookings].Rating = stof(f_rating);
        numBookings++;
    }
    file.close();
}

//========================================================================//

Booking book_space(int space_id) {
    Booking person;
    person.SpaceID = space_id;
    person.UserID = currentUserID;

    for (int i = 0; i < numUsers; i++) {
        if (users[i].ID == currentUserID) {
            person.name = users[i].FirstName + " " + users[i].LastName;
            person.phone = users[i].Phone;
            break;
        }
    }

    int availableSeats = -1;
    int openHour = -1;
    int closeHour = -1;

    for (int i = 0; i < numSpaces; i++) {
        if (stoi(spaces2D[i][0]) == space_id) {
            availableSeats = stoi(spaces2D[i][7]);
            openHour = convertTimeToInt(spaces2D[i][8]);
            closeHour = convertTimeToInt(spaces2D[i][9]);
            break;
        }
    }

    if (availableSeats == -1 || openHour == -1 || closeHour == -1) {
        cout << "Error: Space not found.\n";
        return person;
    }

    cin.ignore(1000, '\n');

    cout << "\n--- Enter Booking Details ---\n";

    cout << "Enter date (day/month/year): ";
    getline(cin, person.Date);
    person.Date = correct_Date(person.Date);

    while (person.Date.empty()) {
        cout << "Date cannot be empty. Please enter again: ";
        getline(cin, person.Date);
        person.Date = correct_Date(person.Date);
    }

    cout << "Enter start time (in 24h format, e.g., 14 for 2:00 PM). Space open from " << openHour << ":00 to " << closeHour << ":00: ";
    cin >> person.Time;
    while (cin.fail() || person.Time.empty()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid time. Please enter a number (e.g., 14): ";
        cin >> person.Time;
    }

    int timeAsInt = stoi(person.Time);
    while (timeAsInt < openHour || timeAsInt >= closeHour) {
        cout << "Invalid time. Space is open from " << openHour << ":00 to " << closeHour << ":00. Please enter again: ";
        cin >> person.Time;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        timeAsInt = stoi(person.Time);
    }

    int maxAllowedHours = closeHour - timeAsInt;

    cout << "Enter number of hours required (max " << maxAllowedHours << "): ";
    cin >> person.Hours;
    while (cin.fail() || person.Hours <= 0 || person.Hours > maxAllowedHours) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid hours. Must be between 1 and " << maxAllowedHours << ". Please enter again: ";
        cin >> person.Hours;
    }

    do {
        cout << "Enter number of seats (available seats: " << availableSeats << "): ";
        cin >> person.Seats;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. ";
            continue;
        }
        if (person.Seats <= 0 || person.Seats > availableSeats) {
            cout << "Invalid number. Please enter a value between 1 and " << availableSeats << ".\n";
        }
    } while (person.Seats <= 0 || person.Seats > availableSeats);

    return person;
}

float calculateTotalCost(int space_id, int hours, int seats) {
    float pricePerHour = 0.0f;
    for (int i = 0; i < numSpaces; i++) {
        if (stoi(spaces2D[i][0]) == space_id) {
            pricePerHour = stof(spaces2D[i][3]);
            break;
        }
    }
    return pricePerHour * hours * seats;
}

bool check_availability(int space_id, Booking& b) {
    int start = stoi(b.Time);
    int end = start + b.Hours;

    for (int i = 0; i < numBookings; i++)
    {
        int bookedStart = stoi(bookings[i].Time);
        int bookedEnd = bookedStart + bookings[i].Hours;

        if (bookings[i].SpaceID == space_id && bookings[i].Date == b.Date && (start < bookedEnd && end > bookedStart)) {

            return false;
        }

    }

    return true;

}

void confirm_booking(Booking& b) {
    b.BookingID = 1000 + rand() % 9000;
    b.TotalCost = calculateTotalCost(b.SpaceID, b.Hours, b.Seats);
    b.UserID = currentUserID;
    b.Rating = 0.0f;

    if (numBookings < 20) {
        bookings[numBookings] = b;
        numBookings++;
        saveAllBookingsToFile();

        cout << "\n========================================" << endl;
        cout << "         RESERVATION SUCCESSFUL!        " << endl;
        cout << "  Booking ID   : " << b.BookingID << endl;
        cout << "  Customer     : " << b.name << endl;
        cout << "  Total Cost   : " << b.TotalCost << " EGP" << endl;
        cout << "========================================" << endl;
    }
    else {
        cout << "Error: Could not save booking to file.\n";
    }
}

void bookASpace(int selectedID) {
    int space_id = selectedID;

    if (space_id == -1) {
        cout << "Enter Space ID to book: ";
        cin >> space_id;
    }

    if (currentUserID == -1) {
        cout << "Access Denied: Please login first.\n";
        return;
    }

    Booking currentBooking = book_space(space_id);

    if (currentBooking.SpaceID == 0) {
        cout << "Booking failed: Invalid space ID.\n";
        return;
    }

    if (check_availability(space_id, currentBooking)) {
        confirm_booking(currentBooking);
    }
    else {
        cout << "\n[!] Sorry, this space is already occupied at this time.\n";
    }
}

//========================================================================//

void updateRating() {
    int target_id;
    cout << "Enter Booking ID to rate: ";
    cin >> target_id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input.\n";
        return;
    }

    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].BookingID == target_id) {
            if (bookings[i].UserID != currentUserID) {
                cout << "This booking cannot be rated by you!" << endl;
                return;
            }

            if (bookings[i].Rating > 0) {
                cout << "This booking has already been rated (" << bookings[i].Rating << ").\n";
                char confirm;
                cout << "Do you want to update the rating? (y/n): ";
                cin >> confirm;
                if (confirm != 'y' && confirm != 'Y') {
                    cout << "Rating update cancelled.\n";
                    return;
                }
            }

            float rating;
            cout << "Enter your rating (1.0 to 5.0): ";
            cin >> rating;

            while (cin.fail() || rating < 1.0 || rating > 5.0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid rating. Please enter a number between 1.0 and 5.0: ";
                cin >> rating;
            }

            bookings[i].Rating = rating;
            cout << "Rating updated successfully!" << endl;
            saveAllBookingsToFile();
            return;
        }
    }
    cout << "Booking ID not found." << endl;
}

float Average_Rating(int space_id) {
    int count = 0;
    float sum = 0.0f;

    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].SpaceID == space_id && bookings[i].Rating > 0) {
            sum += bookings[i].Rating;
            count++;
        }
    }

    if (count == 0) return 0.0f;
    return sum / count;
}

//========================================================================//

void Booking_cancellation() {
    int targetID;
    cout << "Enter Booking ID to cancel: ";
    cin >> targetID;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input.\n";
        return;
    }

    int delete_index = -1;

    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].BookingID == targetID) {
            if (bookings[i].UserID != currentUserID) {
                cout << "You cannot cancel this booking. It does not belong to you.\n";
                return;
            }
            delete_index = i;
            break;
        }
    }

    if (delete_index == -1) {
        cout << "Booking ID " << targetID << " not found.\n";
        return;
    }

    for (int i = delete_index; i < numBookings - 1; i++) {
        bookings[i] = bookings[i + 1];
    }
    numBookings--;
    saveAllBookingsToFile();
    cout << "Booking ID " << targetID << " has been successfully cancelled.\n";
}

void edit_booking() {
    int targetID;
    cout << "Enter Booking ID to edit: ";
    cin >> targetID;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input.\n";
        return;
    }

    int edit_index = -1;

    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].BookingID == targetID) {
            if (bookings[i].UserID != currentUserID) {
                cout << "You cannot edit this booking. It does not belong to you.\n";
                return;
            }
            edit_index = i;
            break;
        }
    }

    if (edit_index == -1) {
        cout << "Booking ID " << targetID << " not found.\n";
        return;
    }

    Booking& oldBooking = bookings[edit_index];

    int openHour = -1;
    int closeHour = -1;
    int availableSeats = -1;

    for (int i = 0; i < numSpaces; i++) {
        if (stoi(spaces2D[i][0]) == oldBooking.SpaceID) {
            openHour = convertTimeToInt(spaces2D[i][8]);
            closeHour = convertTimeToInt(spaces2D[i][9]);
            availableSeats = stoi(spaces2D[i][7]);
            break;
        }
    }

    if (openHour == -1 || closeHour == -1 || availableSeats == -1) {
        cout << "Error: Space not found.\n";
        return;
    }

    cout << "\n========== Current Booking Info ==========\n";
    cout << "Space ID: " << oldBooking.SpaceID << endl;
    cout << "Date: " << oldBooking.Date << endl;
    cout << "Time: " << oldBooking.Time << endl;
    cout << "Hours: " << oldBooking.Hours << endl;
    cout << "Seats: " << oldBooking.Seats << endl;
    cout << "Rating: " << oldBooking.Rating << endl;
    cout << "===========================================\n\n";

    cout << "Enter new booking details (press Enter to keep current value):\n";

    cin.ignore(1000, '\n');

    string new_date = oldBooking.Date;
    string new_time = oldBooking.Time;
    int new_hours = oldBooking.Hours;
    int new_seats = oldBooking.Seats;

    string input_line;


    cout << "Date [" << oldBooking.Date << "]: ";
    getline(cin, input_line);
    if (!input_line.empty()) {
        new_date = correct_Date(input_line);
        while (new_date.empty()) {
            cout << "Invalid date. Please enter again (day/month/year): ";
            getline(cin, input_line);
            new_date = correct_Date(input_line);
        }
    }


    cout << "Time [" << oldBooking.Time << "]: ";
    getline(cin, input_line);
    if (!input_line.empty()) {
        new_time = input_line;
        int timeAsInt = stoi(new_time);
        while (timeAsInt < openHour || timeAsInt >= closeHour) {
            cout << "Invalid time. Space is open from " << openHour << ":00 to " << closeHour << ":00. Please enter again: ";
            getline(cin, input_line);
            if (input_line.empty()) {
                new_time = oldBooking.Time;
                break;
            }
            new_time = input_line;
            timeAsInt = stoi(new_time);
        }
    }


    int timeAsInt = stoi(new_time);
    int maxAllowedHours = closeHour - timeAsInt;

    cout << "Hours [max " << maxAllowedHours << "] [" << oldBooking.Hours << "]: ";
    getline(cin, input_line);

    if (input_line.empty()) {
        if (oldBooking.Hours <= maxAllowedHours) {
            new_hours = oldBooking.Hours;
        }
        else {
            cout << "Old value (" << oldBooking.Hours << ") is not valid. Please enter new hours (between 1 and " << maxAllowedHours << "): ";
            getline(cin, input_line);
            while (input_line.empty() || stoi(input_line) <= 0 || stoi(input_line) > maxAllowedHours) {
                cout << "Invalid. Must be between 1 and " << maxAllowedHours << ": ";
                getline(cin, input_line);
            }
            new_hours = stoi(input_line);
        }
    }
    else {
        new_hours = stoi(input_line);
        while (new_hours <= 0 || new_hours > maxAllowedHours) {
            cout << "Invalid hours. Must be between 1 and " << maxAllowedHours << ": ";
            getline(cin, input_line);
            new_hours = stoi(input_line);
        }
    }


    int start = stoi(new_time);
    int end = start + new_hours;
    bool available = true;

    for (int i = 0; i < numBookings; i++) {
        if (i == edit_index) continue;

        if (bookings[i].SpaceID == oldBooking.SpaceID && bookings[i].Date == new_date) {
            int bookedStart = stoi(bookings[i].Time);
            int bookedEnd = bookedStart + bookings[i].Hours;

            if (start < bookedEnd && end > bookedStart) {
                available = false;
                break;
            }
        }
    }

    if (!available) {
        cout << "\nSorry, this space is not available at the requested time.\n";
        return;
    }


    cout << "Seats [max " << availableSeats << "] [" << oldBooking.Seats << "]: ";
    getline(cin, input_line);
    if (!input_line.empty()) {
        new_seats = stoi(input_line);
        while (new_seats <= 0 || new_seats > availableSeats) {
            cout << "Invalid seats. Must be between 1 and " << availableSeats << ". Please enter again: ";
            getline(cin, input_line);
            if (input_line.empty()) {
                new_seats = oldBooking.Seats;
                break;
            }
            new_seats = stoi(input_line);
        }
    }


    float new_cost = calculateTotalCost(oldBooking.SpaceID, new_hours, new_seats);

    oldBooking.Date = new_date;
    oldBooking.Time = new_time;
    oldBooking.Hours = new_hours;
    oldBooking.Seats = new_seats;
    oldBooking.TotalCost = new_cost;
    saveAllBookingsToFile();

    cout << "\n========================================\n";
    cout << "     BOOKING MODIFIED SUCCESSFULLY!     \n";
    cout << "========================================\n";
    cout << "  Booking ID:   " << targetID << endl;
    cout << "  Date:         " << new_date << endl;
    cout << "  Time:         " << new_time << endl;
    cout << "  Hours:        " << new_hours << endl;
    cout << "  Seats:        " << new_seats << endl;
    cout << "  Total Cost:   " << new_cost << " EGP" << endl;
    cout << "========================================\n";
}

//========================================================================//

void viewMyBookings() {
    if (currentUserID == -1) { cout << "You are not logged in.\n"; return; }

    int userBookingIndices[20];
    int userBookingCount = 0;

    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].UserID == currentUserID) userBookingIndices[userBookingCount++] = i;
    }

    if (userBookingCount == 0) { cout << "\nNo bookings found for you.\n"; return; }

    cout << "\n=== Your Bookings ===\n";

    for (int j = 0; j < userBookingCount; j++) {
        int idx = userBookingIndices[j];
        cout << "Booking ID: " << bookings[idx].BookingID
            << " | Space ID: " << bookings[idx].SpaceID
            << " | Date: " << bookings[idx].Date
            << " | Time: " << bookings[idx].Time
            << " | Total Cost: " << bookings[idx].TotalCost << " EGP\n";
    }

    int selectedBookingID;
    cout << "\nEnter Booking ID to view details (or 0 to cancel): ";
    cin >> selectedBookingID;
    cin.ignore();
    if (selectedBookingID == 0) return;
    int foundIdx = -1;
    for (int i = 0; i < numBookings; i++) {
        if (bookings[i].BookingID == selectedBookingID && bookings[i].UserID == currentUserID) {
            foundIdx = i; break;
        }
    }
    if (foundIdx == -1) { cout << "Booking ID not found or does not belong to you.\n"; return; }
    Booking& b = bookings[foundIdx];
    cout << "\n=== Booking Details ===\n";
    cout << "Booking ID:   " << b.BookingID << endl
        << "User ID:      " << b.UserID << endl
        << "Space ID:     " << b.SpaceID << endl
        << "Hours:        " << b.Hours << endl
        << "Seats:        " << b.Seats << endl
        << "Date:         " << b.Date << endl
        << "Time:         " << b.Time << endl
        << "Total Cost:   " << b.TotalCost << " EGP" << endl;

}

//========================================================================//

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    load();
    initializeSpaces2D();
    loadBookings();
    load_space();
    int choice;
    ensureAdminExists();
    while (true) {
        cout << "\n****************************************\n";
        cout << "*      Co-Working Space Finder         *\n";
        cout << "****************************************\n";
        cout << "\n1. Login\n2. Sign Up\n3. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: customerLogin(); break;
        case 2: signup(); break;
        case 3: cout << "Thank you! Goodbye.\n"; return 0;
        default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}

