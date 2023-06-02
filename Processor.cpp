#include "Processor.h"
//Overload constructor that populates m_filename
Processor::Processor(string filename) {
    m_fileName = filename;
}
// Destructor that deletes both the vectors with for loops
Processor::~Processor() {
    for (unsigned int i = 0; i < m_processes.size(); i++) {
        delete m_processes.at(i);
    }
    for (unsigned int i = 0; i < m_threads.size(); i++) {
        delete m_threads.at(i);
    }
}
// Calling all these functions
void Processor::InitializeProcessor() {

    DisplayTitle();
    LoadProcesses(m_fileName);
    PopulateThreads();
    MainMenu();

}
// Opens the file and dynamilcally allocated to the Process Pointer
bool Processor::LoadProcesses(string filename) {
    ifstream myfile;

    string name = "";
    string id = "";
    string call = "";
    string duration = "";

    myfile.open(filename);
    if (myfile.is_open()) {
        // use getline to get the entire line than use delimiter to break them into their variables
        while (getline(myfile, name, DELIMITER)) {
            (getline(myfile, id, DELIMITER));
            (getline(myfile, call, DELIMITER));
            (getline(myfile, duration));
            // dynamically allocated Process by passing through the variables you got from the files than put them
            // into the vector
            Process* temp = new Process(name, stoi(id), stoi(call), stoi(duration));
            m_processes.push_back(temp);
        }
        // just for testing but displays all the process loaded
        DisplayProcesses(); // testing only
        // uses for loop to create all the threads with AddThread function
        for (unsigned int i = 0; i < NUM_THREADS; i++) {
            AddThread(m_processes.at(i));
        }
        // return true if file open
        return true;
    }
    // returns false when it doesn't open or exist
    else {
        cout << "File not found" << endl;
        return false;
    }
}
// this function create the thread, think of it as creating the column
void Processor::AddThread(Process * a) {
    if (m_threads.size() < NUM_THREADS) {
        // dynamically allocate Lstack
        Lstack<Process *> *temp = new Lstack<Process *>;
        // use the push function from Lstack to add the thread
        temp->Push(a);
        // pushes it to m_threads
        m_threads.push_back(temp);
    }
}
// uses the id in process to find the location and returns that
int Processor::GetProcessCalled(int id) {
    for (unsigned int i = 0; i < m_processes.size(); i++) {
        if (id == m_processes.at(i)->m_id) {
            return i;
        }
    }
    return -1;
}
// this function puts process into the threads, think of this as the rows
void Processor::PopulateThreads() {
    int num = 0;
    for (unsigned int i = 0; i < m_threads.size(); i++) {
        // uses the top function from Lstack to get m_call
        if (m_threads.at(i)->Top()->m_call != -1) {
            // stores GetProcessCalled in num
            num = GetProcessCalled(m_threads.at(i)->Top()->m_call);
            // uses that num for m_processes indexing and pushing that to the thread
            m_threads.at(i)->Push(m_processes[num]);
        }
    }
}
// the Main menu that give you choice and control your choices choices
void Processor::MainMenu() {
    int choice = 0;
    bool play = true;
    // keeps running until set to false
    while(play) {
        // for reprompting
        do {
            cout << "Choose an option." << endl;
            cout << "1. Display Threads" << endl;
            cout << "2. Start Thread" << endl;
            cout << "3. Quit" << endl;
            cin >> choice;
        } while (choice < 1 || choice > 3);
        if (choice < 1 || choice > 3) {
            cout << "Please enter a valid option" << endl;
        }
        // depending on your choices there are three outcomes
        if (choice == 1) {
            DisplayThread();
        } else if (choice == 2) {
            StartThreads();
        } else if (choice == 3) {
            play = false;
            cout << "Thank you trying UMBC Processor!" << endl;
        }
    }
}
// displays all the process load from the file, mostly for testing purposes
void Processor::DisplayProcesses() {
    for (unsigned int i = 0; i < m_processes.size(); i++) {
        cout << *m_processes.at(i) << endl;
    }
}
// List out the possible threads for you to choose from
void Processor::ListThreads() {
    for (unsigned int i = 0; i < m_threads.size(); i++) {
        // use GetSize function from Lstack to get the total numbers of processes
        cout << i+1 << " Thread " << i+1 << " (" << m_threads.at(i)->GetSize() << " processes)";
    }
}
// Controls which thread is being chosen
int Processor::ChooseThread() {
    int choice = 0;
    do {
        cout << "What thread would you like to view?" << endl;
        ListThreads();
        cin >> choice;
    } while (choice < 1 || m_threads.size() < choice);
    return choice -1;
}
// Displays the processes in the thread you choose
void Processor::DisplayThread() {
    int num = ChooseThread(); // use num to take in your choice
    cout << "Thread " << num << endl;
    // uses that num to find that thread than print out iy contents
    for (int i = 0; i < m_threads.at(num)->GetSize(); i++)  {
        cout << *m_threads.at(num)->At(i) << endl;
    }

}
// This counts how many milliseconds it took to complete the thread
void Processor::StartThreads() {
    // use a nested for loop to access the duration
    for (unsigned int i = 0; i < m_threads.size();i++) {
        int sum = 0; // use to track sum of the thread
        for (int j = 0; j < m_threads.at(i)->GetSize(); j++) {
            sum += m_threads.at(i)->Top()->m_duration;
            // pops/ delete the process after duration been collected
            m_threads.at(i)->Pop();
        }
        cout << "Thread " << i << " took " << sum << " milliseconds to complete" << endl;
    }
}
// Displays the title
void Processor::DisplayTitle() {
    cout << "Welcome to UMBC Processor!" << endl;
}
