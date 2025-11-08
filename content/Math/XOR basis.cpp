void insert(int mask) {
    for (int i = 1; i <= now; i++) {
        mask = min(mask, mask ^ basis[i]);
    }
    if (mask != 0) basis[++now] = mask;
}

// XOR basis: moi mask trong XOR basis la duy nhat, ko the bieu dien bang XOR cua nhung so con lai
// used for: 
/*
find max XOR 
int get_max_xor(int x = 0) {
    for (int b : basis)
        x = max(x, x ^ b);
    return x;
}

find min XOR
bool can_make(int x) {
    for (int b : basis)
        x = min(x, x ^ b);
    return x == 0;
}

count how many XOR value can make
have x numbers in basis -> 2^k value can use
*/