class Entity:
    def __init__(self, name):
        self.name = name
        self.customers = set(())
        
    def enter(self, customer):
        self.customers.add(customer);
        
    def exit(self, customer):
        self.customers.remove(customer)
    
    def getCustomers(self):
        return self.customers

class Department(Entity):
    def __init__(self, name, departmentId):
        Entity.__init__(self, name)
        self.departmentId = departmentId
        self.items = []
        self.observers = []
        
    def enter(self, customer):
        Entity.enter(self, customer)
        customer.departmentId = self.departmentId
        
    def exit(self, customer):
        Entity.exit(self, customer)
        customer.departmentId = None
        
    def addItem(self, item):
        self.items.append(item)
        for observer in self.observers:
            observer.newItemNotification(item)
            
    def priceChangeNotification(self, item):
        for observer in self.observers:
            observer.priceChangeNotification(item)
        
    def getItems(self):
        return self.items
    
    def getObservers(self):
        return self.observers
    
    def addObserver(self, observer):
        self.observers.append(observer)


        