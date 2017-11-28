#!/bin/bash

optarg() {
        local ARGNAME=$1; shift
        local DEFAULT=$1; shift
        for i in "$@"; do
                case $i in
                --${ARGNAME}=*)
                        echo "local ${ARGNAME//-/_}=${i#*=}"
                        return 0
                        ;;
                esac
        done
        echo "local ${ARGNAME//-/_}=${DEFAULT}"
        return 0
}

arg() {
        local ARGNAME=$1; shift
        for i in "$@"; do
                case $i in
                --${ARGNAME}=*)
                        echo "local ${ARGNAME//-/_}=${i#*=}"
                        return 0
                        ;;
                esac
        done
        (>&2 echo "Missing value for argument ${ARGNAME}!")
        echo "exit 1"
}

bind() {
        local CLOSURE=$1; shift
        local FN=$1; shift
        eval function "$CLOSURE" { "$FN" "$@" '"$@";' }
}