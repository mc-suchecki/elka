#!/bin/bash

cat /etc/passwd | grep :$1: | cut -d : -f 1
