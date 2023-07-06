#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem             * m_Next;
  char                     * m_Name;
  char                       m_Secret[24];
} TITEM;

TITEM * newItem ( const char * name, TITEM * next )
{
  TITEM * node = (TITEM *)malloc(sizeof(* node));

  node->m_Next = next;

  char * nameArr = (char *)malloc( (strlen(name)+1) *  sizeof(* nameArr));
  node->m_Name = nameArr;
  memcpy ( node->m_Name, name, strlen(name)+1);

  for ( int i = 0; i < 24; i ++ )
    node->m_Secret[i] = '\0';
  
  return node;
}


// counts the smallest number of two
size_t min (size_t p, size_t p2){
  if (p < p2){
    return p;
  }
  if (p > p2){
    return p2;
  }
  if (p == p2){
    return p;
  }

  return p;
}

// swaps two nodes according to the ascending
int swapNodes ( TITEM **i1, TITEM **i2 , TITEM **head , int asc){
  TITEM * tmp1 = (*head); // pointer to the previous element of i1
  while ( 1 ){
    if ( (*i1) == (*head) ){
      tmp1 = NULL;
      break;
    }
    if ( tmp1->m_Next != (*i1)) {
      tmp1 = tmp1 ->m_Next;
    }
    else break;
  }

  TITEM * tmp2 = (*i2)->m_Next; // pointer to the next element of i2

  size_t lenI1 = strlen((*i1)->m_Name);
  size_t lenI2 = strlen((*i2)->m_Name);

  size_t cnt = 0; //finding characters in the name, which is not similar;
  while ( (*i1)->m_Name[ cnt ] == (*i2)->m_Name[ cnt ] && cnt < min(lenI1, lenI2)){
    cnt += 1;
  }

  if ( (*i1)->m_Name[ cnt ] > (*i2)->m_Name[ cnt ] && asc == 1 ) {

  if ( tmp1 != NULL ){
    tmp1->m_Next = (*i2);
  }
  else (*head)=(*i2);

  (*i2)->m_Next = (*i1);
  (*i1)->m_Next = tmp2;
  
  return 1;
  }

  if ( (*i1)->m_Name[ cnt ] < (*i2)->m_Name[ cnt ] && asc == 0 ){

  if ( tmp1 != NULL ){
    tmp1->m_Next = (*i2);
  }
  else (*head)=(*i2);
  
  (*i2)->m_Next = (*i1);
  (*i1)->m_Next = tmp2;
  
  return 1;
  }

  return 0;
}

TITEM * sortList ( TITEM * l, int ascending ) {
  // if ll is empty
  if ( l == NULL ){
    return NULL;
  }

  // if in ll is only one element
  if ( l->m_Next == NULL){
    return l;
  }

  int swapped;// checks if array is sorted
  TITEM * i1 = l;
  TITEM * i2 = l->m_Next;

  do {
    swapped = 0;

    while ( 1 ){

      //swap nodes
      if ( swapNodes( &i1, &i2, &l , ascending) )
        swapped = 1;

      //move pointers to another pair
      if ( i2->m_Next != NULL ){
        i1 = i2;
        i2 = i2->m_Next;
      } else {
        i1 = l;
        i2 = l->m_Next;
        break;
      } 
    }
    
  } while ( swapped );
  return l;
}

void freeList ( TITEM * src )
{
  if ( src == NULL ){
    return;
  }
  TITEM * tmp = NULL;
  while ( src != NULL ){
    tmp = src->m_Next;
    free(src->m_Name);
    free( src );
    src = tmp;
  }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TITEM * l;
  char tmp[50];

  assert ( sizeof ( TITEM ) == sizeof ( TITEM * ) + sizeof ( char * ) + 24 * sizeof ( char ) );
  l = NULL;
  l = newItem ( "PA1", l );
  l = newItem ( "PA2", l );
  l = newItem ( "UOS", l );
  l = newItem ( "LIN", l );
  l = newItem ( "AG1", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 1 );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = newItem ( "programming and algorithmic I", l );
  l = newItem ( "AAG", l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 0 );
  assert ( l
           && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( l );
  l = NULL;
  strncpy ( tmp, "PA1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "PA2", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "UOS", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "LIN", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 1 );
  assert ( l
           && ! strcmp ( l -> m_Name, "AG1" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  strncpy ( tmp, "programming and algorithmic I", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  strncpy ( tmp, "AAG", sizeof ( tmp ) - 1 );
  tmp[sizeof ( tmp ) - 1 ] = '\0';
  l = newItem ( tmp, l );
  assert ( l
           && ! strcmp ( l -> m_Name, "AAG" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  l = sortList ( l, 0 );
  assert ( l
           && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
  assert ( l -> m_Next
           && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
  assert ( l -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
  assert ( l -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

  freeList ( l );
  return EXIT_SUCCESS;
}
