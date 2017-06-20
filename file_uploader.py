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
LINE_1               = 265
LINE_SPACE           = 70
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
DOCKER_VOLUME_PATH_1 = "develop" # Docker's Volume Path: /develop/data
DOCKER_VOLUME_PATH_2 = "data"

# ==============================================================================
# STRING TABLE
# ==============================================================================

MSG_REGISTRATION_ERROR        = 'Error registering file. Is ngasp running?'
MSG_NO_INPUT_FILE             = 'Choose a file first.'
MSG_INPUT_FILE_DOES_NOT_EXIST = 'File does not exist.'
MSG_SYMLINK_ALREADY_EXISTS    = 'The shortcut already exists: '

# ==============================================================================
# MyQLineEdit class
# For being able to drag & drop files to the QLineEdit
# ==============================================================================

class MyQLineEdit(QtGui.QLineEdit):

    def __init__(self):
        super(MyQLineEdit, self).__init__()
        super(MyQLineEdit, self).setAcceptDrops(True)

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
    button_link.setText("Create Shortcut")
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
                            DOCKER_VOLUME_PATH_1,
                            DOCKER_VOLUME_PATH_2,
                            subfolder)
    try:
        os.makedirs(dst_path)
    except:
        pass
        
    dst = os.path.join(dst_path, ntpath.basename(path_file_name))

    try:
        os.symlink(path_file_name, dst)
    except OSError:
        alert(MSG_SYMLINK_ALREADY_EXISTS + dst)
        clearForm()
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
        alert(str(x))
    except:
        alert(MSG_REGISTRATION_ERROR)
        ret = False

    return ret

# ------------------------------------------------------------------------------
# CheckInputFile()
#
# Description : This function checks if the file exists.
# return      : True if it is Ok. Else, False.
# ------------------------------------------------------------------------------

def CheckInputFile():

    ret = True

    path_file_name = str(le_file_name.text())

    if path_file_name == '':
        alert(MSG_NO_INPUT_FILE)
        ret = False
    else:
        if not os.path.isfile(path_file_name):
            alert(MSG_INPUT_FILE_DOES_NOT_EXIST)
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

    le_file_name.setText(QFileDialog.getOpenFileName())


# ------------------------------------------------------------------------------
# OnLinkFile()
#
# Description : This function creates a shortcut to the selected file. Then, it
#               registers the file.
# return      : True if it is Ok. Else, False.
# ------------------------------------------------------------------------------

def OnLinkFile():

    ret = CheckInputFile()

    if ret == True:
        path_file_name = str(le_file_name.text())
        subfolder = str(le_destination.text())

        ret = createSymbolicLink(path_file_name, subfolder)

        if ret == True:
            registerFileOnServer(path_file_name,
                                 False,  # Do not upload the file. Only register
                                 subfolder)
            clearForm()

    return ret


# ------------------------------------------------------------------------------
# OnUploadFile()
#
# Description : This function uploads the file. If the system installation is
#               local, the upload is like a copy to the docker's volume.
# return      : True if it is Ok. Else, False.
# ------------------------------------------------------------------------------

def OnUploadFile():

    ret = CheckInputFile()

    if ret == True:
        path_file_name = str(le_file_name.text())
        subfolder = str(le_destination.text())
        registerFileOnServer(path_file_name, 
                             True,  # Upload the file (and register it, too)
                             subfolder)
        clearForm()

    return ret


# ==============================================================================
# MAIN
# ==============================================================================
	
if __name__ == '__main__':

    createMainWindow()



