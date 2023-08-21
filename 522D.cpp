#include <bits/stdc++.h>
using namespace std;

int n, q;
const int MAXN = 5e5+1;
int a[MAXN], pre[MAXN], nxt[MAXN];
map<int, int> last;

int ans[710][710];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);
    int i, j, k;
    cin>>n>>q;
    for(i=1;i<=n;i++) cin>>a[i];

    for(i=1;i<=n;i++) {
        if(last.find(a[i]) != last.end())
            pre[i] = last[a[i]];
        else pre[i] = 0;
        last[a[i]] = i;
    }

    last.clear();
    for(i=n;i>=1;i--) {
        if(last.find(a[i]) != last.end())
            nxt[i] = last[a[i]];
        else  nxt[i] = n+1;
        last[a[i]] = i;
    }

    int sqr = sqrt(n);

    for(i=1;i<=sqr+(bool)(sqr*sqr < n);i++) {
        int start = sqr*(i-1) + 1;
        int minn = INT_MAX;
        for(j=start;j<=n;j++) {
            if(pre[j] >= start) minn = min(minn, j-pre[j]);
            ans[i][j/sqr+(bool)(j%sqr)] = minn;
        }
    }

   /* for(i=1;i<=sqr+1;i++) {
        for(j=i;j<=sqr+1;j++)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    } */

    while(q-- ) {
        int l, r;
        cin>>l>>r;
        int bl1 = l/sqr + (bool)(l%sqr) + 1;
        int bl2 = r/sqr + (bool)(r%sqr) - 1;

        if(bl2 < bl1) {
            int minn = INT_MAX;
            for(i=l;i<=r;i++) {
                if(pre[i] >= l) minn = min(minn, i-pre[i]);
            }
            if(minn == INT_MAX) minn = -1;
            cout<<minn<<'\n';
            continue;
        }

        int minn = ans[bl1][bl2];
        for(i=bl2*sqr+1;i<=r;i++) {
            if(pre[i] >= l) minn = min(minn, i-pre[i]);
        }
        for(i=(bl1-1)*sqr;i>=l;i--) {
            if(nxt[i] <= r) minn = min(minn, nxt[i]-i);
        }
        if(minn == INT_MAX) minn = -1;
        cout<<minn<<'\n';
    }


    return 0;
}
