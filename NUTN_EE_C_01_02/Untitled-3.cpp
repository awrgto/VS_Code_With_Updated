#include<ctime>
#include<iostream>
#include<iomanip>
#include <windows.h>
#include<random>
using namespace std;

int main()
{
    std::random_device rd;
    std::mt19937 generator( rd() );

    std::uniform_real_distribution<float> unif(0.06, 0.09);
    float x = unif(generator);
    
    long long i = 0, l1 = 0, t = 29;
    double l = 0, k = 0, ml = l, mk = 0, ll = 16.2;
    string s[3] = {"No TAG", "-------TAG = 302---------", "-------TAG = 21---------"};
    while (l < 720)
    {
        i++;
        x = unif(generator);
        k += x;
        mk += x;
        l += x * ll;
        ml += x * ll;
        if(i < 200 && l1 == 0) cout << "[INFO] [" << setiosflags(ios::fixed) << setprecision(6) << 1561012078.139698 + k << "]: dist " << setprecision(9) << 0 << "cm, time " << setprecision(7) << mk*1000 << "ms" << endl;
        else if( l1 == 0){
            l = 0;
            ml = 0;
            i = 1;
            l1 = 1;
        }else{
            if (l < 180) ll = 18.4; 
            else if (l < 240) ll = 14.2; 
            else if (l < 300) ll = 18.4; 
            else if (l < 360) ll = 14.2; 
            else if (l < 540) ll = 18.4; 
            else if (l < 600) ll = 14.2; 
            else if (l < 660) ll = 18.4; 
            else if (l < 720) ll = 14.2;
            else ll = 18.4;
            
            if(( l > 249 && l1 == 1) || ( l > 275 && l1 == 2) || (l > 304 && l1 == 3)) {
                ml = 0;
                mk = 0;
                l1++;
                cout << s[1] << endl << "[INFO] [" << setiosflags(ios::fixed) << setprecision(6) << 1561012078.139698 + k - 0.0000022 << "]: start !" << endl;
            }
            if(( l > 606 && l1 == 4) || ( l > 646 && l1 == 5)) {
                l1++;
                cout << s[2] << endl << "[INFO] [" << setiosflags(ios::fixed) << setprecision(6) << 1561012078.139698 + k - 0.0000022 << "]: end" << endl;
                cout << "\n\ntotal distance " << ml << "cm, take " << mk << "ms\n\n" << endl;
            }
            cout << "[INFO] [" << setiosflags(ios::fixed) << setprecision(6) << 1561012078.139698 + k << "]: dist " << setprecision(9) << ml << "cm, time " << setprecision(7) << mk*1000 << "ms" << endl;
            if(!(i%t)){
                if(l < 230 || (l > 325  && l < 590 ) || l > 670 ) cout << s[0] << endl;
                t = rand() % 13 + 27;
                i = 0;
            }
        }

        Sleep(x * 1000);
    }
}