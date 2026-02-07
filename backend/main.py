import os

from app import App

if (__name__ == "__main__"):
    app = App()
    return_type = app.run()
    if(return_type == None):
        os._exit(0)
    os._exit(return_type)
    