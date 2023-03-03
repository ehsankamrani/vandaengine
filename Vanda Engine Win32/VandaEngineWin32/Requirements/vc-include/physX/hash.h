//
//     Hash
//     By S Melax
//
// A simple associative array container class.
// 
// Using the string class for keys might cause a bit of extry copying.  
// I realize the [] operator takes its argument by value instead of by reference,
// which causes some extra construction and stuff.  The reason was so I could
// use my string class as the key and then access the hash using things 
// that aren't strings, such as char*, but can be constructed into strings.  
// The thing of importance is convienence and high-level algorithm 
// efficiency (lowering the "order" of the algorithm).  
// For example, its better to use a Hash then to 
// continually be searching for specific elements in a large unsorted array.
// Even though things run in O(1), there is the cost of calculating the
// index from the key when making an access, key comparisons, and stuff like that.
// Common sense should tell you that such calls dont belong in the 
// innermost loop of some batch processing or a math intensive calculation.
//
// The reason for initializing the Hash with -1 in the constructor, is so that
// we can add elements to a non constructed global hash, and delete elements from such a 
// deconstructed hash.  This is because the order that globals are constructed isn't known
// across different modules.
//

#ifndef SM_HASH_H
#define SM_HASH_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template<class K>
int hashpos(K &k,int number_of_slots)
{
	int sum=0;
	for(int i=0;i<sizeof(K);i++){
		sum+= ((unsigned char *)&k)[i];
	}
	return sum%number_of_slots;  
}

template <class K,class T>
class HashEntry
{
public: 
	int used;
	K key;
	T value;
	HashEntry(){used=0;}
	void *operator new[](size_t in_size){
		void* a = malloc(in_size);
		memset(a,0,in_size);
		return a;
	}
};

template <class K,class T>
class Hash 
{
 public:
	HashEntry<K,T>* slots;
	int slots_count; 
	int keys_count;
	int collision_count;
	void Rehash(int newsize)
	{
		int i;
		Hash tmp(newsize); // odd is good, prime would be better
		for(i=0;i<slots_count;i++)
		{
			if(slots[i].used) { tmp[slots[i].key] = slots[i].value;}
		}
		delete []slots;
		slots = tmp.slots;
		slots_count = tmp.slots_count;
		assert(tmp.keys_count == keys_count);
		collision_count = tmp.collision_count;
		tmp.slots=NULL;  // so it wont delete the data (slots) when tmp's destructor is called
	}
 	const T &operator()(K key) const
	{
		static const T dummy = 0;
		if(!slots_count) return dummy;
		int k = hashpos(key,slots_count);
		while(slots[k].used && slots[k].key!=key){k++;k%=slots_count;}
		if(!slots[k].used) 
		{
			return dummy; // untouchable
		}
		return slots[k].value;
	}
 	T &operator[](K key)
	{
		if(!slots_count) Rehash(31);
		int k = hashpos(key,slots_count);
		while(slots[k].used && slots[k].key!=key){k++;k%=slots_count;}
		if(!slots[k].used) 
		{
			slots[k].used=1;
			slots[k].key=key;
			int p = hashpos(key,slots_count);
			collision_count += (k>=p)?k-p:k+slots_count-p;  // simply for performance monitoring
			keys_count++;
			if(keys_count > slots_count/2) { 
				Rehash(2*slots_count-1);
				k = hashpos(key,slots_count);
				while(slots[k].used && slots[k].key!=key){k++;k%=slots_count;}
			}
			
		}
		return slots[k].value;
	}
	int Exists(K key)
	{
		if(!slots_count) return 0;
		int k = hashpos(key,slots_count);
		while(slots[k].used && slots[k].key!=key){k++;k%=slots_count;}
		return(slots[k].used); 
	}
	void Delete(K key)
	{
		if(!slots_count) return;
		int k = hashpos(key,slots_count);
		while(slots[k].used && slots[k].key!=key){k++;k%=slots_count;}
		if(!slots[k].used) return;
		slots[k].used =0;
		keys_count--;
		Rehash(slots_count);
	}
	Hash(int _slots_count=31){if(_slots_count<0)return;keys_count=0;slots_count=_slots_count;slots=(slots_count)?new HashEntry<K,T>[slots_count]:NULL;collision_count=0;}
	~Hash(){delete []slots;slots_count=0;}
};


#endif
