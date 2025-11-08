
mt19937_64 rd (chrono :: steady_clock :: now ().time_since_epoch ().count ());
int Rand (int l, int r) {return uniform_int_distribution <int> (l, r) (rd);}
using namespace std::chrono;
steady_clock::time_point start_time;
const long long TIME_LIMIT_MS = 950;
unsigned long long check_counter = 0;
inline void maybe_timeout_check(){
    if((++check_counter & 1023) == 0){
        auto now = steady_clock::now();
        auto ms = duration_cast<milliseconds>(now - start_time).count();
        if(ms >= TIME_LIMIT_MS){
            //cout << max1 << "\n";
            cout.flush();
            exit(0);
        }
    }
}

// __start_time = steady_clock::now();
// __maybe_timeout_check();
