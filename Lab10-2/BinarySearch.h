#ifndef LAB_6_BINARYSEARCHTREE_H
#define LAB_6_BINARYSEARCHTREE_H

#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
 public:
 int Comparisons = 0;
 int SearchComparisons = 0;
 
 BinarySearchTree( ) : root{ nullptr }
  {
  }

  /**
   * Copy constructor
   */
 BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
  {
    //root = clone( rhs.root );
  }

  /**
   * Move constructor
   */
 BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
  {
    rhs.root = nullptr;
  }

  /**
   * Destructor for the tree
   */
  ~BinarySearchTree( )
    {
      makeEmpty( );
    }

  /**
   * Copy assignment
   */
  BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
      BinarySearchTree copy = rhs;
      std::swap( *this, copy );
      return *this;
    }

  /**
   * Move assignment
   */
  BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
      std::swap( root, rhs.root );
      return *this;
    }


  /**
   * Find the smallest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMin( ) const
  {
    if( isEmpty( ) )
      cout << "Empty!\n";
    return findMin( root )->element;
  }

  int findHeight( ) const
  {
    int height = 0;
    if( isEmpty( ) )
      cout << "Empty!\n";
    return findHeight(root, height);
  }

  /**
   * Find the largest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMax( ) const
  {
    if( isEmpty( ) )
      cout << "Empty!\n";
    return findMax( root )->element;
  }

  /**
   * Returns true if x is found in the tree.
   */
  bool contains( const Comparable & x, int & Count ) const
  {
    return contains( x, root, Count );
  }

  vector<int> getLines( const Comparable & x ) const
    {
      return getLines( x, root );
    }

  /**
   * Test if the tree is logically empty.
   * Return true if empty, false otherwise.
   */
  bool isEmpty( ) const
  {
    return root == nullptr;
  }

  /**
   * Print the tree contents in sorted order.
   */
  void printTree( ostream & out = cout ) const
  {
    if( isEmpty( ) )
      out << "Empty tree" << endl;
    else
      printTree( root, out );
  }

  void outputTree( ofstream & out ) const
  {
    if( isEmpty( ) )
      out << "Empty tree" << endl;
    else
      printTree( root, out );
  }

  /**
   * Make the tree logically empty.
   */
  void makeEmpty( )
  {
    makeEmpty( root );
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert( const Comparable & x, int line )
  {
    insert( x, root, line);
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert( Comparable && x, int line )
  {
    insert( std::move( x ), root, line);
  }

  /**
   * Remove x from the tree. Nothing is done if x is not found.
   */
  void remove( const Comparable & x )
  {
    remove( x, root );
  }

  int size()
  {
    return size(root);
  }

  int depth()
  {
    return depth(root);
  }

  int getKeyComparisons()
  {
    return Comparisons;
  }

  int getSearchComparisons()
  {
    return SearchComparisons;
  }
  
  bool containsTwo( const Comparable & x ) const
  {
    return containsTwo( x, root );
  }
  
 private:
      struct BinaryNode
      {
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;
	int height;
       	vector<int> row;

      BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, vector<int> rowNum, int h = 0, int K = 0 )
      : element{ theElement }, left{ lt }, right{ rt }, row{ rowNum}, height{h} 
	{

	}

      BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt, vector<int> rowNum, int h = 0, int K = 0)
      : element{ std::move( theElement ) }, left{ lt }, right{ rt }, row { rowNum}, height{h}
	{

	}

      };

      //     int Comparisons;

      BinaryNode *root;
	/*
      int getKeyComparisons()
      {
	return Comparisons;
      }
  	*/    	
      int size(BinaryNode * n )
      {
	if (n == nullptr)
	  return 0;
	return 1 + size( n-> left ) + size(n->right);
      }

      int depth( BinaryNode * t)
      {
	if ( t == nullptr)
	  return -1;
	return  1 + max(depth( t-> left) , depth(t-> right));
      }

      
      /**
       * Internal method to insert into a subtree.
       * x is the item to insert.
       * t is the node that roots the subtree.
       * Set the new root of the subtree.
       */
      void insert( const Comparable & x, BinaryNode * & t, int rowNum)
      {
	if( t == nullptr ) {
	  vector<int> v;
	  v.push_back(rowNum);
	  t = new BinaryNode{x, nullptr, nullptr, v};
	}
	else if( x < t->element )
	  {
	    Comparisons++;
	    insert( x, t->left, rowNum);
	    balance(t);
	  }
	else if( t->element < x )
	  {
	    Comparisons += 2;
	    insert( x, t->right, rowNum);
	    balance(t);
	  }
	else
	  {
	    Comparisons +=2;
	    t->row.push_back(rowNum);  // Duplicate; do nothing
	  }
      }

      /**
       * Internal method to insert into a subtree.
       * x is the item to insert.
       * t is the node that roots the subtree.
       * Set the new root of the subtree.
       */
      void insert( Comparable && x, BinaryNode * & t, int rowNum)
      {
	if( t == nullptr ) {
	  vector<int> v;
	  v.push_back(rowNum);
	  t = new BinaryNode{std::move(x), nullptr, nullptr, v};
	}
	else if( x < t->element )
	  {
	    Comparisons +=1;
	    insert( std::move( x ), t->left, rowNum);
	    balance(t);
	  }
	else if( t->element < x )
	  {
	    Comparisons +=2;
	    insert( std::move( x ), t->right, rowNum);
	    balance(t);
	  }
	else
	  {
	    Comparisons += 2;
	    t->row.push_back(rowNum);  // Duplicate; do nothing
	  }
      }

      /**
       * Internal method to remove from a subtree.
       * x is the item to remove.
       * t is the node that roots the subtree.
       * Set the new root of the subtree.
       */
      void remove( const Comparable & x, BinaryNode * & t )
      {
	if( t == nullptr )
	  return;   // Item not found; do nothing
	if( x < t->element )
	  remove( x, t->left );
	else if( t->element < x )
	  remove( x, t->right );
	else if( t->left != nullptr && t->right != nullptr ) // Two children
	  {
	    t->element = findMin( t->right )->element;
	    remove( t->element, t->right );
	  }
	else
	  {
	    BinaryNode *oldNode = t;
	    t = ( t->left != nullptr ) ? t->left : t->right;
	    delete oldNode;
	  }
      }

      
      static const int ALLOWED_IMBALANCE = 1;
      // Assume t is balanced or within one of being balanced
      void balance( BinaryNode * & t )
      {
	if( t == nullptr )
	  return;

	if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
	  if( height( t->left->left ) >= height( t->left->right ) )
	    rotateWithLeftChild( t );
	  else
	    doubleWithLeftChild( t );
	else
	  if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
	    if( height( t->right->right ) >= height( t->right->left ) )
	      rotateWithRightChild( t );
	    else
	      doubleWithRightChild( t );

	t->height = max( height( t->left ), height( t->right ) ) + 1;
      }
      

      /**
       * Internal method to find the smallest item in a subtree t.
       * Return node containing the smallest item.
     */
      BinaryNode * findMin( BinaryNode *t ) const
      {
	if( t == nullptr )
	  return nullptr;
	if( t->left == nullptr )
	  return t;
	return findMin( t->left );
      }

      int findHeight( BinaryNode *t, int count ) const
      {
	if( t == nullptr )
	  return 0;
	if( t->left == nullptr )
	  return count;

	return findHeight( t->left, count+1 );
      }

      /**
       * Internal method to find the largest item in a subtree t.
       * Return node containing the largest item.
       */
      BinaryNode * findMax( BinaryNode *t ) const
      {
	if( t != nullptr )
	  while( t->right != nullptr )
	    t = t->right;
	return t;
      }

      vector<int> getLines( const Comparable & x, BinaryNode *t ) const
	{
	  if( t == nullptr )
	    return t->row;
	  else if( x < t->element )
	    return getLines( x, t->left );
	  else if( t->element < x )
	    return getLines( x, t->right );
	  else
	    return t->row;    // Match
	}

      /**
       * Internal method to test if an item is in a subtree.
       * x is item to search for.
       * t is the node that roots the subtree.
       */
      bool contains( const Comparable & x, BinaryNode *t, int & Count ) const
      {
	if( t == nullptr )
	  return false;
	else if( x < t->element )
	  {
	    Count ++;
	    return contains( x, t->left, Count );
	  }
	else if( t->element < x )
	  {
	    Count += 2;
	    return contains( x, t->right, Count );
	  }
	else
	  {
	    Count += 2;
	    return true;    // Match
	  }
      }
      /*
      int containsTwo( const Comparable & x, BinaryNode *t ) const
      {
	int KComparison = 0;
	if( t == nullptr )
	  return false;
	else if( x < t->element )
	  {
	    KComparison += 1;
	    return containsTwo( x, t->left );
	  }
	else if( t->element < x )
	  {
	    KComparison += 1;
	    return containsTwo( x, t->right );
	  }
	else
	  {
	    KComparison += 1;
	    return KComparison;    // Match
	  }
	  }
      */
      
      
      
      /****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
      *****************************************************/

      /**
       * Internal method to make subtree empty.
       */
      void makeEmpty( BinaryNode * & t )
      {
	if( t != nullptr )
	  {
	    makeEmpty( t->left );
	    makeEmpty( t->right );
	    delete t;
	  }
	t = nullptr;
      }

      /**
       * Internal method to print a subtree rooted at t in sorted order.
       */
      void printTree( BinaryNode *t, ostream & out ) const
      {
	if( t != nullptr )
	  {
	    printTree( t->left, out );

	    out << setw(20)<< left <<  t->element; //"\t"<< t->KeyComparison<<"\t"; // "\t\t\t";
	    
	    for (vector<int>::iterator it = t->row.begin(); it != t->row.end(); ++it) {
	      vector<int>::iterator dupe = it;
	      if (++dupe == t->row.end())
		out << *it << '\n';
	      else
		out << *it << ", ";
	    }



	    printTree( t->right, out );
	  }
      }

      void outputTree( BinaryNode *t, ofstream & out ) const
      {
	if( t != nullptr )
	  {
	    outputTree( t->left, out );
	    out << t->element << endl;
	    outputTree( t->right, out );
	  }
      }
      /**
       * Internal method to clone subtree.
       */
      BinaryNode * clone( BinaryNode *t, vector <int> line) const
      {
	if( t == nullptr )
	  return nullptr;
	else
	  return new BinaryNode{ t->element, clone( t->left, line ), clone( t->right, line ) };
      }
      
      //****************************************************
      // Avl manipulations
      /**
       * Return the height of node t or -1 if nullptr.
       */
      int height( BinaryNode *t ) const
      {
	return t == nullptr ? -1 : t->height;
      }

      int max( int lhs, int rhs ) const
      {
	return lhs > rhs ? lhs : rhs;
      }

      /**
       * Rotate binary tree node with left child.
       * For AVL trees, this is a single rotation for case 1.
       * Update heights, then set new root.
       */
      void rotateWithLeftChild( BinaryNode * & k2 )
      {
	BinaryNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
      }

      /**
       * Rotate binary tree node with right child.
       * For AVL trees, this is a single rotation for case 4.
       * Update heights, then set new root.
       */
      void rotateWithRightChild( BinaryNode * & k1 )
      {
	BinaryNode *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
      }

      /**
       * Double rotate binary tree node: first left child.
       * with its right child; then node k3 with new left child.
       * For AVL trees, this is a double rotation for case 2.
       * Update heights, then set new root.
       */
      void doubleWithLeftChild( BinaryNode * & k3 )
      {
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
      }

      /**
       * Double rotate binary tree node: first right child.
       * with its left child; then node k1 with new right child.
       * For AVL trees, this is a double rotation for case 3.
       * Update heights, then set new root.
       */
      void doubleWithRightChild( BinaryNode * & k1 )
      {
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
      }


      
};

#endif //LAB_6_BINARYSEARCHTREE_H
