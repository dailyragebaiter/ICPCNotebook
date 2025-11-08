vector<int> prefix_function(string s) {
    int n = (int)s.length();              // do dai chuoi s
    vector<int> pi(n);                    // mang pi[i]: do dai tien to dai nhat cung la hau to cua s[0..i]
    for (int i = 1; i < n; i++) {         // duyet tung ky tu tu vi tri 1 -> n-1
        int j = pi[i - 1];                // j: do dai tien to trung khop truoc do
        while (j > 0 && s[i] != s[j])     // neu ky tu tiep theo khong khop
            j = pi[j - 1];                // rut ngan do dai tien to ve gia tri truoc do (theo border truoc)
        if (s[i] == s[j])                 // neu ky tu hien tai trung ky tu tiep theo cua tien to
            j++;                          // mo rong do dai tien to trung khop them 1
        pi[i] = j;                        // luu lai do dai tien to hau to khop dai nhat tai vi tri i
    }
    return pi;                            // tra ve mang pi (prefix-function)
}

int main() {
    string pattern = "aba";
    string text = "abacaba";
    string s = pattern + "#" + text;
    vector<int> pi = prefix_function(s);

    int m = pattern.size();
    for (int i = 0; i < (int)s.size(); i++) {
        if (pi[i] == m) {
            cout << "Pattern found at position " << i - 2*m << "\n";
            // i - 2*m = vị trí bắt đầu của pattern trong text
        }
    }
}
/*

Ung dung thuc te cua ham prefix_function

Ung dung: Tim chuoi con
Muc tieu: Tim vi tri xuat hien cua pattern trong text
Mo ta: Su dung trong thuat toan KMP search

Ung dung: Tim do lap cua chuoi
Muc tieu: Tim xem chuoi co cau truc lap nao khong
Mo ta: Dung pi de phat hien pattern lap lai, vi du "abcabcabc"

Ung dung: Chuoi con trung dau cuoi
Muc tieu: Tim tien to cung la hau to dai nhat
Mo ta: Dung nhieu trong bai toan xu ly chuoi vong, palindrome

Ung dung: Tien xu ly trong bai toan chuoi
Muc tieu: Xac dinh bien (border) hoac phan lap
Mo ta: Dung trong suffix automation, hashing, Z-function, vv
*/