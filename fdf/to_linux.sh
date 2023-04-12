#!/bin/bash
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
NC="\033[0m"

LINUX="Makefile_linux"
MAC="Makefile_mac"

if [ ! -f $LINUX ]; then
	printf "${YELLOW}Makefile for Linux is already there!${NC}\n"
	exit 0
fi

mv Makefile $MAC && mv $LINUX Makefile && printf "done [ ${GREEN}Linux${NC} ]\n"
