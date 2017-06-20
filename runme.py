#!/usr/bin/env python
# -*- coding: utf-8 -*
#c
# ngaSP: the computational solution for next generation analysis of 
# Sequence Polymorphisms.
# Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
# Centre for Research in Agricultural Genomics (CRAG).
# All rights reserved.
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version
# 2.1 as published by the Free Software Foundation.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 2.1 for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License version 2.1 along with this library; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
# Boston, MA 02110-1301, USA.

# brief     runme.py
# details
# author    Joan Jené
# version   1.0
# date      June 19, 2017
# pre
# bug
# warning


import os
import platform
import subprocess
import tempfile

# ==============================================================================
# CONSTANTS
# ==============================================================================

DEV_ENV_PATH   = 'docker/development-environment'
CWD            = os.getcwd()
OS             = platform.system()

# ==============================================================================
# STRING TABLE
# ==============================================================================

MSG_WINDOWS    = 'Windows platform detected...'
MSG_LINUX      = 'GNU/Linux platform detected...'
MSG_MAC        = 'Mac OS X platform detected...'


# ==============================================================================
# MAIN
# ==============================================================================
	
if __name__ == '__main__':

    temp_folder = tempfile.mkdtemp()

    if OS == 'Darwing':
        print(MSG_MAC)
        

    if OS == 'Windows':
        print(MSG_WINDOWS)

    if OS == 'Linux':
        print(MSG_LINUX)

        # Change to the Development Environment Directory
        os.chdir(DEV_ENV_PATH)

        # Create a temporary file
        p = subprocess.Popen(['mktemp'], stdout=subprocess.PIPE)
        temp_file_name, err = p.communicate()
        temp_file_name = 'out.txt'

        # Get the display number
        #p = subprocess.Popen(['echo', '\${DISPLAY}'], stdout=subprocess.PIPE)
        #dplay, err = p.communicate()
        dplay = ':0'
   
        p1 = subprocess.Popen(["xauth", "nlist", dplay], stdout=subprocess.PIPE)
        p2 = subprocess.Popen(["sed", "-e", "s/^..../ffff/"], stdin=p1.stdout, stdout=subprocess.PIPE)
        p3 = subprocess.Popen(["xauth", "-f", 'out.txt', "nmerge", "-"], stdin=p2.stdout)
        p3.communicate()

        # The shm-size is for chrome. Without this option it crashes when changing the window size
#        subprocess.call(["docker", "run", "-it", "--rm", "--privileged", "--net", "host", "--shm-size=1g", "--memory", "1024mb",
#                                   "-p", "3000:3000", "-p","3001:3001",
#                                   "-e", "DISPLAY=" + dplay,
#                                   "-v", CWD + "/develop:/develop", "-v", "/tmp/.X11-unix:/tmp/.X11-unix", "-v", temp_folder + ":" + temp_folder,
#                                   "-e", "XAUTHORITY=" + temp_folder,
#                                   "development-environment",
#                                   "/develop/webapp/start_ngasp.sh"])


