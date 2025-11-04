const int BUFFER_SIZE = 1 << 20;
char input_buffer[BUFFER_SIZE];
int input_pos = 0, input_len = 0;

inline char nextChar() {
    if (input_pos == input_len) {
        input_pos = 0;
        input_len = fread(input_buffer, 1, BUFFER_SIZE, stdin);
        if (input_len == 0) return EOF;
    }
    return input_buffer[input_pos++];
}

inline void fast_read(int &x) {
    x = 0;
    char c;
    bool neg = false;
    do {
        c = nextChar();
    } while (c != '-' && (c < '0' || c > '9'));

    if (c == '-') {
        neg = true;
        c = nextChar();
    }

    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = nextChar();
    }

    if (neg) x = -x;
}
