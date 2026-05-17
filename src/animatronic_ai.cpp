//
// Created by matei on 5/17/2026.
//

#include "../include/animatronic_ai.h"
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
#include "room.h"

const int dx[]={1,-1,0,0,1,-1,1,-1};
const int dy[]={0,0,1,-1,1,1,-1,-1};

struct nodd {
    int x,y;
    float f;
    nodd() : x(0), y(0), f(0.f) {}
    nodd(int x,int y,float f) : x(x), y(y), f(f) {}
    bool operator>(const nodd& other) const {
        return f>other.f;
    }
};

int animatronic_ai::get_index(int x, int y, int w) {
    return x+y*w;
}

bool animatronic_ai::in(int x, int y, int w, int h) {
    return x>=0 && y>=0 && x<w && y<h;
}

std::vector<sf::Vector2i> animatronic_ai::find(const room &r, sf::Vector2i st, sf::Vector2i target) {
    if (st==target) {
        return {};
    }

    sf::Vector2i sz=r.get_grid_size();
    int w=sz.x, h=sz.y;
    if (w<=0 || h<=0) {
        return {};
    }

    if (!in(st.x, st.y, w, h) || !in(target.x, target.y, w, h)) {
        return {};
    }
    std::vector<float> dist(w*h,2e9f);
    std::vector<int> par(w*h,-1);
    std::vector<bool> viz(w*h,false);
    std::priority_queue<nodd,std::vector<nodd>,std::greater<nodd> > pq;
    int ss=get_index(st.x,st.y,w);

    auto heuristic = [&](int x, int y) -> float {
        float dxx = std::abs(x - target.x);
        float dyy = std::abs(y - target.y);
        return std::max(dxx, dyy) + 0.414f * std::min(dxx, dyy);
    };

    dist[ss]=0;
    int sx=st.x;
    int sy=st.y;
    pq.push({sx,sy,heuristic(sx,sy)});
    while (!pq.empty()) {
        nodd nod=pq.top();
        pq.pop();

        int ind=get_index(nod.x,nod.y,w);
        if (viz[ind]) {
            continue;
        }

        viz[ind]=true;

        if (nod.x==target.x && nod.y==target.y) {
            std::vector<sf::Vector2i> ans;
            int curr=ind;
            while (curr!=-1) {
                ans.push_back({curr%w,curr/w});
                curr=par[curr];
            }
            if (!ans.empty()) {
                ans.pop_back();
            }
            std::reverse(ans.begin(),ans.end());
            return ans;
        }

        for (int d=0; d<8; d++) {
            int nx=nod.x+dx[d];
            int ny=nod.y+dy[d];
            if (!in(nx,ny,w,h) || r.is_solid(nx,ny) || (d>=4 && (r.is_solid(nx,nod.y) || r.is_solid(nod.x,ny)))) {
                continue;
            }

            int ni=get_index(nx,ny,w);
            if (viz[ni])
                continue;
            float cost=(d<4) ? 1.f : 1.41f;
            if (dist[ni]>dist[ind]+cost) {
                dist[ni]=dist[ind]+cost;
                par[ni]=ind;
                pq.push({nx,ny,dist[ni]+heuristic(nx,ny)});
            }
        }
    }

    return {};
}

