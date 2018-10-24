/*************** PROGRAM IDENTIFICATION*****************************
//*																   *
//* PROGRAM FILE NAME: Source.cpp Assisgnment #:6				   *
//*																   *
//* PROGRAM AUTHOR						______________________     *
//*										   Rishika Swarnkar        *
//*																   *
//*COURSE: CSC 36000 1							DATE:April 22,2018 *
//*																   *
/********************************************************************/
//*************** PROGRAM DESCRIPTION ********************************
//* PROCESS:The program uses a binary tree data structure to store  *
//* the data.  Each time an I is read, the data item is to be added *
//* to the tree structure keeping the tree sorted, A-Z, for INORDER *
//* TRAVERSALS.The tree is to be kept sorted by ID number. 
//* Each time a D is read, the program searches the tree and delete 
//* the node in question from the tree.A P means that the tree is to
//* be printed according to the instructions. An S indicates that the 
//*on-hand inventory count is to be reduced due to sales activities,
//*an R means that all or part of an inventory order has been received 
//*and that the quantity indicated needs to be transferred from the 
//*“On Order” category to the “On Hand” category.  
//*Finally, a code of O means the on-order inventory count is to be 
//*increased due to restocking activities. You may assume that if the 
//*operation is an S that there are enough items in the inventory to
//*handle the transaction. The program guards against adding duplicate
//*items and insure that we do not attempt to delete or change a nonexistent item.
//*OUTPUT: When the code is a P,the program is to prints out either 
//*the entire tree using INORDER TRAVERSAL or an individual item 
//*depending on the secondary code of E or N. A separate page of output 
//*is generated only for each print command of the entire tree.
//*When printing the entire tree,it includes the same output
//*heading on each page so any employee can tell what the output means.
//*																	*
//* USER DEFINED													*
//* MODULES :														*
//*insert(Node*,Node,ofstream &):Inserts the node in The Binary Sear*
//*								 -ch Tree							*
//*printInventory(Node *, ofstream &):Prints the Entire Inventory   *
//*								based on the key					*
//*newNode(Node):Makes a new node and returns a Node pointer to		*
//*				itself												*
//*pageBreak(ofstream&, int&):Insert Lines to Break the page		*
//*updateSales(struct Node*, string, int, ofstream&):Update Quantity*
//*                           on hand								*
//*updateStockOnHand(struct Node*, string, int, ofstream&):Update   *
//*							Quantity On order						*
//*updateRestock(struct Node*, string, int, ofstream&):Update       *
//*						    Quantity on hand						*
//*printNode(struct Node*, string, ofstream &):Print all the        *
//*					information contained in a Node					*
//*Header(ofstream&):Prints the output preamble						*
//*Footer(ofstream&):Prints the output preamble						*
//*minValueNode(struct Node*):Searches for the Minimum Value in the *
//*				    tree and Returns a node pointer					*
//deleteNode(struct Node*,string, ofstream &):Checks if the         *
//*                 requested id is there to deletes the item if it *
//*                 exist											*
//********************************************************************/
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
int lineCount = 0;
struct Node
{
	  //saves all the infromation about the items
	  Node *left, *right, *parent;
	  string id;
	  string name;
	  int quantityOnHand;
	  int quantityOnOrder;
};
  /*************************************/
  /*******FUNCTION DECLARATIONS********/
Node *newNode(Node input);
Node *insert(Node *node, Node input, ofstream &fout);
void printInventory(Node *root, ofstream &fout);
void printInventory(Node *root, ofstream & fout);
Node * newNode(Node input);
void pageBreak(ofstream &fout, int & printedLine);
void updateSales(struct Node* root, string id, int sales, ofstream &fout);
void updateStockOnHand(struct Node* root, string id, int order, ofstream &fout);
void updateRestock(struct Node* root, string id, int orderQuan, ofstream  &fout);
void printNode(struct Node* root, string id, ofstream &fout);
void Header(ofstream& fout);
void Footer(ofstream& fout);
struct Node * minValueNode(struct Node* nodePtr);
struct Node* deleteNode(struct Node* root, string id, ofstream &fout);
  /**********************************/
  Node *insert(Node *nodePtr, Node input, ofstream &fout)
  {
	  //Receives - A Node pointer , A Node structure , the outfile file
	  //Task - Inserts the node in The Binary Search Tree
	  //Returns - A Node pointer
	  Node *leaf;
	  Node *currNode, *parNode;
	  bool found = false; // Check if the Node already exists
						  // Set the pointers to start at the root
	  currNode = nodePtr;
	  parNode = NULL;
	  while ((found == false) && (currNode != NULL))
	  { // Set flag to true if we find the node
		  if (input.id == currNode->id)
		  {
			  found = true;
			  fout << "ERROR - Attempt to insert a duplicate item (<# " << input.id << "> ) into the database." << endl;
			  fout <<  "-----------------------------------------------------------" <<
				  endl;
			  lineCount += 2;
		  }
		  else
		  {
			  parNode = currNode;
			  // move down the appropriate branch of the tree
			  if (input.id < currNode->id)
				  currNode = currNode->left;
			  else
				  currNode = currNode->right;
		  }
	  }
	  /* If the tree is empty, return a new node */
	  if (nodePtr == NULL)
	  {
		  leaf = newNode(input);
		  fout << "Item ID Number < #" << leaf->id << "> successfully entered into database." << endl;
			  fout <<
			  "-----------------------------------------------------------" <<
			  endl;
		  lineCount += 2;
		  return leaf;
	  }
	/* Otherwise, recur down the tree */
	if (input.id < nodePtr->id)
	{
		nodePtr->left = insert(nodePtr->left, input, fout);
		nodePtr->left->parent = nodePtr;
	}
	else if (input.id> nodePtr->id)
	{
		nodePtr->right = insert(nodePtr->right, input, fout);
		nodePtr->right->parent = nodePtr;
	}
	return nodePtr;// root pointer
  }
  /***********************************/
  void printInventory(Node *root, ofstream & fout)
  {
	  //Receives - Node pointer and the outfile file
	  //Task - Prints the Entire Inventory based on the key
	  //Returns - Nothing
	  bool leftdone = false; // set flag for left print
							 // Start traversal from root
	  while (root)
	  {
		  if (!leftdone)
		  {
			  // If left child is not traversed, find the leftmost child
			  while (root->left)
				  root = root->left;
		  }
		  // Print root's data
		  fout << setw(10) << root->id << setw(25) << root->name << setw(15) <<
			  root->quantityOnHand;
		  fout << setw(10) << root->quantityOnOrder;
		  fout << endl;
		  lineCount++;
		  // Mark left as done
		  leftdone = true;
		  if (root->right)
		  {
			  leftdone = false;
			  root = root->right;
		  }
		// If right child doesn't exist, move to parent
		  else if (root->parent)
		  {
			  // If this node is right child of its parent,
			  // visit parent's parent first
			  while (root->parent &&
				  root == root->parent->right)
				  root = root->parent;
			  if (!root->parent)
				  break;
			  root = root->parent;
		  }
		  else break;
	  }
  }
  /**********************************/
  Node * newNode(Node input)
  {
	  //Receives - Node structure
	  //Task - make a new node
	  //Returns - Node pointer to itself
	  // A utility function to create a new BST node
	  Node *temp = new Node;
	  temp->id = input.id;
	  temp->name = input.name;
	  temp->quantityOnHand = input.quantityOnHand;
	  temp->quantityOnOrder = input.quantityOnOrder;
	  temp->parent = temp->left = temp->right = NULL;
	  return temp;
  }
  /*************************************/
  void pageBreak(ofstream &fout, int & printedLine)
  {
	  //Receives - Output file and number of lines already printed
	  //Task - Insert Lines to Break the page
	  //Returns - Nothing
	  for (int i = 0; i < 50 - printedLine; i++)
	  {
		  fout << endl;
	  }
	  return;
  }
  /**************************************/
  void updateSales(struct Node* root, string id, int sales, ofstream &fout)
  {
	  //Receives - A Node pointer , id to be updated , quantity sold, the outfile file
		  //Task - Update Quantity on hand
		  //Returns - Nothing
		  //look if the node exist in the tree
		  Node *currNode, *parnode;
	  // Declare a flag to indicate the node to be deleted is found
	  bool found = false;
	  // Set the pointers to start at the root
	  currNode = root;
	  parnode = NULL;
	  // Search the tree until we find the node to be deleted or until there
	  // are no more nodes to examine
	  while ((found == false) && (currNode != NULL))
	  { // Set flag to true if we find the node
		  if (id == currNode->id)
		  {
			  found = true;
			  //update the Quantity on hand due to sales
			  currNode->quantityOnHand = currNode->quantityOnHand - sales;
			  fout << "Quantity on Hand for item (<#" << id << "> ) successfully  updated." << endl;
				  fout << "-----------------------------------------------------------" <<
				  endl;
			  lineCount += 2;
			  return;
		  }
		  else // Otherwise keep track of the parent node and move down
			   // the appropriate branch of the tree
		  {
			  parnode = currNode;
			  if (id < currNode->id)
				  currNode = currNode->left;
			  else
				  currNode = currNode->right;
		  }
	  }
	  if (found == false)
	  {
		  fout << "Item (<#" << id << ">) not in database. Data not updated."
			  << endl;
		  fout << "----------------------------------------------------------- "
			  << endl;
		  lineCount += 2;
		  return;
	  }
  }
	/*************************************/
	void updateStockOnHand(struct Node* root, string id, int order, ofstream &fout)
{
	//Receives - A Node pointer , id to be updated, quantity ordered , the	outfile file
		//Task - Update Quantity On order
		//Returns - Nothing
		//look if the node exist in the tree
		Node *currNode, *parnode;
		// *node1, *node2, *node3;
	// Declare a flag to indicate the node to be deleted is found
		bool found = false;
	// Set the pointers to start at the root
	currNode = root;
	parnode = NULL;
	// Search the tree until we find the node to be deleted or until there
	// are no more nodes to examine
	while ((found == false) && (currNode != NULL))
	{ // Set flag to true if we find the node
		if (id == currNode->id)
		{
			found = true;
			//update the Quantity on hand due to sales
			currNode->quantityOnOrder = currNode->quantityOnOrder - order;
			currNode->quantityOnHand = currNode->quantityOnHand + order;
			fout << "Quantity on Hand and Quantity on Order for item (<#" <<
				id << "> ) successfully updated." << endl;
			fout <<
				"-----------------------------------------------------------" <<
				endl;
			lineCount += 2;
			return;
		}
		else // Otherwise keep track of the parent node and move down
			 // the appropriate branch of the tree
		{
			parnode = currNode;
			if (id < currNode->id)
				currNode = currNode->left;
			else
				currNode = currNode->right;
		}
	}
	if (found == false)
	{
		fout << "Item (<#" << id << ">) not in database. Data not updated."
			<< endl;
		fout << "----------------------------------------------------------- "
			
			<< endl;
		lineCount += 2;
		return;
	}
}
  /**************************************************/
  void updateRestock(struct Node* root, string id, int orderQuan, ofstream
	  &fout)
  {
	  ///Receives - A Node pointer , id to be updated, ordered quantity , the outfile file
		  //Task - Update Quantity on hand
		  //Returns - Nothing
		  //look if the node exist in the tree
		  Node *currNode, *parnode;// , *node1, *node2, *node3;
								   // Declare a flag to indicate the node to be deleted is found
		  bool found = false;
	  // Set the pointers to start at the root
	  currNode = root;
	  parnode = NULL;
	  // Search the tree until we find the node to be deleted or until there
	  // are no more nodes to examine
	  while ((found == false) && (currNode != NULL))
	  { // Set flag to true if we find the node
		  if (id == currNode->id)
		  {
			  found = true;
			  //update the Quantity on hand due to sales
			  currNode->quantityOnHand = currNode->quantityOnHand + orderQuan;
			  fout << "Quantity on Order for item ( <#" << id << "> ) successfully updated." << endl;
				  fout <<
				  "-----------------------------------------------------------" <<
				  endl;
			  lineCount += 2;
			  return;
		  }
		  else // Otherwise keep track of the parent node and move down
			   // the appropriate branch of the tree
		  {
			  parnode = currNode;
			  if (id < currNode->id)
				  currNode = currNode->left;
			  else
				  currNode = currNode->right;
		  }
	  }
	  if (found == false)
	  {
		  fout << "Item (<#" << id << ">) not in database. Data not updated."
			  << endl;
		  fout << "----------------------------------------------------------- "
			  << endl;
		  lineCount += 2;
		  return;
	  }
  }
  /*************************************/
  void printNode(struct Node* root, string id, ofstream &fout)
  {
	  //Receives - A Node pointer , id to be updated , the outfile file
	  //Task - Print the Node
	  //Returns - Nothing
	  //look if the node exist in the tree
	  Node *currNode, *parnode;// , *node1, *node2, *node3;
							   // Declare a flag to indicate the node to be deleted is found
		  bool found = false;
	  // Set the pointers to start at the root
	  currNode = root;
	  parnode = NULL;
	  // Search the tree until we find the node to be deleted or until there
	  // are no more nodes to examine
	  while ((found == false) && (currNode != NULL))
	  { // Set flag to true if we find the node
		  if (id == currNode->id)
		  {
			  found = true;
			  fout << " JAKE’S HARDWARE INVENTORY REPORT " << endl;
			  fout << setw(10) << "Item" << setw(25) << "Item " << setw(10) <<
				  "Quantity" << setw(10);
			  fout << "Quantity" << setw(10);
			  fout << endl;
			  fout << setw(10) << "ID Number" << setw(25) << "Description" <<
				  setw(10) << "on hand" << setw(10);
			  fout << "on order" << endl;
			  fout <<"-----------------------------------------------------------" <<endl;
			  lineCount += 4;
			  fout << setw(10) << currNode->id << setw(25) << currNode->name <<
				  setw(15) << currNode->quantityOnHand;
			  fout << setw(10) << currNode->quantityOnOrder;
			  // r << setw(10) <<root-> << setw(10) << Inventory[i].sp;
			  fout << endl;
			  fout <<
				  "-----------------------------------------------------------" <<	  endl;
			  lineCount += 2;
			  return;
		  }
		  else // Otherwise keep track of the parent node and move down
			   // the appropriate branch of the tree
		  {
			  parnode = currNode;
			  if (id < currNode->id)
				  currNode = currNode->left;
			  else
				  currNode = currNode->right;
		  }
	  }
	  if (found == false)
	  {
		  fout << "Item (<#" << id << ">) not in database to print." << endl;
		  fout << "----------------------------------------------------------- "
			  << endl;
		  lineCount += 2;
		  return;
	  }
  }
  /************************************/
  void Header(ofstream& fout)
  {
	  //Receives - the outfile file
	  //Task - Prints the output preamble
	  //Returns - Nothing
	  fout << setw(30) << "Rishika Swarnkar";
	  fout << setw(17) << "CSC 36000";
	  fout << setw(15) << "Section 11" << endl;
	  fout << setw(30) << "Spring 2018";
	  fout << setw(17) << "Assignment #5" << endl;
	  fout << setw(35) << "--------------------------------------";
	  fout << setw(35) << "-------------------------------------- " << endl <<
		  endl;
	  lineCount += 4;
	  return;
  }
  /************ END OF FUNCTION HEADER *****************/
  //***************************************************/
  /************* FUNCTION FOOTER **********************/
  void Footer(ofstream& fout)
  {
	  //Receives - the outfile file
	  //Task - Prints the output preamble
	  //Returns - Nothing
	  fout << endl;
	  fout << setw(35) << "------------------------------" << endl;
	fout << setw(35) << "| END OF PROGRAM OUTPUT |" << endl;
	fout << setw(35) << "-------------------------------" << endl;
	return;
  }
  /******* END OF FUNCTION FOOTER************/
  /*****************************************/
  struct Node * minValueNode(struct Node* nodePtr)
  {
	  //Receives - Node Pointer
	  //Task - Look for the Minimum Value in the tree
	  //Returns - A node pointer
	  struct Node* current = nodePtr;
	  /* loop down to find the leftmost leaf */
	  while (current->left != NULL)
		  current = current->left;
	  return current;
  }
  /**************************************/
  struct Node* deleteNode(struct Node* root, string id, ofstream &fout)
{
//Receives - A Node pointer , id to be updated , the outfile file
//Task - Checks if the requested id is there to delete,
// deletes the item if it exist
//Returns - New Node
//look if the node exist in the tree
Node *delnode, *parnode;//
						// Declare a flag to indicate the node to be deleted is found
bool found = false;
// Set the pointers to start at the root
delnode = root;
parnode = NULL;
while ((found == false) && (delnode != NULL))
{ // Set flag to true if we find the node
	if (id == delnode->id)
	{
		found = true;
	}
	else // Otherwise keep track of the parent node and move down
		 // the appropriate branch of the tree
	{
		parnode = delnode;
		if (id < delnode->id)
			delnode = delnode->left;
		else
			delnode = delnode->right;
	}
}
	if (found == false)
	{
		cout << "Node is not in the tree !" << endl;
		fout << "ERROR --- Attempt to delete an item (<#" << id << "> ) not in the database list." << endl;
		fout << "----------------------------------------------------------- "
			<< endl;
		lineCount += 2;
		return root;
	}
  // base case
  if (root == NULL) return root;
  // If the key to be deleted is smaller than the root's key,
  // then it lies in left subtree
  if (id < root->id)
	  root->left = deleteNode(root->left, id, fout);
  // If the key to be deleted is greater than the root's key,
  // then it lies in right subtree
  else if (id > root->id)//(key > root->key)
	  root->right = deleteNode(root->right, id, fout);// key);
													  // if key is same as root's key, then This is the node
													  // to be deleted
  else if (id == root->id)
  {
	  struct Node *temp;
	  // node with only one child or no child
	  if (root->left == NULL)
	  {
		  temp = root->right;
		  lineCount += 2;
	  }
	  else
	  {
		  temp = root->left;
		  lineCount += 2;
	  }
	  return temp;
	  fout << "Item ID Number (<#" << id << "> ) successfully deleted from database." << endl;
		  fout << "----------------------------------------------------------- "
		  << endl;
	  // node with two children: Get the inorder successor (smallest in the right subtree)
	  temp = minValueNode(root->right);
	  // Copy the inorder successor's content to this node
	  root->id = temp->id;
	  root->name = temp->name;
	  root->quantityOnHand = temp->quantityOnHand;
	  root->quantityOnOrder = temp->quantityOnOrder;
	// Delete the inorder successor
	root->right = deleteNode(root->right, temp->id, fout);
  }
  return root;
}
  /*********************/
  int main()
  {
	  char key; // key to determine the operation to the inventory
	  Node * root = NULL;
	  ifstream fin;
	  ofstream fout;
	  fout.open("Inventory.txt");// open input file
	  string idprint;
	  fin.open("tree_in.txt");// open output file
	  fin >> key;
	  Header(fout); // display function Header
	  Node inputData;
	  do
	  {
		  switch (key)
		  {
		  case 'I':
			  // Reads the information from file to a Node
			  fin >> inputData.id;
			  fin >> ws;
			  getline(fin, inputData.name);
			  fin >> inputData.quantityOnHand;
			  fin >> inputData.quantityOnOrder;
			  // Insert the node in the tree
			  root = insert(root, inputData, fout);
			  break;
		  case 'P':
			  char c;
			  fin >> c;
			  // Print on a new page
			  pageBreak(fout, lineCount);
			  lineCount = 0;// reset lineCoounter
			  fout << left;
			  if (c == 'E')
			  {
				  fout << " JAKE’S HARDWARE INVENTORY REPORT " << endl;
				  fout << setw(10) << "Item" << setw(25) << "Item " << setw(10)
					  << "Quantity" << setw(10);
				  fout << "Quantity" << setw(10);
				  fout << endl;
				  fout << setw(10) << "ID Number" << setw(25) << "Description"
				  << setw(10) << "on hand" << setw(10);
				fout << "on order" << endl;
				fout <<"-----------------------------------------------------------" << endl;
					lineCount += 3;
				printInventory(root, fout);
				fout <<"-----------------------------------------------------------" << endl;
					lineCount += 1;
			  }
			  else if (c == 'N')
			  {
				  //Print just one node of the tree
				  fin >> ws;
				  getline(fin, inputData.id);
				  idprint = inputData.id;// id to be printed
				  printNode(root, idprint, fout);
			  }
			  break;
		  case 'D':
			  // Read the id to Delete
			  fin >> inputData.id;
			  fin >> ws;
			  getline(fin, inputData.name);
			  // Delete Node
			  deleteNode(root, inputData.id, fout);
			  break;
		  case 'S':
			  int sales;
			  fin >> inputData.id;
			  fin >> sales;
			  // Update the inventory when sale occurs
			  updateSales(root, inputData.id, sales, fout);
			  break;
		  case 'O':
			  int quantityOrdered;
			  fin >> inputData.id;
			  fin >> quantityOrdered;
			  // Update the inventory when quantity is ordered
			  updateRestock(root, inputData.id, quantityOrdered, fout);
			  break;
		  case 'R':
			  int order;
			  fin >> inputData.id;
			  fin >> order;
			  // Update stock when order is received
				  updateStockOnHand(root, inputData.id, order, fout);
			break;
		  default:
			  cout << "Error Reading File";
			  break;
		  }
		  fin >> key;
	  } while (key != 'Q');// Indicated end of input file
	  Footer(fout);// Ouput Footer
	  fin.close();// close input file
	  fout.close();// close output file
	  system("pause");
	  return 0;
  }