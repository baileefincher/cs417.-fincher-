from customer import Customer
from department import Department, Entity
from item import ItemList, Item
import initial_data


class Store(Entity):
    def __init__(self, name):
        Entity.__init__(self, name)
        self.departments = []
        self.totalSales = 0
        
    def getShoppingCart(self):
        return ItemList()
    
    def getWishList(self):
        return ItemList()
    
    def getDepartments(self):
        return self.departments
    
    def addDepartment(self, department):
        self.departments.append(department)
        
    def exit(self, customer):
        Entity.exit(self, customer)
        if customer.shoppingCart.getItems():
            print(f"Checking out customer {customer.name}")
            print("Items purchased:")
            total = 0
            for item in customer.shoppingCart.getItems():
                print(f"    {item.name} ${item.price}")
                total += item.price
            
            totalFormatted = '${:,.2f}'.format(total)
            print(f"Total = {totalFormatted}")
            
            self.totalSales += total
            
def selectCustomer(customers):
    while True:
        print()
        for i in range(len(customers)):
            print(f"    {i+1}.  {customers[i].name}")
        choice = int(input("Please make a selection: "))
        idx = choice - 1;
        
        if idx < len(customers):
            return customers[idx]
        
def newCustomer(customers):
    while True:
        name = input("\nPlease enter your name: ")
        isNameTaken = False
        for customer in customers:
            if customer.name == name:
                isNameTaken = True
                break
            
        if isNameTaken:
            print("That customer name is already taken.  Please try again")
        else:
            customer = Customer(name)
            customers.append(customer)
            return customer
        
def displayItem(item, customer):
    choice = 0
    while choice != 3:
        print(f"\n{item.name}    {item.price}")
        print("    1.  Add Item to Shopping Cart")
        print("    2.  Add Item to Wish List")
        print("    3.  Exit")
        choice = int(input("Please make a selection:"))
        
        if choice == 1:
            quanity = -1
            while quanity < 0:
                quanity = int(input("Select quanity: "))
                if quanity > 0:
                    for i in range(quanity):
                        customer.getShoppingCart().addItem(item)
                    print(f"{quanity} {item.name}(s) added to shopping cart")
            return
        elif choice == 2:
            customer.getWishList().addItem(item)
            print(f"{item.name} added to wish list")
            return
        elif choice == 3:
            return
        
def selectItem(department):
    while True:
        items = department.getItems()
        numItems = len(items)
        print()
        for i in range(numItems):
            print(f"    {i+1}:    {items[i].name}    {items[i].price}")
        choice = int(input("Please make a selection:"))
            
        idx = choice - 1
        if idx < numItems:
            return items[idx]
            
def viewItemList(itemList, customerName, listType):
    choice = 0
    while choice != 2:
        items = itemList.getItems()
        if not items:
            print(f"{customerName}'s {listType} is empty")
        numItems = len(items)
        print()
        print(f"{listType} for {customerName}")
        total = 0
        for i in range(numItems):
            item = items[i]
            print(f"{i+1}:  {item.name}    {item.price}")
            total += item.price
            
        totalFormatted = '${:,.2f}'.format(total)
        print(f"\n Cart total is ${totalFormatted}")
        
        print("\n1.  Remove Item")
        print("2.  Exit")
        choice = int(input("Please make a selection:"))
        if choice == 1:
            item = int(input("Select item to remove: "))
            idx = item - 1
            if idx >= 0 and idx < numItems:
                itemList.removeItemAtIndex(idx)
        
    
        
def displayDepartmentMenu(department, customer):
    department.enter(customer)
    choice = 0
    while choice != 5:
        print()
        print(f"{customer.name}, Welcome to the {department.name} department!")
        print("    1. View Items")
        print("    2. View Shopping Cart")
        print("    3. View Wish List")
        print("    4. Register for Item Notifications")
        print("    5. Exit Department")
        choice = int(input("Please make a selection: "))
        
        if choice == 1:
            item = selectItem(department)
            displayItem(item, customer)
        elif choice == 2:
            viewItemList(customer.getShoppingCart(), customer.name, "Shopping Cart")
        elif choice == 3:
            viewItemList(customer.getWishList(), customer.name, "Wish List")
        elif choice == 4:
            department.addObserver(customer)
            
    department.exit(customer)
            
def selectDepartment(store, message="Please make a selection: "):
    departments = store.getDepartments()
    numDepartments = len(departments)
    exitOption = numDepartments + 1
    choice = ''
    
    while choice != exitOption:
        print()
        for i in range(numDepartments):
            print(f"    {i+1}.  {departments[i].name}")
        print(f"    {exitOption}.  Exit")
        choice = int(input(message))
        if choice == exitOption:
            return
        
        idx = choice - 1
        if idx < numDepartments:
            department = departments[idx]
            return department
        
    return None
        
def displayStoreMenu(store, customer):
    store.enter(customer)
    print(f"\nWelcome {customer.name}!")
    while True:
        department = selectDepartment(store)
        if department:
            displayDepartmentMenu(department, customer)
        else:
            break
            
    store.exit(customer)
    
def displayAdminMenu(store):
    choice = ''
    while choice != '3':
        totalSalesFormatted = '${:,.2f}'.format(store.totalSales)
        print(f"\n{store.name} Administration.  Total sales = {totalSalesFormatted}")
        print("   1. Add Item")
        print("   2. Change Item Price")
        print("   3. Exit")
        choice = input("Please make a selection: ")
        
        if choice == '1' or choice == '2':
            department = selectDepartment(store, "Select the department for the new item: ")
            if department:
                if choice == '1':
                    itemName = input("Item name: ")
                    price = float(input("Item price: "))
                    newItem = Item.createItem(itemName, department, price)
                    department.addItem(newItem)
                else:
                    item = selectItem(department)
                    newPrice = input(f"Enter the new price for {item.name}: ")
                    item.changePrice(newPrice)
            
def displayStoreWelcomeMenu(store, customers):
    choice = ''
    while choice != '4':
        print(f"\n\nWelcome to {store.name}")
        print("    1.  Existing Customer")
        print("    2.  New Customer")
        print("    3.  Administration")
        print("    4.  Exit")
        choice = input("Please make a selection: ")
        
        if choice == '1':
            customer = selectCustomer(customers)
            displayStoreMenu(store, customer)
        elif choice == '2':
            customer = newCustomer(customers)
            displayStoreMenu(store, customer)
        elif choice == '3':
            displayAdminMenu(store)
    
def main():
    initialData = initial_data.initialize()
    departments = initialData[0];
    customers = initialData[1]
    
    store = Store("Bailee-Mart")
    for dept in departments:
        store.addDepartment(dept)
        
    displayStoreWelcomeMenu(store, customers)

if __name__ == "__main__":
    main()
            
                    
        