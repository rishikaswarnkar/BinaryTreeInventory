# BinaryTreeInventory
The program uses a binary tree data structure to store the data.Each time an I is read, the data item is to be added to the
tree structure keeping the tree sorted, A-Z, for INORDER TRAVERSALS.  
The tree is kept sorted by ID number.
Each time a D is read, the program searches the tree and deletes the node in question from the tree. 
A P means that the tree is printed according to the instructions. An S indicates that the on-hand inventory count
is reduced due to sales activities,an R means that all or part of an inventory order has been received and
that the quantity indicated needs to be transferred from the “On Order” category to the “On Hand” category.
Finally, a code of O means the on-order inventory count is increased due to restocking activities.
We may assume that if the operation is an S that there are enough items in the inventory to handle the transaction. 
We guard against adding duplicate items and to insure we do not attempt to delete or change a nonexistent item.

OUTPUT:  Each line of input is processed according to the command code at the beginning of each line.
It prints out of the tree’s contents is when the command code is a P.
When the code is a P, the program is to print out either the entire tree using INORDER TRAVERSAL or
an individual item depending on the secondary code of E or N. 
A separate page of output is to be generated only for each print command of the entire tree. 
When printing the entire tree,we include the same output heading on each page so any employee
can tell what the output means.


The heading is shown below.  ( NOTE:  Actual column spacing is at your discretion but all data must be properly aligned.): 


                                                    JAKE’S HARDWARE INVENTORY REPORT    
                                          Item                    Item                         Quantity        Quantity
                                          ID Number        Description             On hand        On Order
                                          ---------------------------------------------------------------------------
