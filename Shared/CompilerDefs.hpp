/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2012-2013 Mislav Blazevic, Ryan Lahfa

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef COMPILER_DEFS_HPP
#define COMPILER_DEFS_HPP

/** ************************ Windows stuff ************************ **/
    #if defined(WIN32) || defined(_WIN32)
    #define WOD_DLL_DECL __declspec(dllexport)

/** ************************ Microsoft Visual Studio C++ stuff ************************ **/
    #if defined(_MSC_VER)
        #define MSVC
        #pragma warning(disable : 4251)
    #endif

/** ************************ GNU GCC Compiler stuff ************************ **/
    #elif defined( __GNUC__ )
        #define WOD_DLL_DECL __attribute__((__visibility__("default")))
    #else
        #define WOD_DLL_DECL export
    #endif

#endif
