//==============================================================================
// Set of functions designated to read the settings from a particular source.
// Currently only .ini files are supported.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef SETTINGS_READER_H
#define SETTINGS_READER_H

#include <iostream>
#include <string>
#include "settings_struct.h"
#include "INIReader.h"

using namespace std;

namespace utils {
    /**
     * Loads information from the provided .ini file into appropriate structure.
     *
     * @param pathToINI A relative or absolute path to the .ini file.
     *
     * @return          Settings structure loaded with values from specified
     *                  .ini file or they alternative defaults.
     */
    Settings readFromINI(string pathToINI);
}


#endif
