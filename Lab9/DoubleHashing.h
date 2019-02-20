//#ifndef QUADRATIC_PROBING_H
//#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class DoubleHashTable
{
 public:
  int SearchCount = 0;
  int InsertCount = 0;
  
  explicit DoubleHashTable( int size = 101 ) : array( nextPrime( size ) )
    { makeEmpty( ); }

  bool contains( const HashedObj & x ) //const
  {
    return isActive( findPos( x, SearchCount ) );
  }
  int getSearchProbes()
  {
    return SearchCount;
  }
  int getInsertProbes()
  {
    return InsertCount;
  }

  void makeEmpty( )
  {
    currentSize = 0;
    for( auto & entry : array )
      entry.info = EMPTY;
  }

  bool insert( const HashedObj & x )
  {
    // Insert x as active
    float QuaSize = currentSize;
    if( QuaSize / array.size( ) > .5 )
      return false;
    int currentPos = findPos( x,InsertCount );
    if( isActive( currentPos ) )
      return false;

    if( array[ currentPos ].info != DELETED )
      ++currentSize;

    array[ currentPos ].element = x;
    array[ currentPos ].info = ACTIVE;

    return true;
  }
  /*
  bool insert( HashedObj && x )
  {
    // Insert x as active
    float QuaSize = currentSize;
    if( QuaSize / array.size( ) > .5 )
      return false;
    
    int currentPos = findPos( x );
    if( isActive( currentPos ) )
      return false;

    if( array[ currentPos ].info != DELETED )
      ++currentSize;

    array[ currentPos ] = std::move( x );
    array[ currentPos ].info = ACTIVE;

    return true;
    }*/

  bool remove( const HashedObj & x )
  {
    int currentPos = findPos( x );
    if( !isActive( currentPos ) )
      return false;

    array[ currentPos ].info = DELETED;
    return true;
  }

  enum EntryType { ACTIVE, EMPTY, DELETED };

 private:
      struct HashEntry
      {
	HashedObj element;
	EntryType info;

	HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
	: element{ e }, info{ i } { }

	HashEntry( HashedObj && e, EntryType i = EMPTY )
	: element{ std::move( e ) }, info{ i } { }
      };

      vector<HashEntry> array;
      int currentSize;

      bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

      int findPos( const HashedObj & x, int & totalprobes) const
      {
	int offset = 71 - (x % 71);
	int currentPos = myhash( x );
	totalprobes +=1;

	while( array[ currentPos ].info != EMPTY &&
	       array[ currentPos ].element != x )
	  {
	    totalprobes += 1;
	    currentPos += offset;  // Compute ith probe
	    //offset += 1;
	    if( currentPos >= array.size( ) )
	      currentPos -= array.size( );
	  }

	return currentPos;
      }

      void rehash( )
      {
	vector<HashEntry> oldArray = array;

	// Create new double-sized, empty table
	array.resize( nextPrime( 2 * oldArray.size( ) ) );
	for( auto & entry : array )
	  entry.info = EMPTY;

	// Copy table over
	currentSize = 0;
	for( auto & entry : oldArray )
	  if( entry.info == ACTIVE )
	    insert( std::move( entry.element ) );
      }

      size_t myhash( const HashedObj & x ) const
      {
	static hash<HashedObj> hf;
	return hf( x ) % array.size( );
      }
};

//#endif
