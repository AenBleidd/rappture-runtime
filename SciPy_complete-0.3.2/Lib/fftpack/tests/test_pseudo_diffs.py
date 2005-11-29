#!/usr/bin/env python
# Created by Pearu Peterson, September 2002
""" Test functions for fftpack.pseudo_diffs module
"""
__usage__ = """
Build fftpack:
  python setup_fftpack.py build
Run tests if scipy is installed:
  python -c 'import scipy;scipy.fftpack.test(<level>)'
Run tests if fftpack is not installed:
  python tests/test_pseudo_diffs.py [<level>]
"""
import sys
from scipy_test.testing import *
set_package_path()
from fftpack import diff,fft,ifft,tilbert,itilbert,hilbert,ihilbert,rfft
from fftpack import shift
from fftpack import fftfreq
del sys.path[0]

import Numeric
from Numeric import arange, add, array, sin, cos, pi,exp,tanh,sum

def random(size):
    return rand(*size)

import unittest

def direct_diff(x,k=1,period=None):
    fx = fft(x)
    n = len (fx)
    if period is None:
        period = 2*pi
    w = fftfreq(n)*2j*pi/period*n
    if k<0:
        w = 1 / w**k
        w[0] = 0.0
    else:
        w = w**k
    if n>2000:
        w[250:n-250] = 0.0
    return ifft(w*fx).real

def direct_tilbert(x,h=1,period=None):
    fx = fft(x)
    n = len (fx)
    if period is None:
        period = 2*pi
    w = fftfreq(n)*h*2*pi/period*n
    w[0] = 1
    w = -1j/tanh(w)
    w[0] = 0j
    return ifft(w*fx)

def direct_itilbert(x,h=1,period=None):
    fx = fft(x)
    n = len (fx)
    if period is None:
        period = 2*pi
    w = fftfreq(n)*h*2*pi/period*n
    w = 1j*tanh(w)
    return ifft(w*fx)

def direct_hilbert(x):
    fx = fft(x)
    n = len (fx)
    w = fftfreq(n)*n
    w = -1j*Numeric.sign(w)
    return ifft(w*fx)

def direct_ihilbert(x):
    return -direct_hilbert(x)

def direct_shift(x,a,period=None):
    n = len(x)
    if period is None:
        k = fftfreq(n)*1j*n
    else:
        k = fftfreq(n)*2j*pi/period*n
    return ifft(fft(x)*Numeric.exp(k*a)).real


class test_diff(ScipyTestCase):

    def check_definition(self):
        for n in [16,17,64,127,32]:
            x = arange(n)*2*pi/n
            assert_array_almost_equal(diff(sin(x)),direct_diff(sin(x)))
            assert_array_almost_equal(diff(sin(x),2),direct_diff(sin(x),2))
            assert_array_almost_equal(diff(sin(x),3),direct_diff(sin(x),3))
            assert_array_almost_equal(diff(sin(x),4),direct_diff(sin(x),4))
            assert_array_almost_equal(diff(sin(x),5),direct_diff(sin(x),5))
            assert_array_almost_equal(diff(sin(2*x),3),direct_diff(sin(2*x),3))
            assert_array_almost_equal(diff(sin(2*x),4),direct_diff(sin(2*x),4))
            assert_array_almost_equal(diff(cos(x)),direct_diff(cos(x)))
            assert_array_almost_equal(diff(cos(x),2),direct_diff(cos(x),2))
            assert_array_almost_equal(diff(cos(x),3),direct_diff(cos(x),3))
            assert_array_almost_equal(diff(cos(x),4),direct_diff(cos(x),4))
            assert_array_almost_equal(diff(cos(2*x)),direct_diff(cos(2*x)))
            assert_array_almost_equal(diff(sin(x*n/8)),direct_diff(sin(x*n/8)))
            assert_array_almost_equal(diff(cos(x*n/8)),direct_diff(cos(x*n/8)))
            for k in range(5):
                assert_array_almost_equal(diff(sin(4*x),k),direct_diff(sin(4*x),k))
                assert_array_almost_equal(diff(cos(4*x),k),direct_diff(cos(4*x),k))

    def check_period(self):
        for n in [17,64]:
            x = arange(n)/float(n)
            assert_array_almost_equal(diff(sin(2*pi*x),period=1),
                                      2*pi*cos(2*pi*x))
            assert_array_almost_equal(diff(sin(2*pi*x),3,period=1),
                                      -(2*pi)**3*cos(2*pi*x))

    def check_sin(self):
        for n in [32,64,77]:
            x = arange(n)*2*pi/n
            assert_array_almost_equal(diff(sin(x)),cos(x))
            assert_array_almost_equal(diff(cos(x)),-sin(x))
            assert_array_almost_equal(diff(sin(x),2),-sin(x))
            assert_array_almost_equal(diff(sin(x),4),sin(x))
            assert_array_almost_equal(diff(sin(4*x)),4*cos(4*x))
            assert_array_almost_equal(diff(sin(sin(x))),cos(x)*cos(sin(x)))

    def check_expr(self):
        for n in [64,77,100,128,256,512,1024,2048,4096,8192][:5]:
            x = arange(n)*2*pi/n
            f=sin(x)*cos(4*x)+exp(sin(3*x))
            df=cos(x)*cos(4*x)-4*sin(x)*sin(4*x)+3*cos(3*x)*exp(sin(3*x))
            ddf=-17*sin(x)*cos(4*x)-8*cos(x)*sin(4*x)\
                 -9*sin(3*x)*exp(sin(3*x))+9*cos(3*x)**2*exp(sin(3*x))
            d1 = diff(f)
            assert_array_almost_equal(d1,df)
            assert_array_almost_equal(diff(df),ddf)
            assert_array_almost_equal(diff(f,2),ddf)
            assert_array_almost_equal(diff(ddf,-1),df)
            #print max(abs(d1-df))

    def check_expr_large(self):
        for n in [2048,4096]:
            x = arange(n)*2*pi/n
            f=sin(x)*cos(4*x)+exp(sin(3*x))
            df=cos(x)*cos(4*x)-4*sin(x)*sin(4*x)+3*cos(3*x)*exp(sin(3*x))
            ddf=-17*sin(x)*cos(4*x)-8*cos(x)*sin(4*x)\
                 -9*sin(3*x)*exp(sin(3*x))+9*cos(3*x)**2*exp(sin(3*x))
            assert_array_almost_equal(diff(f),df)
            assert_array_almost_equal(diff(df),ddf)
            assert_array_almost_equal(diff(ddf,-1),df)
            assert_array_almost_equal(diff(f,2),ddf)

    def check_int(self):
        n = 64
        x = arange(n)*2*pi/n
        assert_array_almost_equal(diff(sin(x),-1),-cos(x))
        assert_array_almost_equal(diff(sin(x),-2),-sin(x))
        assert_array_almost_equal(diff(sin(x),-4),sin(x))
        assert_array_almost_equal(diff(2*cos(2*x),-1),sin(2*x))

    def check_random_even(self):
        for k in [0,2,4,6]:
            for n in [60,32,64,56,55]:
                f=random ((n,))
                af=Numeric.sum(f)/n
                f=f-af
                # zeroing Nyquist mode:
                f = diff(diff(f,1),-1)
                assert_almost_equal(Numeric.sum(f),0.0)
                assert_array_almost_equal(diff(diff(f,k),-k),f)
                assert_array_almost_equal(diff(diff(f,-k),k),f)

    def check_random_odd(self):
        for k in [0,1,2,3,4,5,6]:
            for n in [33,65,55]:
                f=random ((n,))
                af=Numeric.sum(f)/n
                f=f-af
                assert_almost_equal(Numeric.sum(f),0.0)
                assert_array_almost_equal(diff(diff(f,k),-k),f)
                assert_array_almost_equal(diff(diff(f,-k),k),f)

    def check_zero_nyquist (self):
        for k in [0,1,2,3,4,5,6]:
            for n in [32,33,64,56,55]:
                f=random ((n,))
                af=Numeric.sum(f)/n
                f=f-af
                # zeroing Nyquist mode:
                f = diff(diff(f,1),-1)
                assert_almost_equal(Numeric.sum(f),0.0)
                assert_array_almost_equal(diff(diff(f,k),-k),f)
                assert_array_almost_equal(diff(diff(f,-k),k),f)

    def bench_random(self,level=5):
        print
        print 'Differentiation of periodic functions'
        print '====================================='
        print ' size  |  convolve |    naive'
        print '-------------------------------------'
        for size,repeat in [(100,1500),(1000,300),
                            (256,1500),
                            (512,1000),
                            (1024,500),
                            (2048,200),
                            (2048*2,100),
                            (2048*4,50),
                            ]:
            print '%6s' % size,
            sys.stdout.flush()
            x = arange (size)*2*pi/size
            if size<2000:
                f = sin(x)*cos(4*x)+exp(sin(3*x))
            else:
                f = sin(x)*cos(4*x)
            assert_array_almost_equal(diff(f,1),direct_diff(f,1))
            assert_array_almost_equal(diff(f,2),direct_diff(f,2))
            print '| %9.2f' % self.measure('diff(f,3)',repeat),
            sys.stdout.flush()
            print '| %9.2f' % self.measure('direct_diff(f,3)',repeat),
            sys.stdout.flush()
            print ' (secs for %s calls)' % (repeat)


class test_tilbert(ScipyTestCase):

    def check_definition(self):
        for h in [0.1,0.5,1,5.5,10]:
            for n in [16,17,64,127]:
                x = arange(n)*2*pi/n
                y = tilbert(sin(x),h)
                y1 = direct_tilbert(sin(x),h)
                assert_array_almost_equal (y,y1)
                assert_array_almost_equal(tilbert(sin(x),h),
                                          direct_tilbert(sin(x),h))
                assert_array_almost_equal(tilbert(sin(2*x),h),
                                          direct_tilbert(sin(2*x),h))

    def check_random_even(self):
        for h in [0.1,0.5,1,5.5,10]:
            for n in [32,64,56]:
                f=random ((n,))
                af=Numeric.sum(f)/n
                f=f-af
                assert_almost_equal(Numeric.sum(f),0.0)
                assert_array_almost_equal(direct_tilbert(direct_itilbert(f,h),h),f)

    def check_random_odd(self):
        for h in [0.1,0.5,1,5.5,10]:
            for n in [33,65,55]:
                f=random ((n,))
                af=Numeric.sum(f)/n
                f=f-af
                assert_almost_equal(Numeric.sum(f),0.0)
                assert_array_almost_equal(itilbert(tilbert(f,h),h),f)
                assert_array_almost_equal(tilbert(itilbert(f,h),h),f)

    def bench_random(self,level=5):
        print
        print ' Tilbert transform of periodic functions'
        print '========================================='
        print ' size  | optimized |    naive'
        print '-----------------------------------------'
        for size,repeat in [(100,1500),(1000,300),
                            (256,1500),
                            (512,1000),
                            (1024,500),
                            (2048,200),
                            (2048*2,100),
                            (2048*4,50),
                            ]:
            print '%6s' % size,
            sys.stdout.flush()
            x = arange (size)*2*pi/size
            if size<2000:
                f = sin(x)*cos(4*x)+exp(sin(3*x))
            else:
                f = sin(x)*cos(4*x)
            assert_array_almost_equal(tilbert(f,1),direct_tilbert(f,1))
            print '| %9.2f' % self.measure('tilbert(f,1)',repeat),
            sys.stdout.flush()
            print '| %9.2f' % self.measure('direct_tilbert(f,1)',repeat),
            sys.stdout.flush()
            print ' (secs for %s calls)' % (repeat)

class test_itilbert(ScipyTestCase):

    def check_definition(self):
        for h in [0.1,0.5,1,5.5,10]:
            for n in [16,17,64,127]:
                x = arange(n)*2*pi/n
                y = itilbert(sin(x),h)
                y1 = direct_itilbert(sin(x),h)
                assert_array_almost_equal (y,y1)
                assert_array_almost_equal(itilbert(sin(x),h),
                                          direct_itilbert(sin(x),h))
                assert_array_almost_equal(itilbert(sin(2*x),h),
                                          direct_itilbert(sin(2*x),h))

class test_hilbert(ScipyTestCase):

    def check_definition(self):
        for n in [16,17,64,127]:
            x = arange(n)*2*pi/n
            y = hilbert(sin(x))
            y1 = direct_hilbert(sin(x))
            assert_array_almost_equal (y,y1)
            assert_array_almost_equal(hilbert(sin(2*x)),
                                      direct_hilbert(sin(2*x)))

    def check_tilbert_relation(self):
        for n in [16,17,64,127]:
            x = arange(n)*2*pi/n
            f = sin (x)+cos (2*x)*sin(x)
            y = hilbert(f)
            y1 = direct_hilbert(f)
            assert_array_almost_equal (y,y1)
            y2 = tilbert(f,h=10)
            assert_array_almost_equal (y,y2)

    def check_random_odd(self):
        for n in [33,65,55]:
            f=random ((n,))
            af=Numeric.sum(f)/n
            f=f-af
            assert_almost_equal(Numeric.sum(f),0.0)
            assert_array_almost_equal(ihilbert(hilbert(f)),f)
            assert_array_almost_equal(hilbert(ihilbert(f)),f)

    def check_random_even(self):
        for n in [32,64,56]:
            f=random ((n,))
            af=Numeric.sum(f)/n
            f=f-af
            # zeroing Nyquist mode:
            f = diff(diff(f,1),-1)
            assert_almost_equal(Numeric.sum(f),0.0)
            assert_array_almost_equal(direct_hilbert(direct_ihilbert(f)),f)
            assert_array_almost_equal(hilbert(ihilbert(f)),f)

    def bench_random(self,level=5):
        print
        print ' Hilbert transform of periodic functions'
        print '========================================='
        print ' size  | optimized |    naive'
        print '-----------------------------------------'
        for size,repeat in [(100,1500),(1000,300),
                            (256,1500),
                            (512,1000),
                            (1024,500),
                            (2048,200),
                            (2048*2,100),
                            (2048*4,50),
                            ]:
            print '%6s' % size,
            sys.stdout.flush()
            x = arange (size)*2*pi/size
            if size<2000:
                f = sin(x)*cos(4*x)+exp(sin(3*x))
            else:
                f = sin(x)*cos(4*x)
            assert_array_almost_equal(hilbert(f),direct_hilbert(f))
            print '| %9.2f' % self.measure('hilbert(f)',repeat),
            sys.stdout.flush()
            print '| %9.2f' % self.measure('direct_hilbert(f)',repeat),
            sys.stdout.flush()
            print ' (secs for %s calls)' % (repeat)

class test_ihilbert(ScipyTestCase):

    def check_definition(self):
        for n in [16,17,64,127]:
            x = arange(n)*2*pi/n
            y = ihilbert(sin(x))
            y1 = direct_ihilbert(sin(x))
            assert_array_almost_equal (y,y1)
            assert_array_almost_equal(ihilbert(sin(2*x)),
                                      direct_ihilbert(sin(2*x)))

    def check_itilbert_relation(self):
        for n in [16,17,64,127]:
            x = arange(n)*2*pi/n
            f = sin (x)+cos (2*x)*sin(x)
            y = ihilbert(f)
            y1 = direct_ihilbert(f)
            assert_array_almost_equal (y,y1)
            y2 = itilbert(f,h=10)
            assert_array_almost_equal (y,y2)

class test_shift(ScipyTestCase):

    def check_definition(self):
        for n in [18,17,64,127,32,2048,256]:
            x = arange(n)*2*pi/n
            for a in [0.1,3]:
                assert_array_almost_equal(shift(sin(x),a),direct_shift(sin(x),a))
                assert_array_almost_equal(shift(sin(x),a),sin(x+a))
                assert_array_almost_equal(shift(cos(x),a),cos(x+a))
                assert_array_almost_equal(shift(cos(2*x)+sin(x),a),
                                          cos(2*(x+a))+sin(x+a))
                assert_array_almost_equal(shift(exp(sin(x)),a),exp(sin(x+a)))
            assert_array_almost_equal(shift(sin(x),2*pi),sin(x))
            assert_array_almost_equal(shift(sin(x),pi),-sin(x))
            assert_array_almost_equal(shift(sin(x),pi/2),cos(x))

    def bench_random(self,level=5):
        print
        print ' Shifting periodic functions'
        print '=============================='
        print ' size  | optimized |    naive'
        print '------------------------------'
        for size,repeat in [(100,1500),(1000,300),
                            (256,1500),
                            (512,1000),
                            (1024,500),
                            (2048,200),
                            (2048*2,100),
                            (2048*4,50),
                            ]:
            print '%6s' % size,
            sys.stdout.flush()
            x = arange (size)*2*pi/size
            a = 1
            if size<2000:
                f = sin(x)*cos(4*x)+exp(sin(3*x))
                sf = sin(x+a)*cos(4*(x+a))+exp(sin(3*(x+a)))
            else:
                f = sin(x)*cos(4*x)
                sf = sin(x+a)*cos(4*(x+a))
            assert_array_almost_equal(direct_shift(f,1),sf)
            assert_array_almost_equal(shift(f,1),sf)
            print '| %9.2f' % self.measure('shift(f,a)',repeat),
            sys.stdout.flush()
            print '| %9.2f' % self.measure('direct_shift(f,a)',repeat),
            sys.stdout.flush()
            print ' (secs for %s calls)' % (repeat)

if __name__ == "__main__":
    ScipyTest('fftpack.pseudo_diffs').run()
