#!/bin/bash

#Call the global_bash_var file
location="/etc/Restricted-Shell/"
source "${location}Src/global_bash_var"

#Check if system has dependencies

readlink_status=$(which readlink)

if [[ $? != 0 ]]
then
	echo -e "${RED_TEXT}Error: 2001${RESET}"
	exit -1
fi

path="$(readlink -f $1)"

if [[ "$path" =~ "$DEFAULT_LOCATION"* ]]
then
	echo -e "${RED_TEXT}Error: 1004${RESET}"
	exit -1
fi

rnano_status=$(which rnano)

if [[ ! -z $rnano_status ]]
then
	rnano $1
else
	nano $1
fi
