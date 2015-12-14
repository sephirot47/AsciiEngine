#include "Debug.h"

string Debug::logFile;
ofstream Debug::fileStream;
unsigned int Debug::fileMode = DbgModeLog | DbgModeWarning | DbgModeError;
unsigned int Debug::outputMode = DbgModeFile | DbgModeTerm;

agl::Window Debug::debugWindow = agl::Window(0,0,0,0);

std::list<std::string> Debug::windowMessages = std::list<std::string>();
const int Debug::WindowMessagesLimit = 100;

void Debug::showWindow()
{
    if(Debug::debugWindow.getWidth() == 0)
    {   //Execute only once, singleton
        Debug::debugWindow.setPos(agl::Window::getMaxWidth()  * 0.9,
                                  agl::Window::getMaxHeight() * 0.05);

        Debug::debugWindow.setSize(agl::Window::getMaxWidth()  * 0.05,
                                   agl::Window::getMaxHeight() * 0.9);

        Debug::debugWindow.drawBox = true;
    }

    Debug::debugWindow.erase();

    int drawBoxOffset = (Debug::debugWindow.drawBox ? 1 : 0);
    int y = Debug::debugWindow.getClippedHeight() - drawBoxOffset; //Begin from the bottom
    for(auto rit= Debug::windowMessages.begin(); rit != Debug::windowMessages.end(); ++rit)
    {
        Debug::debugWindow.printf(drawBoxOffset, y, "%s", (*rit).c_str());

        --y; //go up
        if(y < drawBoxOffset-1) break; //When arrived to top, just stop
    }

    Debug::debugWindow.display();
}

void Debug::log(ostringstream &log)
{

    if (outputMode & DbgModeFile and fileMode & DbgModeLog)
    {
        if (fileStream.is_open()) fileStream << log.str();

        Debug::windowMessages.push_front(log.str());
        if(Debug::windowMessages.size() >= Debug::WindowMessagesLimit) Debug::windowMessages.pop_back();
        Debug::showWindow();
    }
}

void Debug::warning(ostringstream &log)
{
    if (outputMode & DbgModeFile and fileMode & DbgModeWarning)
    {
        if (fileStream.is_open()) fileStream << log.str();

        Debug::windowMessages.push_front(log.str());
        if(Debug::windowMessages.size() >= Debug::WindowMessagesLimit) Debug::windowMessages.pop_back();
        Debug::showWindow();
    }

    if (outputMode & DbgModeTerm)
    {
        cerr << log.str();
    }
}

void Debug::error(ostringstream &log)
{
    if (outputMode & DbgModeFile and fileMode & DbgModeError)
    {
        if (fileStream.is_open()) fileStream << log.str();

        Debug::windowMessages.push_front(log.str());
        if(Debug::windowMessages.size() >= Debug::WindowMessagesLimit) Debug::windowMessages.pop_back();
        Debug::showWindow();
    }

    if (outputMode & DbgModeTerm)
    {
        cerr << log.str();
    }
}

void Debug::setFile(string filepath)
{
    if (filepath == CZ_AUTO_LOG_FILE)
    {
        string dbg = CZ_LOG_DIR;
        dbg.append("/");
        dbg.append("test");
        dbg.append(".log");
        filepath = dbg;
        cerr << "Saving log to: " << filepath << endl;
    }
    logFile = filepath;
    if (fileStream.is_open()) fileStream.close();
        fileStream.open(logFile,fstream::out);
}

/*
ostream& operator<<(ostream &log, const glm::vec2 &v)
{
    log << "vec2(" << v.x << ", " << v.y << ")";
    return log;
}

ostream& operator<<(ostream &log, const glm::vec3 &v)
{
    log << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return log;
}

ostream& operator<<(ostream &log, const glm::quat &q)
{
    log << "quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return log;
}


ostream &operator<<(ostream &log, const glm::mat4 &v)
{
    log << "mat4(" << v[0][0] << ", " << v[1][0] << ", " << v[2][0] << ", " << v[3][0] << "," << endl;
    log << " " << v[0][1] << ", " << v[1][1] << ", " << v[2][1] << ", " << v[3][1] << "," << endl;
    log << " " << v[0][2] << ", " << v[1][2] << ", " << v[2][2] << ", " << v[3][2] << "," << endl;
    log << " " << v[0][3] << ", " << v[1][3] << ", " << v[2][3] << ", " << v[3][3] << ")" << endl;
    return log;
}
*/
