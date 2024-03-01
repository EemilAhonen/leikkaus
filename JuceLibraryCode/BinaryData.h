/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   RobotoRegular_ttf;
    const int            RobotoRegular_ttfSize = 168260;

    extern const char*   Icon_png;
    const int            Icon_pngSize = 745589;

    extern const char*   Background_png;
    const int            Background_pngSize = 43053;

    extern const char*   Compensation_OFF_png;
    const int            Compensation_OFF_pngSize = 10538;

    extern const char*   Compensation_ON_png;
    const int            Compensation_ON_pngSize = 10546;

    extern const char*   Delta_OFF_png;
    const int            Delta_OFF_pngSize = 6347;

    extern const char*   Delta_ON_png;
    const int            Delta_ON_pngSize = 6393;

    extern const char*   Lines_png;
    const int            Lines_pngSize = 31267;

    extern const char*   Menu_png;
    const int            Menu_pngSize = 105106;

    extern const char*   Oversampling_OFF_png;
    const int            Oversampling_OFF_pngSize = 10344;

    extern const char*   Oversampling_ON_png;
    const int            Oversampling_ON_pngSize = 10362;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 11;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
