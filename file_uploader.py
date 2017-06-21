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

# ==============================================================================
# IMPORTS
# ==============================================================================

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

APP_TITLE           = "ngasp - File Uploader"    # Application Title
WIN_X                = 100                       # Main Window Innitial Pos X
WIN_Y                = 100                       # Main Window Innitial Pos Y
WIN_W                = 600                       # Main Window Width
WIN_H                = 565                       # Main Window Height
COL_1                = 50                        # Position of the first column of controls
COL_2                = 185                       # Position of the second column of controls
COL_3                = 500                       # Position of the third column of controls
LINE_1               = 255                       # First line top position 
LINE_SPACE           = 80                        # Space between lines
CONTROL_H            = 30                        # Default height of controls
DEFAULT_BUTTON_W     = 140                       # Default width of buttons
DEFAULT_BUTTON_H     = 50                        # Default height of buttons
BUTTON_BROWSER_W     = 30                        # The width of the browsert button
IMAGES_PATH          = 'media'                   # Folder where images are stored
BG_IMAGE             = 'uploader_background.png' # The main window's background image
ICON_IMAGE           = 'ngasp_01.png'            # The application icon

# General constants:

FILES_SEPARATOR      = ','                       # e.g. file1.fas,file2.fas

# These are constants for uploading the file:

REMOTE_SERVER        = 'localhost'               # e.g. http://localhost:3000/datafiles
PORT                 = '3000'                    # Port
WEB_SERVICE          = '/datafiles'              # Web Service name
WEB_SERVICE_TYPE     = 'POST'                    # POST = Adding files / GET = listing
LOCAL_INSTALLATION   = True                      # False if Back-End is remote
DOCKER_VOLUME_PATH   = ['develop',               # Docker's Volume Path:
                        'data']                  #   Linux  &
                                                 #   Mac OS X : /develop/data
                                                 #   Windows  : \develop\data
# String Table

MSG_REGISTRATION_ERROR        = 'Is ngasp running? Error uploading file: '
MSG_NO_INPUT_FILE             = 'Choose a file first.'
MSG_INPUT_FILE_DOES_NOT_EXIST = 'File does not exist: '
MSG_SYMLINK_CREATION_ERROR    = 'The destination folder for this shortcut is owned by the root user. Change its owner first: '
MSG_SHORTCUT_CREATED          = 'Shortcut created for file: '
MSG_REGISTERED_FILES          = ' file(s) uploaded.'
MSG_REGISTERED_SHORTCUT       = ' shortcut(s) uploaded.'
MSG_UNLINK_ERROR              = 'Could not remove the shortcut of the just created shortcut to: '
MSG_NO_REGISTERED_FILES       = 'No files or shortcuts have been uploaded.'
UPLOAD_FILE_BUTTON_TEXT       = 'Upload File(s)'
UPLOAD_SHORTCUT_BUTTON_TEXT   = 'Upload Shortcut(s)'
BROWSER_BUTTON_TEXT           = '...'
FILES_PLACE_HOLDER            = 'You can also drag & drop files here'
DEST_PLACE_HOLDER             = 'Enter path to store uploaded files'

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
# GLOBALS
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

    # Main Window

    app.setWindowIcon(QtGui.QIcon(os.path.join(os.getcwd(),
                                  IMAGES_PATH,
                                  ICON_IMAGE)))

    w.setGeometry(WIN_X, WIN_Y, WIN_W, WIN_H)
    w.setFixedSize(WIN_W, WIN_H)
    w.setWindowTitle(APP_TITLE)

    background_image = os.path.join(os.getcwd(),
                                    IMAGES_PATH,
                                    BG_IMAGE)
    # Files Line Edit

    le_file_name.setParent(w)
    le_file_name.setGeometry(COL_2,
                             LINE_1,
                             COL_3 - COL_2,
                             CONTROL_H)
    le_file_name.setPlaceholderText(FILES_PLACE_HOLDER) 

    # Browser button

    button_file_name.setParent(w)
    button_file_name.clicked.connect(OnSelectFile)
    button_file_name.setText(BROWSER_BUTTON_TEXT)
    button_file_name.setGeometry(COL_3,
                                 LINE_1,
                                 BUTTON_BROWSER_W,
                                 CONTROL_H)

    # Destination Line Edit

    le_destination.setParent(w)
    le_destination.setGeometry(COL_2,
                               LINE_1 + LINE_SPACE * 1,
                               COL_3 - COL_2,
                               CONTROL_H)
    le_destination.setPlaceholderText(DEST_PLACE_HOLDER) 

    regex=QRegExp("([a-z-A-Z-0-9_]+)([a-z-A-Z-0-9_]+/)*")
    validator = QtGui.QRegExpValidator(regex)
    le_destination.setValidator(validator)

    # Bottom Buttons Position

    if LOCAL_INSTALLATION == True:
        pos_button_upload = (WIN_W / 3) - (DEFAULT_BUTTON_W / 2)
        pos_button_link   = (WIN_W / 3) * 2 - (DEFAULT_BUTTON_W / 2)
    else:
        pos_button_upload = (WIN_W / 2) - (DEFAULT_BUTTON_W / 2)
        pos_button_link   = 0


    # Upload File(s) Button

    button_upload.setParent(w)
    button_upload.clicked.connect(OnUploadFile)
    button_upload.setText(UPLOAD_FILE_BUTTON_TEXT)
    button_upload.setGeometry(pos_button_upload,
                              WIN_H - LINE_SPACE - CONTROL_H, 
                              DEFAULT_BUTTON_W,
                              DEFAULT_BUTTON_H)

    # Upload Shortcut(s) Button

    button_link.setParent(w)
    button_link.clicked.connect(OnLinkFile)
    button_link.setText(UPLOAD_SHORTCUT_BUTTON_TEXT)
    button_link.setGeometry(pos_button_link,
                            WIN_H - LINE_SPACE - CONTROL_H, 
                            DEFAULT_BUTTON_W,
                            DEFAULT_BUTTON_H)
    button_link.setVisible(LOCAL_INSTALLATION)

    # StyleSheet

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

    # Remove the focus of the first QLineEdit in order to show its placeholder:

    w.setFocus()

    # Show the window:

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
    msgBox.setWindowTitle(APP_TITLE)
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
        str_files = str_files + str(one_file) + FILES_SEPARATOR

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

        files = str(le_file_name.text()).split(FILES_SEPARATOR)

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

        # Show final report to the user:
        if registered_files > 0:
            if upload == True:
                alert(str(registered_files) + MSG_REGISTERED_FILES)
            else:
                alert(str(registered_files) + MSG_REGISTERED_SHORTCUT)
           
        else:
            alert(MSG_NO_REGISTERED_FILES)

    else:
        alert(MSG_NO_INPUT_FILE)


# ==============================================================================
# MAIN
# ==============================================================================
	
if __name__ == '__main__':

    createMainWindow()



