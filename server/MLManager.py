from data import Data
from model import Model
import model # ACTIONS
import random
import math
import numpy as np

# class MLManager
# Handles all neural network related jobs, forms an interface to the game and server

class MLManager:

    MIN_EPS = 0.01 # min epsilon value. when close to this, the learned model is heavily utilized
    MAX_EPS = 0.99 # max epsilon value. when close to this, actions are completely random
    GAMMA = 0.95 # replace with something appropriate
    '''
    Init MLManager
    In the beginning actions should be choosen completely randomly
    '''
    def __init__(self, sess):
        self.__sess = sess
        self.__model = Model(sess)
        self.__data = Data()
        self.__eps = MLManager.MAX_EPS # set to something more correct
        self.__learning_rate = 0.0005 # adjust this to affect how fast the network learns
        self.__updates = 0
        self.__batch_size = 50

    '''
    Get next action for the AI player
    state: string, path to state image
    return: action string constant, this should be returned to the game itself
    NOTICE: actins are stored as int value in the dict but this returs the matching string
    '''
    def __get_next_action(self, state):
        if random.random() < self.__eps:
            index = random.randrange(0, len(model.ACTIONS))
            self.__data.add_action(index)
            return model.ACTIONS[index]
        else:
            action = np.argmax(self.__model.predict_one(Model.get_image_array(state), self.__sess))
            self.__data.add_action(action)
            return model.ACTIONS[action]

    '''
    Wrapper call for Data.add_reward()
    Call this from server
    '''
    def set_reward(self, reward):
        self.__data.add_reward(reward)

    '''
    Update whole neural network
    Call this after server has received image in string format
    imageStr: new image which represents current state
    prev_reward: prev reward value
    return: action which should be taken
    '''
    def update(self, imageStr, prev_reward):
        # create new image (state)
        self.__data.add_data(imageStr)
        state = self.__data.get_current_state()
        # estimate correct action
        action = self.__get_next_action(state)
        return action

    '''
    Wrapper call for training the network
    Call this from server after action has been returned to client
    '''
    def train_network(self):
        self.__train()
        # update epsilon value
        self.__updates += 1
        self.__eps = MLManager.MIN_EPS + (MLManager.MAX_EPS - MLManager.MIN_EPS) * math.exp(-self.__learning_rate * self.__updates)

    '''
    Train the neural network
    This is called from train_network
    '''
    def __train(self):
        batch_data = self.__data.get_training_data(self.__batch_size)
        if batch_data != []:
            # be sure to filter out possible None values (currently won't do it)
            states = np.array([Model.get_image_array(item[0]) for item in batch_data])
            next_states = np.array([Model.get_image_array(item[3]) for item in batch_data])
            # Q learning Q(s, a)
            Q_1 = self.__model.predict_batch(states, self.__sess)
            # Q learning Q(s', a')
            Q_2 = self.__model.predict_batch(next_states, self.__sess)

            length = len(batch_data)
            # training arrays
            training1 = np.zeros((length, self.__model.get_num_states()))
            training2 = np.zeros((length, self.__model.get_num_actions()))

            for index, data in enumerate(batch_data):
                state, action, reward, next_state = data[0], data[1], data[2], data[3]
                compensated = Q_1[index]
                compensated[action] = reward + MLManager.GAMMA * np.amax(Q_2[index])
                training1[index] = Model.get_image_array(state).reshape(self.__model.get_num_states())
                training2[index] = compensated
            self.__model.train_batch(self.__sess, training1, training2)
