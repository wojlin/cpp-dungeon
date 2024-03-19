#ifndef MAIN_H
#define MAIN_H

#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <iostream>
#include <locale>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#include <ncursesw/ncurses.h>

#include "levelGenerator.h"


#define GAME_NAME "dungeon game"

#define NETWORK_PORT 2137
#define NETWORK_ERROR 69

class debuggingInstance
{
    public:
        void launch()
        {
            std::cout << "### " << GAME_NAME << " debugging tool ###" << std::endl;
            createServer(NETWORK_PORT);
            launchGameInstance();
            awaitConnection();
            awaitMessages();
        }

    protected:

        int serverSocket = -1;
        int clientSocket = -1;

        void createServer(int port)
        {
            serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (serverSocket == -1) {
                throw NetworkError("Error creating socket");
            }

            // Set SO_REUSEADDR option
            int reuse = 1;
            if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) 
            {
                throw NetworkError("Error setting socket option");
            }

            // Bind the socket to an address and port
            sockaddr_in serverAddr;
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any address
            serverAddr.sin_port = htons(port); // Port number


            if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
            {
                throw NetworkError("Error binding socket");
            }

            // Listen for incoming connections
            if (listen(serverSocket, 1) == -1) 
            {
                throw NetworkError("Error binding socket");
            }

            std::cout << "Server waiting for connections..." << std::endl;    
        }

        void launchGameInstance()
        {
            system("terminator -g \"../config/terminator.cfg\" -p \"dungeon\" --geometry=1000x1000 -T \"dungeon game\" -e \"./dungeon game\" &");
        }

        void awaitConnection()
        {
            sockaddr_in clientAddr;
            socklen_t clientAddrSize = sizeof(clientAddr);
            clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
            if (clientSocket == -1) 
            {
                throw NetworkError("Error accepting connection");
            }

            std::cout << "Client connected" << std::endl;
        }

        void awaitMessages()
        {
            char buffer[1024];
            while (true) {
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0) {
                    std::cerr << "Error receiving data" << std::endl;
                    break;
                }
                buffer[bytesReceived] = '\0'; // Null-terminate the received data
                
                std::cout << "Received: " << buffer << std::endl;
                
                if (strcmp(buffer, "end") == 0) 
                {
                    
                    std::cout << "Received 'end' command. Closing connection and program." << std::endl;
                    closeConnection();
                    break;
                }
            }
        }

        void closeConnection()
        {
            close(clientSocket);
            close(serverSocket);
        }
};

class gameInstance
{
    public:

        void launch()
        {
            createClient();
            setupGUI();
            
            
            levelGenerator level(1);
            level.generatePreview("preview.png", 1);

            bool end = false;
            while(!end)
            {
                level.print(level.getPlayerPos().x, level.getPlayerPos().y, 80, 40);
                int input = getch();
                clear();
                if(input == 68 || input == 97) 
                { 
                    coords pos = level.getPlayerPos();
                    level.setPlayerPos(pos.x - 1, pos.y);

                    send(clientSocket, "A", strlen("A"), 0);
        
                }
                else if(input == 67 || input == 100) 
                { 
                    coords pos = level.getPlayerPos();
                    level.setPlayerPos(pos.x + 1, pos.y);

                    
                    send(clientSocket, "D", strlen("D"), 0);
                }
                else if(input == 65 || input == 119) 
                { 
                    coords pos = level.getPlayerPos();
                    level.setPlayerPos(pos.x, pos.y - 1);

                    
                    send(clientSocket, "S", strlen("S"), 0);
                }
                else if (input == 66 || input == 115) 
                { 
                    coords pos = level.getPlayerPos();
                    level.setPlayerPos(pos.x, pos.y + 1);

                    send(clientSocket, "W", strlen("W"), 0);
                }
                else if(input == 'q')
                {
                    send(clientSocket, "end", strlen("end"), 0);
                    end=true;
                }
                else 
                { 
                    mvprintw(0, 0, "%d", input);
                }

            }
            
            teardownGUI();
        }

    protected:
        int clientSocket = -1;

        void setupGUI()
        {
            std::locale::global(std::locale("")); // Set the global locale to the user's preferred locale
            std::wcout.imbue(std::locale()); // Set the wide character output stream to use the global locale
            setlocale(LC_ALL, "");

            initscr();
            start_color();
            cbreak();
            noecho();
            //keypad(stdscr, TRUE);

            // Enable Unicode support
            if (!has_colors() || !can_change_color() || !has_ic()) {
                endwin();
                throw GUIError("failed to initialize curses module");
            }
            if (use_default_colors() == ERR) {
                endwin();
                throw GUIError("failed to initialize curses module");
            }

        }

        void createClient()
        {
            clientSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (clientSocket == -1) 
            {
                throw NetworkError("Error creating socket");
            }

            sockaddr_in serverAddr;
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(NETWORK_PORT); 
            inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

            if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
            {  
                throw NetworkError("Error connecting to server");
            }
        }

        void teardownGUI()
        {
            endwin();   // End ncurses
        }

};

class core
{
    public:

        int launch(int argc, char* argv[])
        {
            if(argc == 1)
            {
                debuggingInstance debug = debuggingInstance();
                debug.launch();
            }
            else
            {
                gameInstance game = gameInstance();
                game.launch();
            }
            return 0;
        }

    protected:
        
};

#endif