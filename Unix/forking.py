#!/usr/bin/env python2.7

import os
import signal
import sys
import time

try:
	pid = os.fork()
except OSError as e:
		print 'fork failed: {}'.format(e)
		sys.exit(1)
		
if pid == 0;	# child
	print '* Child PID: {}, Parent PID: {}'.format(os.getpid(), os.getpid))
	time.sleep(10)
	sys.exit(1)
else:			# parent
	print '# Child PID: {}, Parent PID: {}'.format(pid, os.getpid())
	os.kill(pid, signal.SIGHUP)
	pid, status = os.wait()
	print '# Child pid: {} exited with status {}'.format(pid, status >> 8)