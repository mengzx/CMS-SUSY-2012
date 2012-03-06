#!/usr/bin/env python

from copy import deepcopy

def foo(*args, **kwargs):
#    print 'args = ', args
#    print 'kwargs = ', kwargs
    for key,v in kwargs.iteritems():
        print "%s=%s" % (key,v)
#        if kwargs[key] is not None:
#           print kwargs[key]
    print '---------------------------------------'

def foo1(*args, **kwargs):
    for key in kwargs:
#        print kwargs[key]
        kwargs[key]=kwargs[key]
    return kwargs

if __name__ == '__main__':
#    foo(1,2,3,4)
#    foo(a=1,b=2,c=3,d=foo1(a=4,b=5,c=6))
    fo1=foo1(a=4,b=5,c=6)
    fo=deepcopy(fo1)
    foo(a=1,b=2,d=fo)
#    foo(1,2,3,4, a=1,b=2,c=3)
#    foo('a', 1, None, a=1, b='2', c=3)

