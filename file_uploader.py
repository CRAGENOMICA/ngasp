#!/usr/bin/env python
# -*- coding: utf-8 -*

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
from PyQt4 import QtGui
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from ftplib import FTP
# from tkinter
from shutil import copyfile

# ==============================================================================
# CONSTANTS
# ==============================================================================

# These are constants for building the interface:

APP_TITTLE         = "ngasp - File Uploader"
WIN_X              = 100
WIN_Y              = 100
WIN_W              = 600
WIN_H              = 250
COL_1              = 50
COL_2              = 150
COL_3              = 500
LINE_1             = 40
LINE_SPACE         = 40
CONTROL_H          = 30
DEFAULT_BUTTON_W   = 100
BUTTON_BROWSER_W   = 30

# These are constants for uploading the file:

LOCAL_SERVER       = 'localhost'
REMOTE_SERVER      = 'localhost'
PORT               = '3000'


# ==============================================================================
# GLOBAL VARIABLES
# ==============================================================================

# QApplication creation:

app = QtGui.QApplication(sys.argv)

# These are all the controls of the main window:

w                  = QtGui.QWidget()
label_file_name    = QtGui.QLabel()
le_file_name       = QtGui.QLineEdit()
button_file_name   = QtGui.QPushButton()
label_destination  = QtGui.QLabel()
label_destination2 = QtGui.QLabel()
cb_create_copy     = QtGui.QCheckBox()
button_upload      = QtGui.QPushButton()
button_cancel      = QtGui.QPushButton()


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

    w.setGeometry(WIN_X, WIN_Y, WIN_W, WIN_H)
    w.setWindowTitle(APP_TITTLE)
    w.setAcceptDrops(True)

    label_file_name.setParent(w)
    label_file_name.setText("File Name:")
    label_file_name.move(COL_1, LINE_1)

    le_file_name.setParent(w)
    le_file_name.setGeometry(COL_2, LINE_1, COL_3 - COL_2, CONTROL_H)
    le_file_name.setAcceptDrops(True)

    button_file_name.setParent(w)
    button_file_name.clicked.connect(OnSelectFile)
    button_file_name.setText("...")
    button_file_name.setGeometry(COL_3, LINE_1, BUTTON_BROWSER_W, CONTROL_H)

    label_destination.setParent(w)
    label_destination.setText("Destination:")
    label_destination.move(COL_1, LINE_1 + LINE_SPACE * 1)

    label_destination2.setParent(w)
    label_destination2.setText("Root History")
    label_destination2.move(COL_2, LINE_1 + LINE_SPACE * 1)

    cb_create_copy.setParent(w)
    cb_create_copy.setText("Create a copy of the file in the Server")
    cb_create_copy.move(COL_1, LINE_1 + LINE_SPACE * 2)
    cb_create_copy.setCheckState(Qt.Checked)

    cb_create_copy.setVisible((LOCAL_SERVER == REMOTE_SERVER))

    button_upload.setParent(w)
    button_upload.clicked.connect(OnUploadFile)
    button_upload.setText("Upload")
    button_upload.setGeometry((WIN_W / 3) - (DEFAULT_BUTTON_W / 2),
                              WIN_H - LINE_SPACE - CONTROL_H, 
                              DEFAULT_BUTTON_W, CONTROL_H)

    button_cancel.setParent(w)
    button_cancel.clicked.connect(OnCancelUpload)
    button_cancel.setText("Cancel")
    button_cancel.setGeometry((WIN_W / 3) * 2 - (DEFAULT_BUTTON_W / 2),
                               WIN_H - LINE_SPACE - CONTROL_H,
                               DEFAULT_BUTTON_W, CONTROL_H)
    w.show()
    sys.exit(app.exec_())


# ------------------------------------------------------------------------------
# createSymbolicLink()
#
# Description: This function creates a symbolic link of the selected file
#              in the shared folder between the docker container and the host.
# return     : True if Ok. Otherwise, False.
# ------------------------------------------------------------------------------

def createSymbolicLink():

    ret = True

    # The source is the selected file and the destination is the
    # develop folder inside the current directory

    src = str(le_file_name.text())
    cwd = os.getcwd()
    dst = os.path.join(cwd, "develop", ntpath.basename(src))

    try:
        os.symlink(src, dst)
    except OSError:
        alert('The file "' + dst + '" already exists')
        ret = False

    return ret


# ------------------------------------------------------------------------------
# sendFileToServer()
#
# Description: This function uploads the selected file to the remote server.
# ------------------------------------------------------------------------------

def sendFileToServer():

    ret = True

    src = str(le_file_name.text())
    os.system('curl --upload-file ' + src + ' -X POST -H "filename:' + ntpath.basename(src) + '" -H "filetype:remote" http://' + REMOTE_SERVER + ':' + PORT + '/upload')

    return ret


# ------------------------------------------------------------------------------
# sendFileReferenceToServer()
#
# Description: This function uploads the reference of the selected file to the
#              remote server.
# ------------------------------------------------------------------------------

def sendFileReferenceToServer():

    ret = True

    src = str(le_file_name.text())
    
    # The option "filetype:local" prevents from curl to send the file.
    os.system('curl --upload-file ' + src + ' -X POST -H "filename:' + ntpath.basename(src) + '" -H "filetype:local" -H "pathname:' + src + '" http://' + REMOTE_SERVER + ':' + PORT + '/upload')

    return ret

# ------------------------------------------------------------------------------
# alert()
#
# Description: This function shows a message to the user.
# @param msg : The input message to be shown to the user.
# return     : None
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
# Description: This function shows a file dialog to the user in order to 
#              select a file from the local file system.
# return     : None
# ------------------------------------------------------------------------------

def OnSelectFile():

    le_file_name.setText(QFileDialog.getOpenFileName())

# ------------------------------------------------------------------------------
# OnUploadFile()
#
# Description: This function decides, depending on the value of a checkbox,
#              if the file must be uploaded to a server or it only has to be
#              symbolically linked to the shared folder between docker and the
#              host.
#              This function ensures that user has selected a file first.
# return     : None
# ------------------------------------------------------------------------------

def OnUploadFile():

    ret = True

    src = str(le_file_name.text())
    if src == '':
        alert('Choose a file first')
        ret = False
    else:
        src = src.replace('file://', '')
        le_file_name.setText(src)

        if LOCAL_SERVER == REMOTE_SERVER:
            if cb_create_copy.checkState() == Qt.Checked:
                ret = sendFileToServer()
            else:
                ret = createSymbolicLink()
                if ret == True:
                    ret = sendFileReferenceToServer()
        else:
            ret = sendFileToServer()

    if ret == True:
        alert('Done.')
        le_file_name.setText('')

    return ret


# ------------------------------------------------------------------------------
# OnCancelUpload()
#
# Description: Close the application.
# return     : None
# ------------------------------------------------------------------------------

def OnCancelUpload():

    sys.exit(0)

# ==============================================================================
# MAIN
# ==============================================================================
	
if __name__ == '__main__':

    createMainWindow()



