#include <iostream>
using namespace std;

int main( ) {
    double r   = 0.001;
    long int n = 50, p = 100000;
    //cin >> r >> n >> p;
    double sum = 0, sum2 = 0;
    while (n--) {
        sum += p;
        sum = sum * (1.0l + r);
        sum2 += p;
        sum2 = sum2 + sum2 * r;
        if (!(sum == sum2))
            cout << sum << "\t" << sum2 << endl;
        else
            cout << "same" << sum2 << endl;
    }
    cout << sum << endl
         << sum2 << endl;
    return 0;
}