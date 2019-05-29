from http.server import BaseHTTPRequestHandler
from urllib.parse import urlparse, parse_qs
import socketserver
import sys
import base64
import tensorflow as tf
from MLManager import MLManager


'''
Basic server
Do NOT USE this in production
'''
class BasicServer(BaseHTTPRequestHandler):
    IP = '192.168.0.14'
    PORT = 10000
    reward = 0
    mlManager = None

    '''
    Handle incoming HTTP POST requests
    '''
    def do_POST(self):
        if self.path == '/reward':
            length = int(self.headers['content-length'])
            reward_data = self.rfile.read(length)
            BasicServer.reward = int(reward_data.decode('utf-8').strip('\n'))
            print('reward: ', BasicServer.reward)
            self.send_response(200)
            self.end_headers()
            BasicServer.mlManager.set_reward(BasicServer.reward)

        if self.path == '/update':
            length = int(self.headers['content-length'])
            field_data = self.rfile.read(length)
            # ends to \n, filter it out
            data = field_data[:-1].decode('utf-8')
            action = BasicServer.mlManager.update(data, BasicServer.reward)
            print('action: ', action)
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(bytes(action, 'utf-8'))
            BasicServer.mlManager.train_network()


'''
Main: create server instance and init tensorflow session. Create also MLManager
'''
def main():
    httpd = None
    sess = tf.Session()
    BasicServer.mlManager = MLManager(sess)
    try:
        httpd = socketserver.TCPServer((BasicServer.IP, BasicServer.PORT), BasicServer)
        httpd.serve_forever()
    finally:
        if httpd:
            httpd.server_close()
        sess.close()



if __name__ == '__main__':
    main()
