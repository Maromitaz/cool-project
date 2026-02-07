#include "utils.h"


//#define mMaxBuffer 1024
//constexpr const char *msg = "Hello from the server-side!";
//
//int main()
//{
//    HANDLE hPipe;
//    char buffer[mMaxBuffer] = { 0 };
//    DWORD bytesRead;
//
//    hPipe = CreateNamedPipeW(
//        L"\\\\.\\pipe\\MyPipe",
//        PIPE_ACCESS_DUPLEX,
//        PIPE_TYPE_MESSAGE |
//        PIPE_READMODE_MESSAGE|
//        PIPE_WAIT,
//        PIPE_UNLIMITED_INSTANCES,
//        mMaxBuffer,
//        mMaxBuffer,
//        0,
//        NULL);
//    
//    if(hPipe == INVALID_HANDLE_VALUE){
//        std::println("Failed to create named pipe.");
//        return 1;
//    }
//    std::println("Awaiting client connection...");
//
//    while(true)
//    {
//        if(ConnectNamedPipe(hPipe, NULL) != FALSE)
//        {
//            
//            // std::println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
//            // std::println("Client connected. Sending the following message...");
//            // std::println("{}", msg);
//            WriteFile(hPipe, msg, strlen(msg), &bytesRead, NULL);
//            // std::println("Message sent!");
//            
//            // std::println("#####################################################");
//            // std::println("Getting message from client...");
//            // DWORD bytesRead = 0;
//            bool result = ReadFile(hPipe, (LPVOID)buffer, (DWORD)mMaxBuffer, (LPDWORD)(&bytesRead), NULL);
//            if(result) std::println("Message recieved:\n {}", buffer);
//            else std::println("{}", GetLastError());
//            DisconnectNamedPipe(hPipe);
//            // std::println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
//        }
//    }
//
//    CloseHandle(hPipe);
//
//    return 0;
//}
