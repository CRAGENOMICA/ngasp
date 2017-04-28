#!/bin/bash

gradle clean -b /develop/.gradle/build_samtoolslib.gradle
gradle build_and_export_lib -b /develop/.gradle/build_samtoolslib.gradle

chmod 777 /develop/webapp/bin/*
