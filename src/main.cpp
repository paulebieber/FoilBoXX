//####################################//
//  Foilbox by Paul v. Bieberstein  //
//  Beta_V0.1                     //
//##############################//

#include <QApplication>
#include "Interface.h"
#include "iostream"

//Read Version from CMake
#ifdef FOILBOXX_VERSION_STRING
    #define version FOILBOXX_VERSION_STRING
#else
    #define version "Version not provided by CMake!"
#endif

int main(int argc, char **argv) {

    std::cout <<
            "    _______       _  __ ____       _  ___  ___________________\n"
            "   /  ____/___   (_)/ // __ )____ | |/   |/ ____Version_"<<version<<"/\n"
            "  /  /_  / __ \\ / // // __  / __ \\|   /|   /\n"
            " /  __/ / /_/ // // // /_/ / /_/ /   |/   |_____ \n"
            "/__/    \\____//_//_//_____/\\____/_/|___/|______/\n"
            "by Paul Rogalla von Bieberstein\n" << std::endl;

    QApplication app (argc,argv);
    app.setStyle("fusion");

	Interface* interface = new Interface(app,version);

    return app.exec();
}
