from http.server import BaseHTTPRequestHandler
from urllib.parse import urlparse, parse_qs
import socketserver
import sys
import base64
import tensorflow as tf
from MLManager import MLManager
from data import Data

TensorFlowModelPath = 'model.ckpt'

'''
Basic server
Do NOT USE this in production
'''
class BasicServer(BaseHTTPRequestHandler):
    IP = '192.168.0.14'
    #IP = '192.168.43.124'
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
            (action, from_model) = BasicServer.mlManager.update(data)
            print('action: {}, from model: {}'.format(action, from_model))
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
    with tf.Session() as sess:
        Data.init_ImageNum()
        BasicServer.mlManager = MLManager(sess)
        saver = tf.train.Saver()
        try:
            saver.restore(sess, TensorFlowModelPath)
        except ValueError as e:
            print(e)
        finally:
            try:
                httpd = socketserver.TCPServer((BasicServer.IP, BasicServer.PORT), BasicServer)
                httpd.serve_forever()
            except Exception as e:
                print(e)
            finally:
                if httpd:
                    httpd.server_close()
                Data.store_ImageNum()
                save_path = saver.save(sess, TensorFlowModelPath)



if __name__ == '__main__':
    main()
