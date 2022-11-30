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


class Client:
    def __init__(self):
        self.children = []

    def addChild(self, directory):
        self.children.append(directory)


def testDriver():
    client = Client()

