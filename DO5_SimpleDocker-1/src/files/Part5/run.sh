#! /bin/bash

gcc -o server server.c -lfcgi
service nginx start
nginx -s reload
spawn-fcgi -p 8080 server
