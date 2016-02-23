#include <unistd.h>
#include <cstdlib>

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;

int main(int argc, char * argv[]) {
    const char * ip = "0.0.0.0";
    uint16_t port = 80;
    const char * dir = ".";

    int res;
    while ((res = getopt(argc, argv, "h:p:d:")) != -1) {
        switch (res) {
            case 'h':
                ip = optarg;
                break;
            case 'p':
                try {
                    port = lexical_cast<uint16_t>(optarg);
                } catch (...) {
                    cerr << "could not parse port number: " << optarg << endl;
                    return EXIT_FAILURE;
                }
                break;
            case 'd':
                dir = optarg;
                break;
            case '?':
            case ':':
                cerr << "Invalid command line syntax!\n";
                return EXIT_FAILURE;
        }
    }

    if (port == 0) { // TCP port 0 is reserved; atoi returns 0 if it couldn't parse the int
        cerr << "Incorrect port specified!" << endl;
        return EXIT_FAILURE;
    }

    pid_t pid = fork(); // forking to return fastly
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid > 0) {
        cout << "started server on " << ip << ":" << port << " at directory " << dir << endl;
        return EXIT_SUCCESS;
    }

    if (setsid() < 0) { // setting a new SID not to be orphaned
        perror("setsid");
        return EXIT_FAILURE;
    }

    if (chdir(dir) < 0) {
        perror("chdir");
        return EXIT_FAILURE;
    }

    // closing the fds: using them being a daemon is a bad idea anyway
    close(STDIN_FILENO);
    //close(STDOUT_FILENO);
    //close(STDERR_FILENO);

    io_service io_service;
    ip::tcp::socket server_socket {io_service};

    //server_socket.async_connect(server_endpoint, [](error_code & ec) { cerr << "lil))" }

    while (true) {
        sleep(228);
    }
}

