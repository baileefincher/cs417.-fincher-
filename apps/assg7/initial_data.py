from customer import Customer
from department import Department
from item import Item

nextDepartmentId = 1

def createDepartment(name):
    global nextDepartmentId
    dept = Department(name, nextDepartmentId)
    nextDepartmentId += 1
    return dept
    
def initialize():
    books = createDepartment("Books")
    music = createDepartment("Music")
    software = createDepartment("Software")
    video = createDepartment("Video")
    
    books.addItem(Item.createItem("Verity", books, 9.99))
    books.addItem(Item.createItem("It Ends With Us", books, 12.95))
    books.addItem(Item.createItem("Reminders of Him", books, 8.98))
    
    music.addItem(Item.createItem("Red", music, .99))
    music.addItem(Item.createItem("Reputation", music, .99))
    music.addItem(Item.createItem("1989", music, 12.16))
    
    software.addItem(Item.createItem("FincherNet Ultimate", software, 1200.00))
    software.addItem(Item.createItem("Microsoft Office", software, 99.99))
    software.addItem(Item.createItem("FincherNet Ultimate Pro", software, 9000.00))
    
    video.addItem(Item.createItem("Gone Girl", video, 9.99))
    video.addItem(Item.createItem("Dear John", video, 11.00))
    video.addItem(Item.createItem("Cheaper by the Dozen", video, 8.95))
    
    departments = [books, music, software, video]
    customers = [Customer("Fred"), Customer("Wilma"), Customer("Barney"), Customer("Betty")]
    
    return (departments, customers)
    