class return_type:
    def __init__(self, arg_type):
        self.returned: bool
        if(isinstance(arg_type, type)):
            self.type = arg_type
        else:
            raise "User must provide a type, not a variable."