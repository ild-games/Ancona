import os

STATE_FILE_NAME = ".duckling_state"

##
# @brief Used to keep track of the build state. Implements the [] operator to store key,value pairs between builds.
# You must use the with keyword or call .close on the object once you are done using it.
# 
class BuildState:
    def __init__(self, cmake_src):
        self.state = {}
        self.filename = os.path.join(cmake_src,"build",STATE_FILE_NAME)
        os.makedirs(os.path.join(cmake_src,"build"),exist_ok=True)

        #Read in the state file if there is one
        if os.path.isfile(self.filename):
            with open(self.filename, "r") as state_file:
                self._read_file(state_file)

    def __getitem__(self, index):
        if index in self.state:
            return self.state[index]
        else:
            return None

    def __setitem__(self, index, value):
        self.state[index] = value

    def _read_file(self, state_file):
        for line in state_file:
            key,value = map(lambda s: s.strip(), line.split("=",1))
            self[key] = value

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.close()

    def close(self):
        with open(self.filename, "w") as state_file:
            for key,val in self.state.items():
                print("{}={}".format(key,val),file=state_file)
