#!/usr/bin/env bash

usage()
{
    echo "usage: pgsql-tunnel.sh -a host [-u user]"
    echo "      Create tunnel to remote postgres server."
}

HOST=localhost
USER=postgres

while [ "$1" != "" ]; do
    case $1 in
        -a | --host )           shift
                                HOST=$1
                                ;;
        -u | --user )           shift
                                USER=$1
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done

ssh -f -L 5433:127.0.0.1:5432 ${USER}@${HOST} -N
