#include <conio.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

static int p = 0;

class a {
    char roomn[5], room_name[20], host[10];
    int start_hr, start_min, end_hr, end_min, chair_capacity;
    char **chair;
public:
    a() : chair(nullptr), chair_capacity(32) {}  // Default chair capacity
    void setRoom();
    void reserveSlot();
    void empty();
    void showAllRooms();
    void roomCapacityAvailable();
    void position(int i);
    int remainingChairs();  // Function to calculate remaining chairs
    void showRoomDetails(); // Function to show complete details of a room
    ~a();  // Destructor to free dynamically allocated memory
} room[10];

a::~a() {
    if (chair != nullptr) {
        for (int i = 0; i < 8; i++)
            delete[] chair[i];
        delete[] chair;
    }
}

void vline(char ch) {
    for (int i = 80; i > 0; i--)
        cout << ch;
}

void a::setRoom() {
    cout << "Enter Room no: ";
    cin >> room[p].roomn;
    cout << "Enter Room name: ";
    cin.ignore(); // Clear the newline left in the buffer
    cin.getline(room[p].room_name, 20);
    cout << "Enter Host's name: ";
    cin >> room[p].host;
    cout << "Enter Start time (HH MM): ";
    cin >> room[p].start_hr >> room[p].start_min;
    cout << "Enter Session End time (HH MM): ";
    cin >> room[p].end_hr >> room[p].end_min;
    cout << "Enter the chair capacity (max 32): ";
    cin >> room[p].chair_capacity;
    if (room[p].chair_capacity > 32) {
        room[p].chair_capacity = 32;  // Ensure capacity doesn't exceed 32
    }

    // Allocate memory for chairs based on the capacity
    room[p].chair = new char*[8];
    for (int i = 0; i < 8; i++) {
        room[p].chair[i] = new char[4 * 10];
    }

    room[p].empty();
    p++;
}

void a::reserveSlot() {
    int chair;
    char number[5];
top:
    cout << "Room no: ";
    cin >> number;
    int n;
    for (n = 0; n < p; n++) {
        if (strcmp(room[n].roomn, number) == 0)
            break;
    }
    if (n >= p) {
        cout << "Enter correct Room no.\n";
        goto top;
    }

    while (true) {
        cout << "\nChair Number: ";
        cin >> chair;
        if (chair > room[n].chair_capacity) {
            cout << "\nThere are only " << room[n].chair_capacity << " chairs available in this Room.\n";
        } else {
            if (strcmp(&room[n].chair[chair / 4][(chair % 4 - 1) * 10], "Empty") == 0) {
                cout << "Enter passenger's name: ";
                cin >> &room[n].chair[chair / 4][(chair % 4 - 1) * 10];
                break;
            } else {
                cout << "The Chair no. is already reserved.\n";
            }
        }
    }
}

void a::empty() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(&room[p].chair[i][j * 10], "Empty");
        }
    }
}

void a::showAllRooms() {
    if (p == 0) {
        cout << "All rooms available for booking\n";
    } else {
        for (int n = 0; n < p; n++) {
            vline('*');
            cout << "\nRoom no: \t" << room[n].roomn
                 << "\nRoom name: \t" << room[n].room_name
                 << "\nHost: \t" << room[n].host << "\t\tStart time: \t"
                 << room[n].start_hr << ":" << room[n].start_min << "\tEnd time: " << room[n].end_hr << ":" << room[n].end_min
                 << "\n";
            vline('*');
        }
    }
}

void a::position(int n) {
    int s = 0, p = 0;
    for (int i = 0; i < 8; i++) {
        cout << "\n";
        for (int j = 0; j < 4; j++) {
            s++;
            if (strcmp(&room[n].chair[i][j * 10], "Empty") == 0) {
                cout.width(5);
                cout.fill(' ');
                cout << s << ".";
                cout.width(18);
                cout.fill(' ');
                cout << &room[n].chair[i][j * 10];
                p++;
            } else {
                cout.width(5);
                cout.fill(' ');
                cout << s << ".";
                cout.width(18);
                cout.fill(' ');
                cout << &room[n].chair[i][j * 10];
            }
            if (s >= room[n].chair_capacity) break;  // Stop if capacity is reached
        }
        if (s >= room[n].chair_capacity) break;  // Stop if capacity is reached
    }
    cout << "\n\nThere are " << p << " Chairs empty in Room No: " << room[n].roomn;
}

int a::remainingChairs() {
    int remaining = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(&chair[i][j * 10], "Empty") == 0) {
                remaining++;
            }
        }
    }
    return remaining;
}

void a::roomCapacityAvailable() {
    for (int n = 0; n < p; n++) {
        vline('*');
        cout << "\nRoom no: \t" << room[n].roomn
             << "\nRoom name: \t" << room[n].room_name
             << "\nHost: \t" << room[n].host << "\t\tStart time: \t"
             << room[n].start_hr << ":" << room[n].start_min << "\tEnd Time: \t" << room[n].end_hr << ":" << room[n].end_min
             << "\nTotal Remaining Chairs: \t" << room[n].remainingChairs()
             << "\n";
        vline('*');
    }
}

void a::showRoomDetails() {
    char number[5];
    cout << "Enter Room no: ";
    cin >> number;
    int n;
    for (n = 0; n < p; n++) {
        if (strcmp(room[n].roomn, number) == 0)
            break;
    }
    if (n >= p) {
        cout << "Enter correct Room no.\n";
        return;
    }

    vline('*');
    cout << "\nRoom no: \t" << room[n].roomn
         << "\nRoom name: \t" << room[n].room_name
         << "\nHost: \t" << room[n].host << "\t\tStart time: \t"
         << room[n].start_hr << ":" << room[n].start_min << "\tEnd time: " << room[n].end_hr << ":" << room[n].end_min
         << "\nTotal Remaining Chairs: \t" << room[n].remainingChairs()
         << "\n";
    vline('*');
    room[n].position(n);
}

int main() {
    system("cls");
    int w;
    while (1) {
        // system("cls");
        cout << "\n\n\n\n\n";
        cout << "\t\t\t1.All Rooms\n\t\t\t"
             << "2.Set the Room\n\t\t\t"
             << "3.Reserve a Slot\n\t\t\t"
             << "4.Room Capacity Available\n\t\t\t"
             << "5.Check Room Details\n\t\t\t"
             << "6.Exit\n";
        cout << "\n\t\t\tEnter your choice:->";
        cin >> w;
        switch (w) {
            case 1: room[0].showAllRooms();
                    break;
            case 2: room[p].setRoom();
                    break;
            case 3: room[p].reserveSlot();
                    break;
            case 4: room[0].roomCapacityAvailable();
                    break;
            case 5: room[0].showRoomDetails();
                    break;
            case 6: exit(0);
        }
    }
    return 0;
}
