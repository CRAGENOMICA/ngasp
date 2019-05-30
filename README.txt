Last modifications and decisions of the proyect was documented in this private github: https://github.com/CRAGENOMICA/ngasp_intranet

$NgaSP
========

This repository contains the Next generation of the Genome Analysis Toolkit ($NgaSP). The contents
of this repository are 100% open source and released under the LGPL 2.1 license (see [LICENSE.TXT](https://github.com/cragenomica/ngaSP/blob/master/LICENSE.TXT)).

NgaSP aims to bring together well-established tools from the [NgaSP](http://www.cragenomica.org/WIP) and
[WIP](http://cragenomica.github.io/WIP/) codebases under a streamlined framework,
and to enable selected tools to be run in a massively parallel way on local clusters or in the cloud using
[Apache Spark](http://spark.apache.org/). It also contains many newly developed tools not present in earlier
releases of the toolkit.

## Table of Contents
* [Requirements](#requirements)
* [Quick Start Guide](#quickstart)
* [Building ngaSP](#building)
* [Running ngaSP](#running)
    * [Passing JVM options to gatk](#jvmoptions)
* Contribute
* Support
* License

Requirements
--------

***Please see the [ngaSP website](https://bioinformatics.cragenomica.es/projects/ngaSP), where you would soon (can) download a precompiled executable, read documentation, ask questions, and receive technical support.***

## <a name="requirements">Requirements</a>


Quick Start Guide
------------

Install $NgaSP by running:

    install project

Building ngaSP

Running ngaSP


Contribute
----------

- Issue Tracker: github.com/$NgaSP/$NgaSP/issues
- Source Code: github.com/$NgaSP/$NgaSP

Support
-------

If you are having issues, please let us know.
We have a mailing list located at: project@google-groups.com

License
-------

[![License (LGPL 2.1)](https://img.shields.io/badge/License-LGPL%20v2.1-blue.svg)](https://opensource.org/licenses/LGPL-2.1)




ReadMe file — Instructions
==========================

This file provides a brief description of the project's folders structure.

If this is the first time you open this project, you can start by reading 
the manual (./doc/TeX/ngasp.pdf).


## <a name="downloading">downloading</a>

Project folders are organized in this way:
    * develop/

    * develop/source/backend/
      This is the source code of the "backend" (the system core).

    * develop/webapp/
      This is the folder of the "front-end" (web application).

    * develop/webapp/tmp
      This is the temporary folder used by the back-end for storing experiment results and messages.

    * develop/source/samtoolslib/
      This is the source code of samtools library with some modifications (search for this tag: "//!").

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

    * docker/
      This folder contains the docker files for creating the compiling- and the developing- environments.

    * gradle/
    * gradlew
    * gradlew.bat
      This folder and files are used by Jenkins, the continuous integration system.

    * LICENSE.txt
      This is the license text for this project (GNU Lesser GPL 2.1)

    * media/
      This folder contains ngasp resources such as logos, icons and images.

    * ngasp.xcodeproj
      It contains the XCode configuration for opening the ./source/backend.

    * readme.txt
      This file.

    * release/
      This folder contains the final application once it is compiled.

    * tools/
      It contains some development tools.

    * ./.git
      This folder is used by to Git.

    * ./.gitattibutes
      Here are defined some files and folders to be included but not versioned with Git.

    * ./.gitignore
      Here are defined some files and folders to be excluded versioning with Git.



