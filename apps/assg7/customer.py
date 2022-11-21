from item import ItemList

class Customer:

    def __init__(self, name):
        self.name = name
        self.shoppingCart = ItemList()
        self.wishList = ItemList()
        self.departmentId = None
        
    def getShoppingCart(self):
        return self.shoppingCart
    
    def getWishList(self):
        return self.wishList
        
    def newItemNotification(self, item):
        print(f'Customer {self.name} notified of new item {item.name}')
        
    def priceChangeNotification(self, item):
        print(f'Customer {self.name} notified of price change for {item.name} to {item.price}')

        