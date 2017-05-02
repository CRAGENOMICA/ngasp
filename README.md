ReadMe file — Instructions
==========================

This file give you a brief description of the project's folders structure.

If this is the first time you open this project, you can start reading the book 
of ngasp (./doc/TeX/ngasp.pdf).


Project folders are organized in this way:

    * docker/
      This folder contains the docker files for creating the compiler environment and the development-environment.

    * media/
      This folder contains ngasp resources such as logos, icons and images.

    * develop/source/backend/
      This is the source code of the "backend" (the system core).

    * develop/webapp/
      This is the folder of the "front-end" (web application).

    * develop/webapp/tmp
      This is the temporary folder used by the back-end for storing experiment results and messages.

    * develop/source/samtoolslib/
      This is the source code of samtools with some modifications (search for this tag: "//!").

    * develop/source/seqan/
      This is the source code of the seqan library.

    * develop/repository/
      It contains some example experiments and pipelines.

    * develop/examples/
      This folder contains data example files. Only for development purposes.

    * develop/tests/
      This folder contains development scripts for testing purposes.

    * doc/
      This folder contains development documentation about the project.

    * gradle/
    * gradlew
    * gradlew.bat
      This folder and files are used by Jenkins.

    * LICENSE.txt
      This is the license text for this project.

    * ngasp.xcodeproj
      It contains the XCode configuration for opening the ./source/backend.

    * readme.txt
      This file.

    * release/
      This folder contains the final application folder.
      This folder is compressed and stored on the public web for being downloaded.

    * tools/
      It contains some development tools.

    * ./.git
      This folder owns to Git.

    * ./.gitignore
      It excludes files and folders from Git transactions.



