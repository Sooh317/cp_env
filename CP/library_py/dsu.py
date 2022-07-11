class dsu:
    def __init__(self, N):
        self.n = N
        self.par = [-1 for i in range(N)]

    def leader(self, a):
        assert 0<=a<self.n, "0<=a<n,a={0},n={1}".format(a,self.n)
        if self.par[a] < 0 : return a
        self.par[a] = self.leader(self.par[a])
        return self.par[a]

    def size(self, a):
        assert 0<=a<self.n, "0<=a<n,a={0},n={1}".format(a,self.n)
        return -self.par[self.leader(a)]

    def merge(self, a, b):
        assert 0<=a<self.n, "0<=a<n,a={0},n={1}".format(a,self.n)
        assert 0<=b<self.n, "0<=b<n,b={0},n={1}".format(b,self.n)
        x = self.leader(a)
        y = self.leader(b)
        if x == y : return x
        if self.par[x] < self.par[y] : x, y = y, x
        self.par[y] += self.par[x]
        self.par[x] = y
        return y
    
    def same(self, a, b):  
        assert 0<=a<self.n, "0<=a<n,a={0},n={1}".format(a,self.n)
        assert 0<=b<self.n, "0<=b<n,b={0},n={1}".format(b,self.n)
        return self.leader(a) == self.leader(b)
    
    def groups(self):
        who_is_leader = [None] * self.n
        tmp = [[] for i in range(self.n)]
        res = []
        for i in range(self.n):
            tmp[self.leader(i)].append(i)
        for i in range(self.n):
            if len(tmp[i]) == 0 : continue
            res.append(tmp[i])
        return res