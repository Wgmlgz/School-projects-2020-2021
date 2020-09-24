#include <iostream>
#include <cmath>

struct XYZ {
    int x, y, z;
};
struct ABCD {
    int a, b, c, d;
};

bool cmp_XYZ(XYZ a, XYZ b) {
    bool f = (a.x == b.x && a.y == b.y && a.z == b.z);

    return f;
}
XYZ RNG (XYZ x, ABCD a) {
    int res = (a.a*x.x + a.b*x.y + a.c*x.z) % a.d;

    x.z = x.y;
    x.y = x.x;
    x.x = res;

    return x;
}

int main () {


    // result values
    int p = 1, n = 0;
    double z = 0;


    // input
    XYZ x;
    ABCD a;
    std::cin >> a.a >> a.b >> a.c >> a.d >> x.z >> x.y >> x.x;


    // p find
    XYZ frog = x, toad = x;
    for (int i = 0; !cmp_XYZ(toad, frog) || i == 0; ++i) {
        frog = RNG(frog, a);
        frog = RNG(frog, a);
        toad = RNG(toad, a);
    }

    frog = RNG(frog, a);
    for (;!cmp_XYZ(toad, frog); frog = RNG(frog, a), ++p) ;
    

    // n find
    frog = x, toad = x;
    for (int i = 0; i < p; i++, frog = RNG(frog, a)) ;
    
    for (int i = 0; !cmp_XYZ(toad, frog); ++i, ++n) {
                frog = RNG(frog, a);
        toad = RNG(toad, a);
    }
    
    
    // z find
    int range_vals[20];
    XYZ tmp_xyz = x;

    for (int i = 0; i < 20; i++) {
        range_vals[i] = 0;
    }

    for (int i = 0; i < 400; i++) {
        tmp_xyz = RNG(tmp_xyz, a);

        std::cout << tmp_xyz.z << std::endl;

        int tmp = tmp_xyz.x;
        double tmpf = static_cast<double>(tmp) / a.d; 
        ++range_vals[static_cast<int>(tmpf * 20)];
    }

    for (int i = 0; i < 20; i++) {
        z += pow(static_cast<double>(range_vals[i] - 20), 2) / 400;
    }
    

    // output
    std::cout << p << " " << n << " " << z;
}