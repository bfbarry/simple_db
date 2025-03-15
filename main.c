/* hashcode
backing aray
compression function (convert hash to index)
table size (power of 2 or pirme)
load factor size/cap
 
put and collision handling
closed addressing (stored k,v at same index)
    - external chaining
open addressing: use different indexing
     - linear probing (time_probed + origIndex) % backkingArray.length
 
removal w/ linear probing:
    - DEL flag
 
put (have to check if it's already in the table):
    - if there is DEL, save it
    - if you later encounter null, you know it's not in the table
*/
 
unsigned long hash_djb2(unsigned char* str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; // same as hash * 33 + c because bitshifting is faster
    }
    return hash;
}
 
typedef struct HashMap {
    int size;
    int cap;
    float loadFactor;
    int* backingArray;
} HashMap;


HashMap* init(int cap, float loadFactor) {
    HashMap* map = malloc(sizeof(HashMap));
    map->size = 0;
    map->cap = cap;
    map->loadFactor = loadFactor;

    return map;
}

int put(HashMap* this, unsigned char* k, int v) {

    int ix = hash_djb2(k) % this->cap;
    
}

int get(int key) {}

int main(int argc, char* argv[]) {
    HashMap* m = init(17, 0.5);
    m.put()
}