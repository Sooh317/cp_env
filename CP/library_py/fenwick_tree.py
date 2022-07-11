class BIT:
    def __init__(self, N):
        self.n = (N + 1)
        self.d = [0] * (N + 1)
        self.cnt = 1
        while self.cnt < self.n: self.cnt <<= 1
    
    def add(self, p, x = 1):
        assert 0 <= p < self.n
        p += 1
        while p < self.n:
            self.d[p] += x
            p += p & (-p)

    def _sum(self, r):
        res = 0
        while r:
            res += self.d[r]
            r -= r & (-r)
        return res

    def sum(self, l, r):
        assert 0 <= l and l <= r and r <= self.n
        return self._sum(r) - self._sum(l)
    
    def lower_bound(self, val):
        if val <= 0 : return 0
        pos, k = 0, self.cnt
        while k:
            npos = pos + k
            if npos < self.n and self.d[npos] < val:
                val -= self.d[npos]
                pos = npos
            k >>= 1
        return pos