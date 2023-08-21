#include <bits/stdc++.h>
using namespace std;

int n, q, k;
const int MAXN = 100001;
int a[MAXN];
map<int, int> br[320];
int prec[320][320];

int main()
{
    int i, j;
    cin>>n>>q>>k;
    for(i=1;i<=n;i++) cin>>a[i];

    int sqr = sqrt(n);

    int bl = 1;
    for(i=1;i<=n;i++) {
        br[bl][a[i]]++;
        if(i%sqr == 0) {
            br[bl+1] = br[bl];
            bl++;
        }
    }

    for(i=1;i<=sqr+(bool)(sqr*sqr < n);i++) {
        int start = sqr*(i-1) + 1;
        map<int, int> tbr;
        int ans = 0, bl = i;
        for(j=start;j<=n;j++) {
            ans+= tbr[a[i]^k] + br[bl-1][a[i]^k] - br[i-1][a[i]^k];
            tbr[a[i]]++;
            if(j%sqr == 0) {
                prec[i][bl] = ans;
                bl++;
                tbr.clear();
            }
        }

    }

    while(q-- ){
        int l, r;
        cin>>l>>r;
        int bl1 = l/sqr + (bool)(l%sqr) + 1;
        int bl2 = r/sqr + (bool)(r%sqr) - 1;
        map<int, int> tbr;
        int ans = 0;
        if(bl2 < bl1) {
            for(i=l;i<=r;i++) {
                ans+= tbr[a[i]^k];
                tbr[a[i]]++;
            }
            cout<<ans<<endl;
            continue;
        }

        ans = prec[bl1][bl2];

        for(i=bl2*sqr+1;i<=r;i++) {
            ans+= tbr[a[i]^k] + br[bl2][a[i]^k] - br[bl1-1][a[i]^k];
            tbr[a[i]]++;
        }
        for(i=(bl1-1)*sqr;i>=l;i--) {
            ans += tbr[a[i]^k] + br[bl2][a[i]^k] - br[bl1-1][a[i]^k];
            tbr[a[i]]++;
        }

        cout<<ans<<endl;
    }

    return 0;
}
