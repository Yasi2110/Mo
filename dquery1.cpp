#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30001;
const int MAXQ = 200001;
int n, q;
int a[MAXN];
struct Query{
    int l, r, ans, pos;
};
Query t[MAXQ];
int sqr;

bool sortfunc(Query t1, Query t2) {
    if(t1.l / sqr == t2.l / sqr) return t1.r > t2.r;
    else return t1.l < t2.l;
}

int br[1000001];

bool sortfunc2(Query t1, Query t2) {
    return t1.pos < t2.pos;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);
    int i, j;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];

    cin>>q;
    for(i=1;i<=q;i++)
        cin>>t[i].l>>t[i].r, t[i].pos = i;

    sqr = sqrt(n);
    sort(t+1, t+q+1, sortfunc);

    int tans = 0;
    for(i=t[1].l;i<=t[1].r;i++) {
        if(br[a[i]] == 0) tans++;
        br[a[i]]++;
    }
    t[1].ans = tans;

    for(i=2;i<=q;i++) {
        if(t[i].l < t[i-1].l) {
            for(j=t[i].l;j<t[i-1].l;j++) {
                if(br[a[j]] == 0) tans++;
                br[a[j]]++;
            }
        }
        else if(t[i].l > t[i-1].l) {
            for(j=t[i-1].l;j<t[i].l;j++) {
                br[a[j]]--;
                if(br[a[j]] == 0) tans--;
            }
        }

        if(t[i].r < t[i-1].r) {
            for(j=t[i].r+1;j<=t[i-1].r;j++) {
                br[a[j]]--;
                if(br[a[j]] == 0) tans--;
            }
        }
        else if(t[i].r > t[i-1].r) {
            for(j=t[i-1].r+1;j<=t[i].r;j++) {
                if(br[a[j]] == 0) tans++;
                br[a[j]]++;
            }
        }

        t[i].ans = tans;
    }

    sort(t+1, t+q+1, sortfunc2);

    for(i=1;i<=q;i++) cout<<t[i].ans<<'\n';

    return 0;
}
