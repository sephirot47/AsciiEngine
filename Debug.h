#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>

#include "glm/glm.hpp"
#include "AsciiGL/Window.h"

enum DbgMode
{
    DbgModeLog = 1,
    DbgModeWarning = 2,
    DbgModeError = 4,
    DbgModeFile = 8,
    DbgModeTerm = 10
};

#define CZ_AUTO_LOG_FILE "cz_auto_log_file"
#define CZ_LOG_DIR "log"

using namespace std;
using namespace glm;

#define debugWarning(x) do{\
    ostringstream log;\
    ostringstream wrn;\
    log << x;\
    wrn << "Warning(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << endl;\
    Debug::warning(wrn);\
    log.flush();\
    wrn.flush();\
} while(0)

#define debugError(x) do{\
    ostringstream log;\
    ostringstream err;\
    log << x;\
    err << "Error(" << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << "): " << log.str() << endl;\
    Debug::error(err);\
    log.flush();\
    err.flush();\
} while(0)

#define debugLog(x) do{\
    ostringstream log;\
    log << x << endl;\
    Debug::log(log);\
    log.flush();\
} while(0)

#define DBG_ASSERT_MSG(x, msg) do{\
    if((x) < 0) debugError(msg);\
} while(0)

#define DBG_ASSERT_RET_MSG(x, msg) do{\
    if((x) < 0){ debugError(msg); return false;} \
} while(0)

#define DBG_ASSERT_RET_VOID_MSG(x, msg) do{\
    x;\
    if(error > 0){ debugError(msg); return;} \
} while(0)

//OSTREAM OPERATORS //////////////////////////////////
ostream& operator<<(ostream &log, const vec3 &v);
ostream& operator<<(ostream &log, const quat &q);
ostream& operator<<(ostream &log, const vec2 &v);
ostream& operator<<(ostream &log, const mat4 &v);


class Debug
{
private:
    static string logFile;
    static ofstream fileStream;

    static std::list<std::string> windowMessages; //message queue
    static const int WindowMessagesLimit;

public:
    static void showWindow(); //shows the window on screen
    static agl::Window debugWindow;

    static unsigned int fileMode;
    static unsigned int outputMode;
    static void setFile(string filepath);
    static void log(ostringstream &log);
    static void warning(ostringstream &log);
    static void error(ostringstream &log);
};

#endif //DEBUG_H
