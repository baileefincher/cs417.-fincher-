import unittest

from customer import Customer
from department import Department, Entity
from item import Item, ItemList
from store import Store

nextDepartmentId = 1

class TestCustomer(Customer):
    def __init__(self, name):
        Customer.__init__(self, name)
        self.newItems = []
        self.priceChanges = []
        
    def newItemNotification(self, item):
        Customer.newItemNotification(self, item)
        self.newItems.append(item)
        
    def priceChangeNotification(self, item):
        Customer.priceChangeNotification(self, item)
        self.priceChanges.append(item)

class EntityTest(unittest.TestCase):
    
    def setUp(self):
        self.entity = self.createEntity("testEntity")
        self.cust1 = TestCustomer("cust1")
        self.cust2 = TestCustomer("cust2")
        self.item1 = Item("item1", 1, self.entity, 1.01)
        self.item2 = Item("item2", 2, self.entity, 2.02)
        
    def createEntity(self, entityName):
        return Entity(entityName)
        
    def testConstruct(self):
        self.assertEqual("testEntity", self.entity.name)
        self.assertEqual(0, len(self.entity.getCustomers()))
        
    def testCustomersEnterExit(self):
        self.entity.enter(self.cust1)
        self.assertEqual(1, len(self.entity.getCustomers()))
        self.assertTrue(self.cust1 in self.entity.getCustomers())
        
        self.entity.enter(self.cust2)
        self.assertEqual(2, len(self.entity.getCustomers()))
        self.assertTrue(self.cust1 in self.entity.getCustomers())
        self.assertTrue(self.cust2 in self.entity.getCustomers())
        
        self.entity.exit(self.cust1)
        self.assertEqual(1, len(self.entity.getCustomers()))
        self.assertFalse(self.cust1 in self.entity.getCustomers())
        self.assertTrue(self.cust2 in self.entity.getCustomers())
        
        self.entity.exit(self.cust2)
        self.assertEqual(0, len(self.entity.getCustomers()))    
    	
class DepartmentTest(EntityTest):
            
    def createEntity(self, entityName):
        global nextDepartmentId
        dept = Department(entityName, nextDepartmentId)        
        nextDepartmentId += 1
        return dept
    
    def testCustomerEnterExit(self):
        self.assertIsNone(self.cust1.departmentId)
        self.entity.enter(self.cust1)
        self.assertEqual(self.entity.departmentId, self.cust1.departmentId)
        self.entity.exit(self.cust1)
        self.assertIsNone(self.cust1.departmentId)
        
    def testItemNotifications(self):
        self.entity.addObserver(self.cust1)
        self.assertEqual(0, len(self.cust1.priceChanges))
        self.assertEqual(0, len(self.cust1.newItems))
        
        self.entity.addItem(self.item1);
        self.assertEqual(1, len(self.cust1.newItems))
        self.assertEqual(0, len(self.cust1.priceChanges))
        self.assertTrue(self.item1 in self.cust1.newItems)
        
        self.item1.changePrice(3.03)
        self.assertTrue(self.item1 in self.cust1.priceChanges)
        self.assertEqual(1, len(self.cust1.priceChanges))
        
    
    
class StoreTest(unittest.TestCase):

    def setUp(self):
        EntityTest.setUp(self)
        self.store = self.entity
        self.department1 = Department("dept1", 1)
        self.department1.addItem(self.item1)
        self.department1.addItem(self.item2)
        
    def createEntity(self, entityName):
        return Store(entityName)
        
    def testConstruct(self):
        self.assertEqual("testEntity", self.store.name)
        self.assertTrue(isinstance(self.store.getShoppingCart(), ItemList))
        self.assertTrue(isinstance(self.store.getWishList(), ItemList))
        self.assertEqual(0, len(self.store.getDepartments()))
        
    def testAddDepartment(self):
        dept1 = Department("dept1", "1")
        self.store.addDepartment(dept1)
        
        dept2 = Department("dept2", "2")
        self.store.addDepartment(dept2)
        
        departments = self.store.getDepartments()
        self.assertEqual(2, len(departments))
        self.assertTrue(dept1 in departments)
        self.assertTrue(dept2 in departments)
        
    def testCheckOut(self):
        self.store.enter(self.cust1)
        self.store.enter(self.cust2)
        
        self.cust2.shoppingCart.addItem(self.item1)
        self.cust2.shoppingCart.addItem(self.item1)
        self.cust2.shoppingCart.addItem(self.item2)
        
        self.store.exit(self.cust1)
        # customer had nothing in shopping cart
        self.assertEqual(0, self.store.totalSales)
        
        self.store.exit(self.cust2)
        expectedTotal = self.item1.price * 2 + self.item2.price
        self.assertEqual(expectedTotal, self.store.totalSales)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
