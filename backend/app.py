import os, time
from ctypes import wintypes, windll, create_string_buffer, Array, c_char
from utils import return_type
GENERIC_READ: int  = 0x80000000
GENERIC_WRITE: int = 0x40000000

FILE_SHARE_READ:  int = 0x1
FILE_SHARE_WRITE: int = 0x2

MAX_BUFFER: int = 1024

INVALID_HANDLE_VALUE: int = wintypes.HANDLE(-1).value

class WinAPI():
        CreateFile   = windll.kernel32.CreateFileW
        ReadFile     = windll.kernel32.ReadFile
        WriteFile    = windll.kernel32.WriteFile
        GetLastError = windll.kernel32.GetLastError
        CloseHandle  = windll.kernel32.CloseHandle

class App():
    def __init__(self):
        self.stringBufferWrite: Array[c_char] | None
        self.stringBufferRead:  Array[c_char] | None
        self.loop: bool = True

    def run(self) -> int:
        try:
            while self.loop:
                self.main_loop()

        except KeyboardInterrupt:
            return 69
        
    def get_pipe_handle(self):
        return windll.kernel32.CreateFileW(
           u"\\\\.\\pipe\\MyPipe",
           FILE_SHARE_READ | FILE_SHARE_WRITE,
           0,
           None,
           3,
           0,
           None
        )
        
    def read_from_pipe(self) -> int | str:
        hPipe = self.get_pipe_handle()
        if(hPipe == INVALID_HANDLE_VALUE):
            print("Failed to opne named pipe.")
            return 1
        
        self.stringBufferRead = create_string_buffer(MAX_BUFFER)
        bBytesRead: bool = WinAPI.ReadFile(
            hPipe,
            self.stringBufferRead,
            MAX_BUFFER,
            None,
            None
        )

        if (not bBytesRead):
            print("Failed to read from the pipe")
            print(WinAPI.GetLastError())
            return 1
        
        message:str = self.stringBufferRead.value.decode('utf-8')
        del self.stringBufferRead
        WinAPI.CloseHandle(hPipe)
        time.sleep(0.6)
        return message
    
    def write_to_pipe(self, message: str) -> int:
        hPipe = self.get_pipe_handle()
        if(hPipe == INVALID_HANDLE_VALUE):
            print("Failed to opne named pipe.")
            return 1
        
        self.stringBufferRead = create_string_buffer(MAX_BUFFER)
        bBytesRead: bool = WinAPI.ReadFile(
            hPipe,
            self.stringBufferRead,
            MAX_BUFFER,
            None,
            None
        )

        if (not bBytesRead):
            print("Failed to read from the pipe")
            print(WinAPI.GetLastError())
            return 1
        
        message:str = self.stringBufferRead.value.decode('utf-8')
        del self.stringBufferRead
        WinAPI.CloseHandle(hPipe)
        time.sleep(0.6)
        return message

    def main_loop(self):
        message = self.read_from_pipe()

        if(type(message) == int): 
            return message
        print(message)
        time.sleep(0.6)

        result = self.write_to_pipe("Hello from something-side?")
        if(result != 0):
            return result