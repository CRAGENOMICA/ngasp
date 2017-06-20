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

# brief     file_uploader.py
# details
# author    Joan Jené
# version   1.0
# date      June 14, 2017
# pre
# bug
# warning


import sys
import ntpath
import os
import subprocess
from PyQt4 import QtGui
from PyQt4.QtGui import *
from PyQt4 import QtCore
from PyQt4.QtCore import *
import glob


# ==============================================================================
# CONSTANTS
# ==============================================================================

# These are constants for building the interface:

APP_TITTLE           = "ngasp - File Uploader"
WIN_X                = 100
WIN_Y                = 100
WIN_W                = 600
WIN_H                = 565
COL_1                = 50
COL_2                = 185
COL_3                = 500
LINE_1               = 255
LINE_SPACE           = 80
CONTROL_H            = 30
DEFAULT_BUTTON_W     = 140
DEFAULT_BUTTON_H     = 50
BUTTON_BROWSER_W     = 30

# These are constants for uploading the file:

REMOTE_SERVER        = 'localhost'
PORT                 = '3000'
WEB_SERVICE          = '/datafiles'
WEB_SERVICE_TYPE     = 'POST'    # For adding files.
LOCAL_INSTALLATION   = True      # For getting do: http://localhost:3000/datafiles
DOCKER_VOLUME_PATH   = ['develop', 'data']  # Docker's Volume Path: /develop/data in Linux and \develop\data in Windows

# ==============================================================================
# STRING TABLE
# ==============================================================================

MSG_REGISTRATION_ERROR        = 'Is ngasp running? Error uploading file: '
MSG_NO_INPUT_FILE             = 'Choose a file first.'
MSG_INPUT_FILE_DOES_NOT_EXIST = 'File does not exist: '
MSG_SYMLINK_CREATION_ERROR    = 'The destination folder for this shortcut is owned by the root user. Change its owner first: '
MSG_SHORTCUT_CREATED          = 'Shortcut created for file: '
MSG_REGISTERED_FILES          = 'Number of uploaded files on Server: '
MSG_UNLINK_ERROR              = 'Could not remove the shortcut of the just created shortcut to: '
MSG_END_REGISTRATION          = '. Restart the ngasp web interface to see them.'
MSG_NO_REGISTERED_FILES       = 'No files or shortcuts have been uploaded.'


# ==============================================================================
# MyQLineEdit class
# For being able to drag & drop files to the QLineEdit
# ==============================================================================

class MyQLineEdit(QtGui.QLineEdit):

    def __init__(self):
        super(MyQLineEdit, self).__init__()
        super(MyQLineEdit, self).setAcceptDrops(True)

    def dropEnterEvent(self, event):
        event.accept()

    def dropMoveEvent(self, event):
        event.accept()

    def dropEvent(self, event):
        data = event.mimeData()
        urls = data.urls()
        if (urls and urls[0].scheme() == 'file' ):
            self.setText(urls[0].path())

# ==============================================================================
# GLOBAL VARIABLES
# ==============================================================================

# QApplication creation:

app = QtGui.QApplication(sys.argv)

# These are all the controls of the main window:

w                  = QtGui.QMainWindow()
le_file_name       = MyQLineEdit()
button_file_name   = QtGui.QPushButton()
le_destination     = QtGui.QLineEdit()
button_upload      = QtGui.QPushButton()
button_link        = QtGui.QPushButton()


# ==============================================================================
# APPLICATION METHODS
# ==============================================================================

# ------------------------------------------------------------------------------
# createMainWindow()
#
# Description: This function creates the application's main window.
# return     : None
# ------------------------------------------------------------------------------

def createMainWindow():
    
    app.setWindowIcon(QtGui.QIcon(os.path.join(os.getcwd(),
                                  "media",
                                  "ngasp_01.png")))

    w.setGeometry(WIN_X, WIN_Y, WIN_W, WIN_H)
    w.setFixedSize(WIN_W, WIN_H)
    w.setWindowTitle(APP_TITTLE)

    background_image = os.path.join(os.getcwd(),
                                    "media",
                                    "uploader_background.png")
    le_file_name.setParent(w)
    le_file_name.setGeometry(COL_2,
                             LINE_1,
                             COL_3 - COL_2,
                             CONTROL_H)

    button_file_name.setParent(w)
    button_file_name.clicked.connect(OnSelectFile)
    button_file_name.setText("...")
    button_file_name.setGeometry(COL_3,
                                 LINE_1,
                                 BUTTON_BROWSER_W,
                                 CONTROL_H)

    le_destination.setParent(w)
    le_destination.setGeometry(COL_2,
                               LINE_1 + LINE_SPACE * 1,
                               COL_3 - COL_2,
                               CONTROL_H)
    le_destination.setAcceptDrops(True)

    regex=QRegExp("([a-z-A-Z-0-9_]+)([a-z-A-Z-0-9_]+/)*")
    validator = QtGui.QRegExpValidator(regex)
    le_destination.setValidator(validator)

    if LOCAL_INSTALLATION == True:
        pos_button_upload = (WIN_W / 3) - (DEFAULT_BUTTON_W / 2)
        pos_button_link   = (WIN_W / 3) * 2 - (DEFAULT_BUTTON_W / 2)
    else:
        pos_button_upload = (WIN_W / 2) - (DEFAULT_BUTTON_W / 2)
        pos_button_link   = 0

    button_upload.setParent(w)
    button_upload.clicked.connect(OnUploadFile)
    button_upload.setText("Upload File")
    button_upload.setGeometry(pos_button_upload,
                              WIN_H - LINE_SPACE - CONTROL_H, 
                              DEFAULT_BUTTON_W,
                              DEFAULT_BUTTON_H)
    button_link.setParent(w)
    button_link.clicked.connect(OnLinkFile)
    button_link.setText("Upload Shortcut")
    button_link.setGeometry(pos_button_link,
                            WIN_H - LINE_SPACE - CONTROL_H, 
                            DEFAULT_BUTTON_W,
                            DEFAULT_BUTTON_H)
    button_link.setVisible(LOCAL_INSTALLATION)

    app.setStyleSheet("QMainWindow"
                      "{"
                      "    background-attachment: fixed;"
                      "    background-image:url(\"" + background_image + "\"); "
                      "    background-repeat: no-repeat; "
                      "}"
                      "QLineEdit"
                      "{"
                      "    color: #445F2E;"
                      "    font: 14px;"
                      "    background-color: #fff;"
                      "}"
                      "QPushButton"
                      "{"
                      "    color: #ffffff;"
                      "    font: bold 14px;"
                      "    background-color: #445F2E"
                      "}")
    w.show()
    sys.exit(app.exec_())


# ------------------------------------------------------------------------------
# createSymbolicLink()
#
# Description     : This function creates a symbolic link of the selected file
#                   in the shared folder between the docker container and the
#                   host.
# @path_file_name : File to be linked.
# @subfolder      : Destination subfolder of the symbolic link. 
# return          : True if it is Ok, otherwise False.
# ------------------------------------------------------------------------------

def createSymbolicLink(path_file_name, subfolder):
    ret = True

    # The source is the selected file and the destination is the
    # develop folder inside the current directory

    dst_path = os.path.join(os.getcwd(),
                            DOCKER_VOLUME_PATH[0],
                            DOCKER_VOLUME_PATH[1],
                            subfolder)
    try:
        os.makedirs(dst_path)
    except:
        pass
        
    symbolic_link = os.path.join(dst_path, ntpath.basename(path_file_name))

    try:
        os.symlink(path_file_name, symbolic_link)
    except OSError:
        ret = False

    return ret

# ------------------------------------------------------------------------------
# removeSymbolicLink()
#
# Description     : This function removes a symbolic link.
# @path_file_name : File linked.
# @subfolder      : Destination subfolder of the symbolic link. 
# return          : True if it is Ok, otherwise False.
# ------------------------------------------------------------------------------

def removeSymbolicLink(path_file_name, subfolder):
    ret = True

    # The source is the selected file and the destination is the
    # develop folder inside the current directory

    dst_path = os.path.join(os.getcwd(),
                            DOCKER_VOLUME_PATH[0],
                            DOCKER_VOLUME_PATH[1],
                            subfolder)
    try:
        os.makedirs(dst_path)
    except:
        pass
        
    symbolic_link = os.path.join(dst_path, ntpath.basename(path_file_name))

    try:
        os.unlink(symbolic_link)
    except OSError:
        ret = False

    return ret

# ------------------------------------------------------------------------------
# registerFileOnServer()
#
# Description     : This function uploads the file to the remote server.
# @path_file_name : File to be registered and / or uploaded.
# @upload_file    : True if the file must be uploaded. Else, False.
# @subfolder      : Subfolder to be created in the server.
# return          : True if Ok. Else, False.
# ------------------------------------------------------------------------------

def registerFileOnServer(path_file_name, upload_file, subfolder):
    ret = True

    file_name = ntpath.basename(path_file_name)

    if upload_file == True:
        u = 'yes'
    else:
        u = 'no'

    try:
        x = subprocess.check_output(['curl',
                         '--upload-file', path_file_name,
                         '-X', WEB_SERVICE_TYPE,
                         '-H', 'filename:' + file_name,
                         '-H', 'subpath:' + subfolder,
                         '-H', 'upload:' + u,
                         'http://' + REMOTE_SERVER + ':' + PORT + WEB_SERVICE])

    except:
        ret = False

    return ret


# ------------------------------------------------------------------------------
# IsInputFilesEmpty()
#
# Description     : This function checks that the input files text control has
#                   at least one file.
# return          : True if it is Empty. Else, False.
# ------------------------------------------------------------------------------

def IsInputFilesEmpty():
    ret = False

    files = str(le_file_name.text())

    if files == '':
        ret = True

    return ret


# ------------------------------------------------------------------------------
# CheckOneInputFile()
#
# Description     : This function checks if the file exists.
# @path_file_name : The file to be checked.
# return          : True if it is Ok. Else, False.
# ------------------------------------------------------------------------------

def CheckOneInputFile(path_file_name):
    ret = True

    if not os.path.isfile(path_file_name):
        ret = False

    return ret


# ------------------------------------------------------------------------------
# clearForm()
#
# Description : This function prepares the application to be ready for 
#               registering / uploading more files.
# return      : None.
# ------------------------------------------------------------------------------

def clearForm():

    le_file_name.setText('')


# ------------------------------------------------------------------------------
# alert()
#
# Description : This function shows a message to the user.
# @msg        : The input message to be shown to the user.
# return      : None
# ------------------------------------------------------------------------------

def alert(msg):

    msgBox = QtGui.QMessageBox(w)
    msgBox.setWindowTitle(APP_TITTLE)
    msgBox.setText(msg)
    msgBox.exec_()


# ==============================================================================
# EVENTS
# ==============================================================================

# ------------------------------------------------------------------------------
# OnSelectFile()
#
# Description : This function shows a file dialog to the user in order to 
#               select a file from the local file system.
# return      : None. The selected file is stored directly in the QLineEdit
#               control.
# ------------------------------------------------------------------------------

def OnSelectFile():

    files = QFileDialog.getOpenFileNames()
    str_files = ''
    for one_file in files:
        str_files = str_files + str(one_file) + ','

    le_file_name.setText(str_files)


# ------------------------------------------------------------------------------
# OnLinkFile()
#
# Description : This function creates shortcuts to the selected files. Then, it
#               registers these files.
# return      : None.
# ------------------------------------------------------------------------------

def OnLinkFile():

    Do(False) # Do not upload files. Only register them.


# ------------------------------------------------------------------------------
# OnUploadFile()
#
# Description : This function uploads the file. If the system installation is
#               local, the upload is like a copy to the docker's volume.
# return      : None.
# ------------------------------------------------------------------------------

def OnUploadFile():

    Do(True) # Upload files and register them.


# ------------------------------------------------------------------------------
# Do()
# @upload     : If False: This function creates shortcuts to the selected files.
#                         Then, it registers these files.
#               If True:  This function uploads the file. If the system installation 
#                         is local, the upload is like a copy to the docker's volume.
# return      : None.
# ------------------------------------------------------------------------------

def Do(upload):

    registered_files = 0

    if IsInputFilesEmpty() == False:

        subfolder = str(le_destination.text())

        files = str(le_file_name.text()).split(',')

        for path_file_name in files:

            if path_file_name <> '':

                if path_file_name.find('*') <> -1:
                    # If the file contains '*', for example: /a/b/*.bam
                    # The following function gets all files ended with '.bam' and it concatenates them to the 'files' list.
                    files.extend(glob.glob(path_file_name))
                else:
                    if CheckOneInputFile(path_file_name) == True:

                        # Try to remove existing previous shortcut to the file (if it exists):
                        # For both cases: "upload shurtcut" and "upload file"
                        removeSymbolicLink(path_file_name, subfolder)

                        if upload == False:
                            # Create shortcut
                            if createSymbolicLink(path_file_name, subfolder) == False:
                                alert(MSG_SYMLINK_CREATION_ERROR + path_file_name)
                                break # <---- STOP

                        # If upload is True, this function uploads the file and it registers it on the Server
                        # If upload is False, this function only registers the file on the Server
                        if registerFileOnServer(path_file_name, upload, subfolder) == False:
                            alert(MSG_REGISTRATION_ERROR + path_file_name)

                            if upload == False:
                                # Remove the just created symbolic link because the file could not be registered on the Server
                                if removeSymbolicLink(path_file_name, subfolder) == False:
                                    alert(MSG_UNLINK_ERROR + path_file_name)
                            break # <---- STOP
                        else:
                            # Increment the number of registered files
                            registered_files = registered_files + 1
                    else:
                        alert(MSG_INPUT_FILE_DOES_NOT_EXIST + path_file_name)
    else:
        alert(MSG_NO_INPUT_FILE)


    if registered_files > 0:
        alert(MSG_REGISTERED_FILES + str(registered_files) + MSG_END_REGISTRATION)
    else:
        alert(MSG_NO_REGISTERED_FILES)



# ==============================================================================
# MAIN
# ==============================================================================
	
if __name__ == '__main__':

    createMainWindow()



