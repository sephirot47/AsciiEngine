#include "Debug.h"

using namespace ae;

string Debug::logFile;
ofstream Debug::fileStream;
unsigned int Debug::fileMode = DebugModeLog | DebugModeWarning | DebugModeError;
unsigned int Debug::outputMode = DebugModeFile | DebugModeTerm;

agl::Window Debug::debugWindow = agl::Window(0,0,0,0);

std::list<std::string> Debug::windowMessages = std::list<std::string>();
const int Debug::WindowMessagesLimit = 100;

void Debug::showWindow()
{
    if(Debug::debugWindow.getWidth() == 0)
    {   //Execute only once, singleton
        Debug::debugWindow.setPos(agl::Window::getMaxWidth()  * 0.9,
                                  agl::Window::getMaxHeight() * 0.0);

        Debug::debugWindow.setSize(agl::Window::getMaxWidth()  * 0.15,
                                   agl::Window::getMaxHeight() * 1.0);

        Debug::debugWindow.setTitle("Debug");
        Debug::debugWindow.drawBox = true;
    }

    Debug::debugWindow.erase();

    if(Debug::windowMessages.size() > 0)
    {
        int drawBoxOffset = (Debug::debugWindow.drawBox ? 1 : 0);
        int maxLines = Debug::debugWindow.getClippedHeight() - drawBoxOffset * 2;
        int endOffset = glm::min(maxLines, (int)Debug::windowMessages.size());
        auto itEnd = Debug::windowMessages.begin();
        std::advance(itEnd, endOffset);
        int y = drawBoxOffset;
        for(auto it = Debug::windowMessages.begin(); it != itEnd; ++it)
        {
            Debug::debugWindow.printf(drawBoxOffset, y, (*it).c_str());
            ++y; //go down
        }
    } else Debug::debugWindow.printf(0,0,""); //change color if nothings written

    Debug::debugWindow.display();
}

void Debug::log(ostringstream &log)
{
    if (outputMode & DebugModeFile and fileMode & DebugModeLog)
    {
        if (fileStream.is_open()) fileStream << log.str();

    }

    if (outputMode & DebugModeTerm)
    {
      Debug::windowMessages.push_front(log.str());
      if(Debug::windowMessages.size() >= Debug::WindowMessagesLimit) Debug::windowMessages.pop_back();
      Debug::showWindow();
    }
}

void Debug::warning(ostringstream &log)
{
    if (outputMode & DebugModeFile and fileMode & DebugModeWarning)
    {
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DebugModeTerm)
    {
      Debug::windowMessages.push_front(log.str());
      if(Debug::windowMessages.size() >= Debug::WindowMessagesLimit) Debug::windowMessages.pop_back();
      Debug::showWindow();
    }
}

void Debug::error(ostringstream &log)
{
    if (outputMode & DebugModeFile and fileMode & DebugModeError)
    {
        if (fileStream.is_open()) fileStream << log.str();

        Debug::windowMessages.push_front(log.str());
        if(Debug::windowMessages.size() >= Debug::WindowMessagesLimit) Debug::windowMessages.pop_back();
        Debug::showWindow();
    }

    if (outputMode & DebugModeTerm)
    {
        cerr << log.str();
    }
}

void Debug::setFile(string filepath)
{
    if (filepath == DebugAutoLogFile)
    {
        string Debug = DebugLogDir;
        Debug.append("/");
        Debug.append("test");
        Debug.append(".log");
        filepath = Debug;
        cerr << "Saving log to: " << filepath << endl;
    }
    logFile = filepath;
    if (fileStream.is_open()) fileStream.close();
        fileStream.open(logFile,fstream::out);
}


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

/*
ostream& operator<<(ostream &log, const glm::quat &q)
{
    log << "quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return log;
}
*/

ostream &operator<<(ostream &log, const glm::mat4 &v)
{
    log << "mat4(" << v[0][0] << ", " << v[1][0] << ", " << v[2][0] << ", " << v[3][0] << "," << endl;
    log << " " << v[0][1] << ", " << v[1][1] << ", " << v[2][1] << ", " << v[3][1] << "," << endl;
    log << " " << v[0][2] << ", " << v[1][2] << ", " << v[2][2] << ", " << v[3][2] << "," << endl;
    log << " " << v[0][3] << ", " << v[1][3] << ", " << v[2][3] << ", " << v[3][3] << ")" << endl;
    return log;
}

