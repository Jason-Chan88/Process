#include "Process.h"
// Default constructor
Process::Process() {
    m_name = "";
    m_id = 0;
    m_call = 0;
    m_duration = 0;
}
// overload constructor where we set all m variable
Process::Process(string name, int id, int call, int duration) {
    m_name = name;
    m_id = id;
    m_call = call;
    m_duration = duration;
}
// friend operator that prints out all the m variables
ostream& operator<<(ostream& output, Process& a) {
    output << a.m_name << " " << a.m_id << " " << a.m_call << " " << a.m_duration << endl;
    return output;
}