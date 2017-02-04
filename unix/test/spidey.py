#!/usr/bin/env python2.7

import getopt
import logging
import os
import socket
import sys
import mimetypes
import signal

# Variables
ADDRESS  = '0.0.0.0'
PORT     = 9234
BACKLOG  = 0
LOGLEVEL = logging.INFO
PROGRAM  = os.path.basename(sys.argv[0])
DOCROOT  = '.'
FORKING  = False

# Usage function
def usage(exit_code=0):
	print >>sys.stderr, '''Usage: {program} [-d DOCROOT -p PORT -f -v]

Options:

	-h       Show this help message
	-f       Enable forking mode
	-v       Set logging to DEBUG level
	
	-d DOCROOT Set root directory (default is current directory)
	-p PORT    TCP Port to listen to (default is 9234)'''.format(port=PORT, program=PROGRAM)
	sys.exit(exit_code)

# BaseHandler Class
class BaseHandler(object):
	def __init__(self, fd, address):
		''' Construct handler from file descriptor and remote client address '''
		self.logger  = logging.getLogger()        # Grab logging instance
		self.socket  = fd                         # Store socket file descriptor
		self.address = '{}:{}'.format(*address)   # Store address
		self.stream  = self.socket.makefile('w+') # Open file object from file descriptor
		self.debug('Connect')

	def debug(self, message, *args):
		''' Convenience debugging function '''
		message = message.format(*args)
		self.logger.debug('{} | {}'.format(self.address, message))

	def info(self, message, *args):
		''' Convenience information function '''
		message = message.format(*args)
		self.logger.info('{} | {}'.format(self.address, message))

	def warn(self, message, *args):
		''' Convenience warning function '''
		message = message.format(*args)
		self.logger.warn('{} | {}'.format(self.address, message))

	def error(self, message, *args):
		''' Convenience error function '''
		message = message.format(*args)
		self.logger.error('{} | {}'.format(self.address, message))

	def exception(self, message, *args):
		''' Convenience exception function '''
		message = message.format(*args)
		self.logger.exception('{} | {}'.format(self.address, message))

	def handle(self):
		''' Handle connection '''
		self.debug('Handle')
		raise NotImplementedError

	def finish(self):
		''' Finish connection by flushing stream, shutting down socket, and then closing it '''
		self.debug('Finish')
		try:
			self.stream.flush()
			self.socket.shutdown(socket.SHUT_RDWR)
		except socket.error as e:
			pass    # Ignore socket errors
		finally:
			self.socket.close()

# HTTPHandler Class
class HTTPHandler(BaseHandler):

	def __init__(self, fd, address, docroot=DOCROOT):
		self.docroot = os.path.abspath(DOCROOT)
		BaseHandler.__init__(self, fd, address)

	def handle(self):
		self.debug('Handle')

		# parse HTTP requests
		self._parse_request()

		# build uripath
		self.uripath = self.docroot + os.environ['REQUEST_URI']
		self.logger.debug(self.docroot)
		self.logger.debug(self.uripath)
		self.logger.debug(os.path.exists(self.uripath))
		# check path existence and types and then dispatch
		if not os.path.exists(self.uripath) or self.docroot not in self.uripath:
		self._handle_error(404)     # DOES NOT EXIST (404)
		elif os.path.isfile(self.uripath) and os.access(self.uripath, os.X_OK):
			self._handle_script()       # CGI script
		elif os.path.isfile(self.uripath) and os.access(self.uripath, os.R_OK):
			self._handle_file()         # static file
		elif os.path.isdir(self.uripath) and os.access(self.uripath, os.R_OK):
			self._handle_directory()    # directory listing
		else:
			self._handle_error(403)     # NO PERMISSIONS (403)

	def _parse_request(self):
		# parses requests
		os.environ['REMOTE_ADDR'] = self.address.split(':', 1)[0]
		os.environ['REMOTE_HOST'] = self.address.split(':', 1)[0]
		os.environ['REMOTE_PORT'] = self.address.split(':', 1)[-1]

		data = self.stream.readline().strip()
		line = True
		while data:
			if line:
				os.environ['REQUEST_METHOD'] = data.split()[0]
				resource = data.split()[1]
				os.environ['REQUEST_URI'] = resource.split('?')[0]
			if len(resource.split('?')) >= 2:
				os.environ['QUERY_STRING'] = resource.split('?')[1]
			else:
				data = data.split(': ', 1)
				if len(data) >= 2:
					os.environ['HTTP_' + data[0].upper().replace('-', '_')] = data[1]

			line = False
			data = self.stream.readline().strip()

	def _handle_file(self):
		self.logger.debug(self.uripath)
		# determines file's mimetype
		mimetype, _ = mimetypes.guess_type(self.uripath)
		if mimetype is None:
			mimetype = 'application/octet-stream'

		self.stream.write('HTTP/1.0 200 OK\r\n')
		self.stream.write('Content-Type: {}\r\n'.format(mimetype))
		self.stream.write('\r\n')

		for line in open(self.uripath, 'rb'):
			self.stream.write(line)
		self.stream.flush()

	def _handle_directory(self):
		# constructs HTML page that lists the contents of the directory
		directory = self.uripath

		self.stream.write('HTTP/1.0 200 OK\r\n')
		self.stream.write('Content-Type: text/html\r\n')
		self.stream.write('\r\n')
		self.stream.write('''
				<html>
				<head>
					<title> {} </title>
				</head>
			<body>'''.format(DOCROOT))
		for item in os.listdir(directory):
			path = os.path.join(directory, item)
			if os.path.isfile(path):
				itemType = 'File'
			elif os.path.isdir(path):
				itemType = 'Directory'
			self.stream.write('<p><b>Item: </b>' + '<a href="' + os.path.join(os.environ['REQUEST_URI'], item) + '">' + item + '</a>' + '&nbsp&nbsp&nbsp<b>Size: </b>' + str(os.path.getsize(path)) + '\t<b>Type: </b>' + itemType + '</p>')
		self.stream.write('''
				</body>
				</html>
				''')

		self.stream.flush()

	def _handle_script(self):
	# executes scripts

	signal.signal(signal.SIGCHLD, signal.SIG_DFL)
	for line in os.popen(self.uripath):
	self.stream.write(line)
	signal.signal(signal.SIGCHLD, signal.SIG_IGN)

	def _handle_error(self, codeNum):
		# constructs HTML page that displays specified error code
		self.stream.write('HTTP/1.0 200 OK\r\n')
		self.stream.write('Content-Type: text/html\r\n')
		self.stream.write('\r\n')

		if codeNum == 404:
		self.stream.write('''
			<!DOCTYPE html>
			<html>
			<body>

			<h2 align="center"> Error 404: Not Found </h2>
			<center><img src="star.jpg" alt="Error:404" style="width:600px;height:600px;"></center>

			</body>
			</html>
			''')
		else:
		self.stream.write('''
			<!DOCTYPE html>
			<html>
			<body>

			<h2 align="center"> Error 403: Access Denied </h2>
			<center><img src="403.png" alt="Error403" style="width:600px;height:600px;"><center>

			</body>
			</html>
			''')

		self.stream.flush()


# TCPServer Class

class TCPServer(object):
	def __init__(self, address=ADDRESS, port=PORT, handler=HTTPHandler):
		''' Construct TCPServer object with the specified address, port, and handler '''
		self.logger  = logging.getLogger()                              # Grab logging instance
		self.socket  = socket.socket(socket.AF_INET, socket.SOCK_STREAM)# Allocate TCP socket
		self.address = address                                          # Store address to listen on
		self.port    = port                                             # Store port to lisen on
		self.handler = handler                                          # Store handler for incoming connections

	def run(self):
		''' Run TCP Server on specified address and port by calling the specified handler on each incoming connection '''
		try:
			# Bind socket to address and port and then listen
			self.socket.bind((self.address, self.port))
			self.socket.listen(BACKLOG)
		except socket.error as e:
			self.logger.error('Could not listen on {}:{}: {}'.format(self.address, self.port, e))
			sys.exit(1)

		self.logger.info('Listening on {}:{}...'.format(self.address, self.port))

		while True:
			# Accept incoming connection
				client, address = self.socket.accept()
				self.logger.debug('Accepted connection from {}:{}'.format(*address))
			if not self.forking:
			# Instantiate handler, handle connection, finish connection
				try:
					handler = self.handler(client, address)
					handler.handle()
				except Exception as e:
					handler.exception('Exception: {}', e)
				finally:
					handler.finish()

			else:
				pid = os.fork()
				if pid == 0:  # Child
					self._handle(client, address)
					# Instantiate handler, handle connection, finish connection
					try: 
						handler = self.handler(client, address)
						handler.handle()
					except Exception as e:
						handler.exception('Exception: {}', e)
					finally:
						handler.finish()
					os._exit(0)
				else:
					client.close()


# Main Execution

if __name__ == '__main__':
	# Parse command-line arguments
	try:
		options, arguments = getopt.getopt(sys.argv[1:], "hfvd:p:")
	except getopt.GetoptError as e:
		usage(1)

	for option, value in options:
		if option == '-f':
			FORKING = True
		elif option == '-v':
			LOGLEVEL = logging.DEBUG
		elif option == '-d':
			DOCROOT = value
		elif option == '-p':
			PORT = int(value)
		else:
			usage(1)

	# Set logging level
	logging.basicConfig(
			level   = LOGLEVEL,
		format  = '[%(asctime)s] %(message)s',
		datefmt = '%Y-%m-%d %H:%M:%S',
	)

	# Instantiate and run server
	server = TCPServer(ADDRESS, PORT, HTTPHandler)
	try:
		server.run()
	except KeyboardInterrupt:
		os.system('clear')
		sys.exit(0)