from numpy.distutils.fcompiler import none


class Component:
    def __init__(self, name):
        self.name = name

    def getName(self):
        return self.name


class File(Component):
    def __init__(self, name):
        Component.__init__(self, name)

    def open(self):
        pass

    def close(self):
        pass;

    def draw(self):
        pass


class BinaryFile(File):
    def __init__(self, name):
        File.__init__(self, name)


class TextFile(File):
    def __init__(self, name):
        File.__init__(self, name)


class OfficeFile(File):
    def __init__(self, name):
        File.__init__(self, name)


class CppFile(File):
    def __init__(self, name):
        File.__init__(self, name)


class HppFile(File):
    def __init__(self, name):
        File.__init__(self, name)


class Directory(Component):
    def __init__(self, name):
        Component.__init__(self, name)
        self.files = []
        self.directories = []

    def addFile(self, file):
        self.files.append(file)

    def removeFile(self, file):
        self.files.remove(file)

    def addDirectory(self, directory):
        self.directories.append(directory)

    def removeDirectory(self, directory):
        self.directories.remove(directory)

    def getFiles(self):
        return self.files

    def getDirectories(self):
        return self.directories


class Factory:
    def create(self, name, componentType):
        if componentType == "dir":
            return Directory(name)
        elif componentType == 'binary':
            return BinaryFile(name)
        elif componentType == 'text':
            return TextFile(name)
        elif componentType == "office":
            return OfficeFile(name)
        elif componentType == "cpp":
            return CppFile(name)
        elif componentType == "hpp":
            return HppFile(name)

        return none


class Client:
    def __init__(self):
        self.children = []

    def addChild(self, directory):
        self.children.append(directory)

