# Low-Level-Network-Communication-in-C

Thi project contains two programs
daytime.c
dayserve.c

dayserve is a server process that listens on an ephemeral TCP port for one connection.
When it receives a connection, it logs the hostname of the client to stdout and writes the current date and time to the client (as text) via the socket connection.
See library routines time() and ctime() to obtain and format the time of day


daytime is a client program that takes one argument on the command line.  That argument is the server’s host name or IP address (in dotted decimal).  It makes a TCP connection to the indicated host and dayserve’s port number (or indicates the error, if it cannot) and then writes the information received from dayserve to stdout.
