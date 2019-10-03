import tensorflow as tf
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt


ACTIONS = { 0: 'hold', 1: 'up', 2: 'left', 3: 'right'}
IMAGE_WIDTH =  40
IMAGE_HEIGHT = 40
IMAGE_LAYERS = 4

#class Model

class Model:

    '''
    Convert imagename to int data array, static method
    imagename: path to converted image
    return: grayscale representation of the image as numpy array
    '''
    @staticmethod
    def get_image_array(imagename):
        image = Image.open(imagename)#.convert('LA')
        # convert to 2D array (int 0 - 255)
        image_array = np.array(image) / 255
        return image_array

    '''
    Init model, create essentials
    '''
    def __init__(self, sess, learning_rate):
        self.__num_actions = 4
        self.__num_states = IMAGE_WIDTH * IMAGE_WIDTH
        self.__optimizer = None
        self.__states = None
        self.__q_training = None
        self.__value_init = None
        self.__output = None
        self.__init_model(sess, learning_rate)

    '''
    Helper method, used to init the model
    '''
    def __init_model(self, sess, __learning_rate):
        #self.__states = tf.placeholder(shape=[None, self.__num_states], dtype=tf.float32)
        self.__states = tf.compat.v1.placeholder(shape=[None, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_LAYERS], dtype=tf.float32)
        self.__q_training = tf.compat.v1.placeholder(shape=[None, self.__num_actions], dtype=tf.float32)
        # fully-connected layers
        #conv1 = tf.layers.conv2d(self.__states, filters=6, kernel_size=(5, 5), padding='same')
        #pooling = tf.layers.max_pooling2d(conv1, pool_size=(2, 2), strides=2)

        #conv2 = tf.layers.conv2d(pooling, filters=12, kernel_size=(4, 4), padding='same')
        '''pooling2 = tf.layers.max_pooling2d(conv2, pool_size=(2, 2), strides=2)
        conv3 = tf.layers.conv2d(pooling2, filters=12, kernel_size=(3, 3), padding='same')
        flatten = tf.layers.flatten(conv3)
        #full1 = tf.layers.(self.__states, 1000, activation=tf.nn.relu)
        #full2 = tf.layers.dense(full1, 100, activation=tf.nn.relu)
        full1 = tf.layers.dense(flatten, 500, activation=tf.nn.relu)'''
        flatten = tf.compat.v1.layers.flatten(self.__states)
        full = tf.compat.v1.layers.dense(flatten, 500)
        full2 = tf.compat.v1.layers.dense(full, 100)
        full3 = tf.compat.v1.layers.dense(full2, 100)
        self.__output = tf.compat.v1.layers.dense(full3, self.__num_actions)
        loss = tf.losses.mean_squared_error(self.__q_training, self.__output)
        self.__optimizer = tf.compat.v1.train.GradientDescentOptimizer(learning_rate=__learning_rate).minimize(loss)
        init = tf.compat.v1.global_variables_initializer()
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
        #return sess.run(self.__output, feed_dict={self.__states: state_image_array.reshape(1, self.__num_states)})
        return sess.run(self.__output, feed_dict={self.__states: state_image_array.reshape(1, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_LAYERS)})

    '''
    Predict whole batch, use this to train the network
    state_image_arrays: batch of numpy image arrays of state images
    sess: tensorflow session object
    return: tensorflow session run call
    '''
    def predict_batch(self, states_image_arrays, sess):
        #return sess.run(self.__output, feed_dict={self.__states: [state.reshape(self.__num_states) for state in states_image_arrays]})
        return sess.run(self.__output, feed_dict={self.__states: states_image_arrays.reshape(len(states_image_arrays), IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_LAYERS)})
    '''
    Train the neural network based on rewards
    sess: tensorflow session object
    states: numpy array of states without rewards
    rewarded_states: numpy array of states with rewards
    return tensorflow session run call
    '''
    def train_batch(self, sess, states, rewarded_states):
        #sess.run(self.__optimizer, feed_dict={self.__states: states, self.__q_training: rewarded_states})
        sess.run(self.__optimizer, feed_dict={self.__states: states.reshape(len(states), IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_LAYERS), self.__q_training: rewarded_states})

if __name__ == '__main__':
    imagename = 'training/data0.png'
    image = Image.open(imagename)#.convert('LA')
    # convert to 2D array (int 0 - 255)
    image_array = np.array(image)

    imgplot = plt.imshow(image)
    plt.show()
