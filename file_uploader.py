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

REMOTE_SERVER      = 'localhost'
PORT               = '3000'
LOCAL_INSTALLATION = True
UPLOAD_FILE        = True
DO_NOT_UPLOAD_FILE = False

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
le_destination     = QtGui.QLineEdit()
cb_symblink        = QtGui.QCheckBox()
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

    le_destination.setParent(w)
    le_destination.setGeometry(COL_2, LINE_1 + LINE_SPACE * 1, COL_3 - COL_2, CONTROL_H)
    le_destination.setAcceptDrops(True)

    cb_symblink.setParent(w)
    cb_symblink.setText("Create a symbolic link to the file")
    cb_symblink.move(COL_1, LINE_1 + LINE_SPACE * 2)
    cb_symblink.setCheckState(Qt.Unchecked)

    # If it is a local installation the user can copy the file to the docker's shared folder or create a symbolic link to the file there
    # If it is a remote installation then, the file must be loaded into the server
    cb_symblink.setVisible(LOCAL_INSTALLATION)

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
# Description      : This function creates a symbolic link of the selected file
#                    in the shared folder between the docker container and the
#                    host.
# @param subfolder : Destination subfolder of the symbolic link. 
# return           : True if it is Ok, otherwise False.
# ------------------------------------------------------------------------------

def createSymbolicLink(subfolder):

    ret = True

    # The source is the selected file and the destination is the
    # develop folder inside the current directory

    src = str(le_file_name.text())
    cwd = os.getcwd()

    dst_path = os.path.join(cwd, "develop/webapp/data/", subfolder)
    try:
        os.makedirs(dst_path)
    except:
        pass
        
    dst = os.path.join(dst_path, ntpath.basename(src))

    alert(dst_path)
    alert(dst)

    try:
        os.symlink(src, dst)
    except OSError:
        alert('The file "' + dst + '" already exists')
        ret = False

    return ret


# ------------------------------------------------------------------------------
# registerFileOnServer()
#
# Description     : This function uploads the selected file to the remote server.
# @param filetype : 'local' -> the file is not uploaded. Only its reference.
#                   'remote'-> both, the file and its reference are uploaded.
# return          : True
# ------------------------------------------------------------------------------

def registerFileOnServer(file_name, upload_file, subfolder):

    ret = True

    command = 'curl --upload-file '
    command = command + file_name
    command = command + ' -X POST '
    command = command + '-H "filename:' + file_name + '" '
    command = command + '-H "subpath:' + subfolder + '" '
    if upload_file == True:
        command = command + '-H "upload:yes" '
    else:
        command = command + '-H "upload:no" '
    command = command + 'http://' + REMOTE_SERVER + ':' + PORT + '/datafiles'

    os.system(command)

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

    subfolder = str(le_destination.text())

    src = str(le_file_name.text())
    if src == '':
        alert('Choose a file first')
        ret = False
    else:
        src = src.replace('file://', '')
        le_file_name.setText(src)

        file_name = ntpath.basename(src)

        if LOCAL_INSTALLATION == True:
            if cb_symblink.checkState() == Qt.Checked:
                ret = createSymbolicLink(subfolder)
                if ret == True:
                    ret = registerFileOnServer(file_name, DO_NOT_UPLOAD_FILE, subfolder)
            else:
                ret = registerFileOnServer(file_name, UPLOAD_FILE, subfolder)
        else:
            ret = registerFileOnServer(file_name, UPLOAD_FILE, subfolder)

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



