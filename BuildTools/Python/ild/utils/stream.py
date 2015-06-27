import functools

class Stream:
    def __init__(self, iterable):
        self.iterator = iterable

    def __iter__(self):
        return iter(self.iterator)

    def map(self, function):
        return Stream(map(function, self.iterator))

    def filter(self, function):
        return Stream(filter(function, self.iterator))

    def reduce(self, function, initializer=None):
        if initializer:
            return functools.reduce(function, self.iterator, initializer)
        return functools.reduce(function, self.iterator)
