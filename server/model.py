import tensorflow as tf
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt


ACTIONS = { 0: 'hold', 1: 'up', 2: 'left', 3: 'right'}
IMAGE_WIDTH =  200
IMAGE_HEIGHT = 100

#class Model

class Model:

    '''
    Convert imagename to int data array, static method
    imagename: path to converted image
    return: grayscale representation of the image as numpy array
    '''
    @staticmethod
    def get_image_array(imagename):
        image = Image.open(imagename).convert('LA')
        # convert to 2D array (int 0 - 255)
        image_array = np.array(image)
        return image_array
        # imgplot = plt.imshow(image)
        # plt.show()

    '''
    Init model, create essentials
    '''
    def __init__(self, sess):
        self.__num_actions = 4
        self.__num_states = IMAGE_WIDTH * IMAGE_WIDTH
        self.__optimizer = None
        self.__states = None
        self.__q_training = None
        self.__value_init = None
        self.__output = None
        self.__init_model(sess)

    '''
    Helper method, used to init the model
    '''
    def __init_model(self, sess):
        self.__states = tf.placeholder(shape=[None, self.__num_states], dtype=tf.float32)
        self.__q_training = tf.placeholder(shape=[None, self.__num_actions], dtype=tf.float32)
        # fully-connected layers
        full1 = tf.layers.dense(self.__states, 1000, activation=tf.nn.relu)
        full2 = tf.layers.dense(full1, 100, activation=tf.nn.relu)
        self.__output = tf.layers.dense(full2, self.__num_actions)
        loss = tf.losses.mean_squared_error(self.__q_training, self.__output)
        self.__optimizer = tf.train.AdamOptimizer().minimize(loss)
        init = tf.global_variables_initializer()
        sess.run(init)

    '''
    Get amount of states in the model
    return: __num_states
    '''
    def get_num_states(self):
        return self.__num_states

    '''
    Get amount of actions in the model
    return: __num_actions
    '''
    def get_num_actions(self):
        return self.__num_actions

    '''
    Predict based on one state, use this to choose next action
    state_image_array: numpy array of states image
    sess: tensorflow session object
    return: tensorflow session run call
    '''
    def predict_one(self, state_image_array, sess):
        return sess.run(self.__output, feed_dict={self.__states: state_image_array.reshape(1, self.__num_states)})

    '''
    Predict whole batch, use this to train the network
    state_image_arrays: batch of numpy image arrays of state images
    sess: tensorflow session object
    return: tensorflow session run call
    '''
    def predict_batch(self, states_image_arrays, sess):
        return sess.run(self.__output, feed_dict={self.__states: [state.reshape(self.__num_states) for state in states_image_arrays]})

    '''
    Train the neural network based on rewards
    sess: tensorflow session object
    states: numpy array of states without rewards
    rewarded_states: numpy array of states with rewards
    return tensorflow session run call
    '''
    def train_batch(self, sess, states, rewarded_states):
        sess.run(self.__optimizer, feed_dict={self.__states: states, self.__q_training: rewarded_states})
