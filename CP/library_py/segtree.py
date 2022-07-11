class segtree:
    def __init__(self, op, e, n, v=None):
        self.n = n
        self.op = op
        self.e = e
        self.h = (n - 1).bit_length()
        self.num = 1 << self.h
        self.d = [self.e()] * (self.num << 1)
        if v != None : 
            for i in range(self.n):
                self.d[i + self.num] = v[i]
            for i in range(self.num - 1, 0, -1):
                self.d[i] = self.op(self.d[i << 1], self.d[i << 1 | 1])
    
    def set(self, p, x):
        assert 0 <= p < self.n
        p += self.num
        self.d[p] = x
        while p:
            self.d[p >> 1] = self.op(self.d[p], self.d[p ^ 1])
            p >>= 1

    def prod(self, l, r):
        assert 0 <= l <= r <= self.n
        sl = self.e()
        sr = self.e()
        l += self.num
        r += self.num
        while l < r : 
            if l & 1:
                sl = self.op(sl, self.d[l])
                l += 1
            if r & 1:
                r -= 1
                sr = self.op(self.d[r], sr)
            l >>= 1
            r >>= 1
        return self.op(sl, sr)
    
    def all_prod(self):
        return self.d[1]
    
    def get(self, p):
        assert 0 <= p < self.n
        return self.d[self.num + p]

    def max_right(self, l, f):
        assert 0 <= l <= self.n
        assert f(self.e())
        if l == self.n: return self.n
        l += self.num
        sm = self.e()
        while True:
            while l % 2 == 0: l >>= 1
            if not f(self.op(sm, self.d[l])):
                while l < self.num:
                    l <<= 1
                    if f(self.op(sm, self.d[l])):
                        sm = self.op(sm, self.d[l])
                        l += 1
                return l - self.num
            sm = self.op(sm, self.d[l])
            l += 1
            if l & -l == l: break
        return self.n
    
    def min_left(self, r, f):
        assert 0 <= r <= self.n
        assert f(self.e())
        if r == 0: return 0
        r += self.num
        sm = self.e()
        while True:
            r -= 1
            while r > 1 and r % 2: r >>= 1 
            if not f(self.op(self.d[r], sm)):
                while r < self.num:
                    r = 2 * r + 1 
                    if f(self.op(self.d[r], sm)):
                        sm = self.op(self.d[r], sm)
                        r -= 1
                return r + 1 - self.num
            sm = self.op(self.d[r], sm)
            if r & -r == r: break
        return 0