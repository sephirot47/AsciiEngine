#include "Debug.h"

string Debug::logFile;
ofstream Debug::fileStream;
unsigned int Debug::fileMode = DbgModeLog | DbgModeWarning | DbgModeError;
unsigned int Debug::outputMode = DbgModeFile | DbgModeTerm;

agl::Window Debug::dbgWindow = agl::Window(10,10,100,100);

void Debug::Log(ostringstream &log)
{
    if (outputMode & DbgModeFile and fileMode & DbgModeLog)
    {
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DbgModeTerm and fileMode & DbgModeLog)
    {
        Debug::dbgWindow.printf(0,0, log.str().c_str());
    }
}

void Debug::Warning(ostringstream &log)
{
    if (outputMode & DbgModeFile and fileMode & DbgModeWarning)
    {
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DbgModeTerm)
    {
        cerr << log.str();
    }
}

void Debug::Error(ostringstream &log)
{
    if (outputMode & DbgModeFile and fileMode & DbgModeError)
    {
        if (fileStream.is_open()) fileStream << log.str();
    }

    if (outputMode & DbgModeTerm)
    {
        cerr << log.str();
    }
}

void Debug::SetFile(string filepath)
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
